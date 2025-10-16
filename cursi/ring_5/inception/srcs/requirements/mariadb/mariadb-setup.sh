#!/usr/bin/env sh
set -e

# 1. Logging helper
log() {
  printf "[mariadb][%s] %s\n" "$(date -u +"%Y-%m-%dT%H:%M:%SZ")" "$*" >&2
}

# 2. Load MariaDB passwords from *_FILE if provided
[ -n "${MARIADB_PASSWORD_FILE:-}" ] && [ -f "${MARIADB_PASSWORD_FILE}" ] && export MARIADB_PASSWORD="$(cat "${MARIADB_PASSWORD_FILE}")"
[ -n "${MARIADB_ROOT_PASSWORD_FILE:-}" ] && [ -f "${MARIADB_ROOT_PASSWORD_FILE}" ] && export MARIADB_ROOT_PASSWORD="$(cat "${MARIADB_ROOT_PASSWORD_FILE}")"
[ -n "${MARIADB_EXPORTER_PASSWORD_FILE:-}" ] && [ -f "${MARIADB_EXPORTER_PASSWORD_FILE}" ] && export MARIADB_EXPORTER_PASSWORD="$(cat "${MARIADB_EXPORTER_PASSWORD_FILE}")"

# 3. Print startup information (hide password unless in development mode)
if [ -n "${APP_ENV:-}" ] && [ "${APP_ENV}" = "development" ]; then
  log "Starting service mariadb with DATABASE=${MARIADB_DATABASE} USER=${MARIADB_USER} PASSWORD=${MARIADB_PASSWORD} PORT=${MARIADB_PORT}"
else
  log "Starting service mariadb with DATABASE=${MARIADB_DATABASE} USER=${MARIADB_USER} PASSWORD=*** PORT=${MARIADB_PORT}"
fi

# 4. Define variables
DATADIR="/var/lib/mysql"
EXTRA_ARGS=""
SOCKET="${DATADIR}/mysqld.sock"
[ -d "${DATADIR}" ] && chown -R mysql:mysql "${DATADIR}"

# 5. Initialize data directory if it does not exist
if [ ! -d "${DATADIR}/mysql" ]; then
  echo "Initializing data directory..."
  install -o mysql -g mysql -m 0755 -d "${DATADIR}"
  mysql_install_db --user=mysql --ldata="${DATADIR}" --basedir=/usr --defaults-file=/etc/mysql/mariadb.cnf > /dev/null

  # 6. Start temporary mysqld (no networking) to bootstrap users and db
  mysqld --skip-networking --user=mysql --datadir="${DATADIR}" &
  pid="$!"

  # 7. Wait until MariaDB is ready
  echo "Waiting for MariaDB to start..."
  i=30
  while [ "$i" -gt 0 ]; do
    if mariadb-admin ping --silent; then
      break
    fi
    i=$((i - 1))
    sleep 1
  done
  if [ "$i" -eq 0 ]; then
    echo >&2 "MariaDB did not start in time."
    exit 1
  fi

  # 8. Cleanup anonymous/root users
  mariadb --protocol=socket <<-EOSQL
    DELETE FROM mysql.user WHERE User='';
    DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost');
    FLUSH PRIVILEGES;
EOSQL

  # 9. Set root password if provided
  if [ -n "${MARIADB_ROOT_PASSWORD:-}" ]; then
    mariadb --protocol=socket <<-EOSQL
      ALTER USER 'root'@'localhost' IDENTIFIED BY '${MARIADB_ROOT_PASSWORD}';
      FLUSH PRIVILEGES;
