#!/usr/bin/env sh
set -e

# ==============================================================================
# WordPress container entrypoint
# Execution order:
# 1. Helpers & runtime checks
# 2. PHP-FPM pool configuration
# 3. Environment (Redis & Database)
# 4. WordPress files & permissions
# 5. Database wait (MariaDB/MySQL)
# 6. WP-CLI bootstrap
# 7. Generate credentials
# 8. Create wp-config.php
# 9. Configure Redis constants
# 10. Install WordPress core
# 11. Language & locale
# 12. Users (admin & common)
# 13. Redis Object Cache plugin
# 14. Start php-fpm
# ==============================================================================

# 1. Helpers & runtime checks
# ---------------------------
log() {
  printf "[wordpress][%s] %s\n" "$(date -u +"%Y-%m-%dT%H:%M:%SZ")" "$*" >&2
}

# Load secrets from *_FILE if present
[ -n "${MARIADB_PASSWORD_FILE:-}" ] && [ -f "${MARIADB_PASSWORD_FILE}" ] && export WORDPRESS_DB_PASSWORD="$(cat "${MARIADB_PASSWORD_FILE}")"
[ -n "${REDIS_PASS_FILE:-}" ] && [ -f "${REDIS_PASS_FILE}" ] && export WORDPRESS_REDIS_PASS="$(cat "${REDIS_PASS_FILE}")"
[ -n "${WORDPRESS_ADMIN_CREDENTIALS_FILE:-}" ] && [ -f "${WORDPRESS_ADMIN_CREDENTIALS_FILE}" ] && set -a && . "${WORDPRESS_ADMIN_CREDENTIALS_FILE}" && set +a
[ -n "${WORDPRESS_USER_CREDENTIALS_FILE:-}" ] && [ -f "${WORDPRESS_USER_CREDENTIALS_FILE}" ] && set -a && . "${WORDPRESS_USER_CREDENTIALS_FILE}" && set +a

# Development mode: print credentials in log
if [ -n "${APP_ENV:-}" ] && [ "${APP_ENV}" = "development" ]; then
  log "Starting wordpress with SITE_URL=${WORDPRESS_SITE_URL} PORT=${WORDPRESS_PORT}
    - SITE_TITLE=${WORDPRESS_SITE_TITLE}
    - ADMIN_USER=${WORDPRESS_ADMIN_USER} ADMIN_EMAIL=${WORDPRESS_ADMIN_EMAIL} ADMIN_PASS=${WORDPRESS_ADMIN_PASS}
    - USER=${WORDPRESS_USER} USER_EMAIL=${WORDPRESS_USER_EMAIL} USER_ROLE=${WORDPRESS_USER_ROLE} USER_PASS=${WORDPRESS_USER_PASS}
    - LOCALE=${WORDPRESS_LOCALE}
    - DB_HOST=${WORDPRESS_DB_HOST} DB_PORT=${WORDPRESS_DB_PORT} DB_NAME=${WORDPRESS_DB_NAME} DB_USER=${WORDPRESS_DB_USER} WORDPRESS_DB_PASSWORD=${WORDPRESS_DB_PASSWORD}
    - REDIS_HOST=${WORDPRESS_REDIS_HOST} REDIS_PORT=${WORDPRESS_REDIS_PORT} REDIS_PASSWORD=${WORDPRESS_REDIS_PASS}"
fi

# Helper: run command as www-data
as_www() { su -s /bin/sh -c "$*" www-data; }

# Detect php-fpm binary
PHP_FPM_BIN="$(command -v php-fpm || command -v php-fpm8.2 || true)"
[ -z "$PHP_FPM_BIN" ] && log "php-fpm binary not found" && exit 1

# 2. PHP-FPM pool configuration
# ------------------------------
POOL_DIR="$(find /etc/php -type d -path '*/fpm/pool.d' -print -quit 2>/dev/null || true)"
[ -z "$POOL_DIR" ] && BASE_DIR="$(find /etc/php -type d -path '*/fpm' -print -quit 2>/dev/null || echo /etc/php/8.2/fpm)" && POOL_DIR="$BASE_DIR/pool.d"
POOL_CONF="$POOL_DIR/www.conf"
TEMPLATE="/usr/local/share/wordpress-fpm/www.conf.template"
HAS_ENVSUBST="$(command -v envsubst || true)"

