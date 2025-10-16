#!/bin/sh
set -e

log() {
  printf "[exporter-mysqld][%s] %s\n" "$(date -u +"%Y-%m-%dT%H:%M:%SZ")" "$*" >&2
}

# Read password from secret file if provided
if [ -n "${EXPORTER_MYSQLD_PASSWORD_FILE:-}" ] && [ -f "${EXPORTER_MYSQLD_PASSWORD_FILE}" ]; then
  # elimina posibles \r y salto de línea final
  EXPORTER_MYSQLD_PASSWORD="$(tr -d '\r' < "${EXPORTER_MYSQLD_PASSWORD_FILE}" | sed -e '${/^\n$/d;}')"
fi

: "${EXPORTER_MYSQLD_PASSWORD:?Falta contraseña (EXPORTER_MYSQLD_PASSWORD o *_FILE)}"

# Escribimos .my.cnf para el exporter
CNF="/etc/mysqld_exporter/.my.cnf"
# shellcheck disable=SC1117
cat > "${CNF}" <<EOF
[client]
user=${EXPORTER_USER}
password=${EXPORTER_MYSQLD_PASSWORD}
host=${EXPORTER_MYSQLD_HOST}
port=${EXPORTER_MYSQLD_PORT}
EOF

# Permisos seguros
chmod 600 "${CNF}"

log "Using ${CNF} (user=${EXPORTER_USER}, host=${EXPORTER_MYSQLD_HOST}, port=${EXPORTER_MYSQLD_PORT})"

# Ejecuta exporter con ese config
exec /usr/local/bin/mysqld_exporter \
  --config.my-cnf="${CNF}" \
  --web.listen-address=":9091"