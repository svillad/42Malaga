#!/usr/bin/env sh
set -eu

# 1. Logging helper
log() {
  printf "[redis][%s] %s\n" "$(date -u +"%Y-%m-%dT%H:%M:%SZ")" "$*" >&2
}

# 2. Load Redis password from *_FILE if provided
[ -n "${REDIS_PASS_FILE:-}" ] && [ -f "${REDIS_PASS_FILE}" ] && export REDIS_PASS="$(cat "${REDIS_PASS_FILE}")"

# 3. Render redis.conf with environment variables using envsubst
envsubst < /etc/redis/redis.conf > /tmp/redis.conf

# 4. generate healthcheck config if password is set
if [ -n "${REDIS_PASS_FILE:-}" ] && [ -f "${REDIS_PASS_FILE}" ]; then
  REDIS_PASS="$(cat "${REDIS_PASS_FILE}")"
  export REDIS_PASS
  printf "auth %s\n" "$REDIS_PASS" > /etc/redis/healthcheck.conf
  chmod 600 /etc/redis/healthcheck.conf
fi

# 5. Start Redis with the rendered configuration
log "✅ Provision complete. Launching Redis"
exec redis-server /tmp/redis.conf