if [ -f "$TEMPLATE" ]; then
  log "Rendering FPM pool from template (port=${WORDPRESS_PORT})"
  mkdir -p "$POOL_DIR"
  [ -n "$HAS_ENVSUBST" ] && envsubst '${WORDPRESS_PORT}' < "$TEMPLATE" > "$POOL_CONF" || sed "s|\${WORDPRESS_PORT}|${WORDPRESS_PORT}|g" "$TEMPLATE" > "$POOL_CONF"
elif [ -f "$POOL_CONF" ]; then
  log "Updating existing $POOL_CONF (port=${WORDPRESS_PORT})"
  sed -ri "s~^\s*listen\s*=.*$~listen = 0.0.0.0:${WORDPRESS_PORT}~" "$POOL_CONF" || true
  sed -ri "s~^;?\s*clear_env\s*=.*$~clear_env = no~" "$POOL_CONF" || true
  grep -q "^ping.path" "$POOL_CONF" || echo "ping.path = /ping" >> "$POOL_CONF"
  grep -q "^pm.status_path" "$POOL_CONF" || echo "pm.status_path = /status" >> "$POOL_CONF"
else
  log "ERROR: No FPM pool template or config found."
  exit 1
fi

# 3. Environment – Redis & Database
# ---------------------------------
REDIS_HOST="${WORDPRESS_REDIS_HOST:-}"
REDIS_PORT="${WORDPRESS_REDIS_PORT:-6379}"
REDIS_PASS="${WORDPRESS_REDIS_PASS:-}"
[ -n "$REDIS_HOST" ] && log "Redis enabled: ${REDIS_HOST}:${REDIS_PORT}" || log "Redis not configured."

DB_HOST="${WORDPRESS_DB_HOST}"
DB_PORT="${WORDPRESS_DB_PORT}"
DB_NAME="${WORDPRESS_DB_NAME}"
DB_USER="${WORDPRESS_DB_USER}"
DB_PASS="${WORDPRESS_DB_PASSWORD}"

# 4. WordPress files & permissions
# --------------------------------
mkdir -p /var/www/html
if [ ! -e /var/www/html/wp-settings.php ] || [ ! -d /var/www/html/wp-includes ]; then
  log "Populating WordPress core into /var/www/html"
  rm -f /var/www/html/index.nginx-debian.html 2>/dev/null || true
  cp -a /usr/src/wordpress/. /var/www/html/
fi
chown -R www-data:www-data /var/www/html

# 5. Database wait
# ----------------
DB_CLI="$(command -v mariadb || command -v mysql || true)"
[ -z "$DB_CLI" ] && log "ERROR: No mariadb/mysql client found." && exit 1

log "Waiting for DB at ${DB_HOST}:${DB_PORT} (database=${DB_NAME})"
i=0
until $DB_CLI -h"$DB_HOST" -P"$DB_PORT" -u"$DB_USER" -p"$DB_PASS" "$DB_NAME" -e "SELECT 1" >/dev/null 2>&1; do
  i=$((i+1)); [ $i -gt 120 ] && log "DB not reachable after 120s" && exit 1
  sleep 1
done
log "DB is reachable."

# 6. WP-CLI bootstrap
# -------------------
if ! command -v wp >/dev/null 2>&1; then
  log "Installing wp-cli"
  curl -fsSL https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar -o /usr/local/bin/wp
  chmod +x /usr/local/bin/wp
fi

# 7. Generate credentials
# -----------------------
gen_pass() { tr -dc 'A-Za-z0-9!@#%^&*' </dev/urandom | head -c 20; }
[ -z "${WORDPRESS_ADMIN_PASS:-}" ] && WORDPRESS_ADMIN_PASS="$(gen_pass)" && export WORDPRESS_ADMIN_PASS && log "Generated WORDPRESS_ADMIN_PASS"
[ -z "${WORDPRESS_USER_PASS:-}" ] && WORDPRESS_USER_PASS="$(gen_pass)" && export WORDPRESS_USER_PASS && log "Generated WORDPRESS_USER_PASS"

# 8. Create wp-config.php
# -----------------------
if [ ! -f /var/www/html/wp-config.php ]; then
  log "Creating wp-config.php"
  as_www "wp config create --skip-check --dbname='${DB_NAME}' --dbuser='${DB_USER}' --dbpass='${DB_PASS}' --dbhost='${DB_HOST}:${DB_PORT}' --path=/var/www/html --allow-root"
fi

