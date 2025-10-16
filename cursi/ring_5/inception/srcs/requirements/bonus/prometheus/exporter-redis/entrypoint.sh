#!/bin/sh
set -e

log() {
  printf "[exporter-redis][%s] %s\n" "$(date -u +"%Y-%m-%dT%H:%M:%SZ")" "$*" >&2
}

# Carga password desde secret si REDIS_PASSWORD_FILE está definido
[ -n "${REDIS_PASSWORD_FILE:-}" ] && [ -f "${REDIS_PASSWORD_FILE}" ] \
  && export REDIS_PASSWORD="$(tr -d '\r' < "${REDIS_PASSWORD_FILE}" | sed -e '${/^\n$/d;}')"

# Construye la URL redis://:password@host:port
REDIS_URL="redis://:${REDIS_PASSWORD:-}@${EXPORTER_REDIS_HOST}:${EXPORTER_REDIS_PORT}"

log "Connecting to ${EXPORTER_REDIS_HOST}:${EXPORTER_REDIS_PORT}"

exec /usr/local/bin/redis_exporter \
  --web.listen-address=":9092" \
  --redis.addr="${REDIS_URL}"