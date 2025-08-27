#!/usr/bin/env bash
set -e

log() {
  printf "[mariadb-setup][%s] %s\n" "$(date -u +"%Y-%m-%dT%H:%M:%SZ")" "$*" >&2
}

log "Starting service mariadb with DATABASE=${MARIADB_DATABASE} USER=${MARIADB_USER} PASSWORD=${MARIADB_PASSWORD}"

# Variables
DATADIR="/var/lib/mysql"
EXTRA_ARGS=()

# Data directory initialization
if [ ! -d "${DATADIR}/mysql" ]; then
  echo "Initializing data directory..."
  install -o mysql -g mysql -m 0755 -d "${DATADIR}"
  mysql_install_db --user=mysql --ldata="${DATADIR}" --basedir=/usr --defaults-file=/etc/mysql/mariadb.cnf > /dev/null

  # Temporarily start to create users/db
  mysqld --skip-networking --user=mysql --datadir="${DATADIR}" &
  pid="$!"

  echo "Waiting for MariaDB to start..."
  for i in {30..0}; do
    if mariadb-admin ping --silent; then
      break
    fi
    sleep 1
  done
  if [ "$i" = 0 ]; then
    echo >&2 "MariaDB did not start in time."
    exit 1
  fi

  mariadb --protocol=socket <<-EOSQL
    DELETE FROM mysql.user WHERE User='';
    DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost');
    FLUSH PRIVILEGES;
EOSQL

  if [ -n "${MARIADB_ROOT_PASSWORD}" ]; then
    mariadb --protocol=socket <<-EOSQL
      ALTER USER 'root'@'localhost' IDENTIFIED BY '${MARIADB_ROOT_PASSWORD}';
      FLUSH PRIVILEGES;
EOSQL
  fi

  # Create DB and app user if defined
  if [ -n "${MARIADB_DATABASE}" ]; then
    mariadb --protocol=socket -uroot <<-EOSQL
      CREATE DATABASE IF NOT EXISTS \`${MARIADB_DATABASE}\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
EOSQL
  fi

  if [ -n "${MARIADB_USER}" ] && [ -n "${MARIADB_PASSWORD}" ]; then
    # Ensure the user is created with host '%'
    mariadb --protocol=socket -uroot <<-EOSQL
      DROP USER IF EXISTS '${MARIADB_USER}'@'localhost';
      CREATE USER IF NOT EXISTS '${MARIADB_USER}'@'%' IDENTIFIED BY '${MARIADB_PASSWORD}';
      FLUSH PRIVILEGES;
EOSQL

    # Grant privileges depending on whether a database is defined or not
    if [ -n "${MARIADB_DATABASE}" ]; then
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

  # Stop the temporary mysqld and exit; the main CMD will start it
  kill -s TERM "$pid"
  wait "$pid"
  echo "Initialization completed."
fi

# If the datadir already exists (instance already initialized), generate idempotent SQL at startup
BOOTSTRAP_SQL="/tmp/bootstrap-init.sql"
if [ -d "${DATADIR}/mysql" ]; then
  : > "${BOOTSTRAP_SQL}"
  NEED_BOOTSTRAP=0
  if [ -n "${MARIADB_ROOT_PASSWORD}" ]; then
    echo "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MARIADB_ROOT_PASSWORD}';" >> "${BOOTSTRAP_SQL}"
    echo "FLUSH PRIVILEGES;" >> "${BOOTSTRAP_SQL}"
    NEED_BOOTSTRAP=1
  fi
  # Create database if requested
  if [ -n "${MARIADB_DATABASE}" ]; then
    echo "CREATE DATABASE IF NOT EXISTS \`${MARIADB_DATABASE}\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;" >> "${BOOTSTRAP_SQL}"
    NEED_BOOTSTRAP=1
  fi
  # Create user and permissions if requested
  if [ -n "${MARIADB_USER}" ] && [ -n "${MARIADB_PASSWORD}" ]; then
    {
      echo "CREATE USER IF NOT EXISTS '${MARIADB_USER}'@'%' IDENTIFIED BY '${MARIADB_PASSWORD}';"
      if [ -n "${MARIADB_DATABASE}" ]; then
        echo "GRANT ALL PRIVILEGES ON \`${MARIADB_DATABASE}\`.* TO '${MARIADB_USER}'@'%';"
      else
        echo "GRANT ALL PRIVILEGES ON *.* TO '${MARIADB_USER}'@'%';"
      fi
      echo "FLUSH PRIVILEGES;"
    } >> "${BOOTSTRAP_SQL}"
    NEED_BOOTSTRAP=1
  fi
  # If there is nothing to do, clean the file; if there are tasks, add --init-file
  if [ "${NEED_BOOTSTRAP}" = "0" ]; then
    rm -f "${BOOTSTRAP_SQL}"
  else
    EXTRA_ARGS+=( "--init-file=${BOOTSTRAP_SQL}" )
  fi
fi

# Exec the main process
exec "$@" "${EXTRA_ARGS[@]}"