# 9. Configure Redis constants
# ----------------------------
if [ -n "$REDIS_HOST" ]; then
  as_www "wp config set WP_CACHE true --type=constant --raw --path=/var/www/html --allow-root" || true
  as_www "wp config set WP_REDIS_HOST '${REDIS_HOST}' --type=constant --path=/var/www/html --allow-root" || true
  as_www "wp config set WP_REDIS_PORT ${REDIS_PORT} --type=constant --raw --path=/var/www/html --allow-root" || true
  [ -n "$REDIS_PASS" ] && as_www "wp config set WP_REDIS_PASSWORD '${REDIS_PASS}' --type=constant --path=/var/www/html --allow-root" || true
fi

# 10. Install WordPress core
# --------------------------
if ! as_www "wp core is-installed --path=/var/www/html --allow-root" >/dev/null 2>&1; then
  log "Installing WordPress core at ${WORDPRESS_SITE_URL}"
  as_www "wp core install \
    --url='${WORDPRESS_SITE_URL}' \
    --title='${WORDPRESS_SITE_TITLE}' \
    --admin_user='${WORDPRESS_ADMIN_USER}' \
    --admin_password='${WORDPRESS_ADMIN_PASS}' \
    --admin_email='${WORDPRESS_ADMIN_EMAIL}' \
    --locale='${WORDPRESS_LOCALE}' \
    --skip-email \
    --path=/var/www/html \
    --allow-root"
else
  log "WordPress core already installed"
fi

# 11. Language & locale
# ---------------------
if [ -n "${WORDPRESS_LOCALE:-}" ]; then
  log "Ensuring core language '${WORDPRESS_LOCALE}'"
  as_www "wp language core install '${WORDPRESS_LOCALE}' --path=/var/www/html --allow-root" || true
  if as_www "wp language core is-installed '${WORDPRESS_LOCALE}' --path=/var/www/html --allow-root" >/dev/null 2>&1; then
    as_www "wp site switch-language '${WORDPRESS_LOCALE}' --path=/var/www/html --allow-root"
    as_www "wp option update WPLANG '${WORDPRESS_LOCALE}' --path=/var/www/html --allow-root"
    as_www "wp user meta update '${WORDPRESS_ADMIN_USER}' locale '${WORDPRESS_LOCALE}' --path=/var/www/html --allow-root" || true
    [ -n "${WORDPRESS_USER:-}" ] && as_www "wp user meta update '${WORDPRESS_USER}' locale '${WORDPRESS_LOCALE}' --path=/var/www/html --allow-root" || true
  fi
fi

# 12. Users (admin & common)
# --------------------------
if as_www "wp user get '${WORDPRESS_ADMIN_USER}' --path=/var/www/html --allow-root" >/dev/null 2>&1; then
  as_www "wp user update '${WORDPRESS_ADMIN_USER}' --user_pass='${WORDPRESS_ADMIN_PASS}' --user_email='${WORDPRESS_ADMIN_EMAIL}' --skip-email --path=/var/www/html --allow-root"
else
  as_www "wp user create '${WORDPRESS_ADMIN_USER}' '${WORDPRESS_ADMIN_EMAIL}' --role=administrator --user_pass='${WORDPRESS_ADMIN_PASS}' --path=/var/www/html --allow-root"
fi

if as_www "wp user get '${WORDPRESS_USER}' --path=/var/www/html --allow-root" >/dev/null 2>&1; then
  as_www "wp user update '${WORDPRESS_USER}' --user_pass='${WORDPRESS_USER_PASS}' --user_email='${WORDPRESS_USER_EMAIL}' --role='${WORDPRESS_USER_ROLE}' --path=/var/www/html --allow-root"
else
  as_www "wp user create '${WORDPRESS_USER}' '${WORDPRESS_USER_EMAIL}' --role='${WORDPRESS_USER_ROLE}' --user_pass='${WORDPRESS_USER_PASS}' --path=/var/www/html --allow-root"
fi

# 13. Redis Object Cache plugin
# -----------------------------
if [ -n "$REDIS_HOST" ]; then
  log "Configuring Redis Object Cache"
  as_www "wp plugin install redis-cache --path=/var/www/html --allow-root" || true
  as_www "wp plugin activate redis-cache --path=/var/www/html --allow-root" || true
  as_www "wp redis enable --path=/var/www/html --allow-root" || true
fi

# 14. Start php-fpm
# -----------------
log "✅ Provision complete. Starting php-fpm on port ${WORDPRESS_PORT}"
exec "$PHP_FPM_BIN" -F