EOSQL
  fi

  # 10. Create application database if defined
  if [ -n "${MARIADB_DATABASE:-}" ]; then
    mariadb --protocol=socket -uroot <<-EOSQL
      CREATE DATABASE IF NOT EXISTS \`${MARIADB_DATABASE}\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
EOSQL
  fi

  # 11. Create application user and grant privileges
  if [ -n "${MARIADB_USER:-}" ] && [ -n "${MARIADB_PASSWORD:-}" ]; then
    mariadb --protocol=socket -uroot <<-EOSQL
      DROP USER IF EXISTS '${MARIADB_USER}'@'localhost';
      CREATE USER IF NOT EXISTS '${MARIADB_USER}'@'%' IDENTIFIED BY '${MARIADB_PASSWORD}';
      FLUSH PRIVILEGES;
EOSQL

    if [ -n "${MARIADB_DATABASE:-}" ]; then
      mariadb --protocol=socket -uroot <<-EOSQL
        GRANT ALL PRIVILEGES ON \`${MARIADB_DATABASE}\`.* TO '${MARIADB_USER}'@'%';
        FLUSH PRIVILEGES;
EOSQL
    else
      mariadb --protocol=socket -uroot <<-EOSQL
        GRANT ALL PRIVILEGES ON *.* TO '${MARIADB_USER}'@'%';
        FLUSH PRIVILEGES;
EOSQL
    fi
  fi

  if [ -n "${MARIADB_EXPORTER_USER:-}" ] && [ -n "${MARIADB_EXPORTER_PASSWORD:-}" ]; then
    mariadb --protocol=socket --socket="${SOCKET}" -uroot <<-EOSQL
      CREATE USER IF NOT EXISTS '${MARIADB_EXPORTER_USER}'@'%' IDENTIFIED BY '${MARIADB_EXPORTER_PASSWORD}';
      GRANT PROCESS, REPLICATION CLIENT, SLAVE MONITOR, SELECT ON *.* TO '${MARIADB_EXPORTER_USER}'@'%';
      FLUSH PRIVILEGES;
EOSQL
  fi

  # 12. Stop temporary mysqld
  kill -s TERM "$pid"
  wait "$pid"
  echo "Initialization completed."
fi

# 13. Generate bootstrap SQL file for idempotent changes (when data dir already exists)
BOOTSTRAP_SQL="/tmp/bootstrap-init.sql"
if [ -d "${DATADIR}/mysql" ]; then
  : > "${BOOTSTRAP_SQL}"
  NEED_BOOTSTRAP=0

  # 13a. Update root password if needed
  if [ -n "${MARIADB_ROOT_PASSWORD:-}" ]; then
    {
      echo "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MARIADB_ROOT_PASSWORD}';"
      echo "FLUSH PRIVILEGES;"
    } >> "${BOOTSTRAP_SQL}"
    NEED_BOOTSTRAP=1
  fi

  # 13b. Ensure database exists
  if [ -n "${MARIADB_DATABASE:-}" ]; then
    echo "CREATE DATABASE IF NOT EXISTS \`${MARIADB_DATABASE}\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;" >> "${BOOTSTRAP_SQL}"
    NEED_BOOTSTRAP=1
  fi

  # 13c. Ensure user exists and has privileges
  if [ -n "${MARIADB_USER:-}" ] && [ -n "${MARIADB_PASSWORD:-}" ]; then
    {
      echo "CREATE USER IF NOT EXISTS '${MARIADB_USER}'@'%' IDENTIFIED BY '${MARIADB_PASSWORD}';"
      if [ -n "${MARIADB_DATABASE:-}" ]; then
        echo "GRANT ALL PRIVILEGES ON \`${MARIADB_DATABASE}\`.* TO '${MARIADB_USER}'@'%';"
      else
        echo "GRANT ALL PRIVILEGES ON *.* TO '${MARIADB_USER}'@'%';"
      fi
      echo "FLUSH PRIVILEGES;"
    } >> "${BOOTSTRAP_SQL}"
    NEED_BOOTSTRAP=1
  fi

  # 13e. Ensure exporter user and privileges
  if [ -n "${MARIADB_EXPORTER_USER:-}" ] && [ -n "${MARIADB_EXPORTER_PASSWORD:-}" ]; then
    {
      echo "CREATE USER IF NOT EXISTS '${MARIADB_EXPORTER_USER}'@'%' IDENTIFIED BY '${MARIADB_EXPORTER_PASSWORD}';"
      echo "GRANT PROCESS, REPLICATION CLIENT, SLAVE MONITOR, SELECT ON *.* TO '${MARIADB_EXPORTER_USER}'@'%';"
      echo "FLUSH PRIVILEGES;"
    } >> "${BOOTSTRAP_SQL}"
    NEED_BOOTSTRAP=1
  fi

  # 13d. Clean bootstrap file if nothing to do, otherwise add as init-file
  if [ "${NEED_BOOTSTRAP}" = "0" ]; then
    rm -f "${BOOTSTRAP_SQL}"
  else
    EXTRA_ARGS="${EXTRA_ARGS} --init-file=${BOOTSTRAP_SQL}"
  fi
fi

# 14. Exec the main process, ensuring desired port is set
if [ "${1:-}" = "mysqld" ]; then
  DESIRED_PORT="${MARIADB_PORT:-3306}"
  log "✅ Provision complete. Starting mysqld on port ${DESIRED_PORT}"
  exec "$@" ${EXTRA_ARGS} "--user=mysql" "--port=${DESIRED_PORT}"
else
  log "✅ Provision complete. Starting ${*}"
  exec "$@" ${EXTRA_ARGS}
fi
