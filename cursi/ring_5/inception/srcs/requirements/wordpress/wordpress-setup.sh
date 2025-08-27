#!/bin/sh
set -e

log() {
  printf "[wordpress-setup][%s] %s\n" "$(date -u +"%Y-%m-%dT%H:%M:%SZ")" "$*" >&2
}

# Detect php-fpm binary
PHP_FPM_BIN="$(command -v php-fpm || command -v php-fpm8.2 || true)"
if [ -z "$PHP_FPM_BIN" ]; then
  log "php-fpm binary not found"
  exit 1
fi

# ---------------------------
# Configure PHP-FPM pool
# ---------------------------
# Resolve pool.d path (Debian layout)
POOL_DIR="$(find /etc/php -type d -path '*/fpm/pool.d' -print -quit 2>/dev/null || true)"
if [ -z "$POOL_DIR" ]; then
  BASE_DIR="$(find /etc/php -type d -path '*/fpm' -print -quit 2>/dev/null || echo /etc/php/8.2/fpm)"
  POOL_DIR="$BASE_DIR/pool.d"
fi
POOL_CONF="$POOL_DIR/www.conf"

TEMPLATE="/usr/local/share/wordpress-fpm/www.conf.template"
HAS_ENVSUBST="$(command -v envsubst || true)"

# Prefer rendering from template; fallback to sed on existing www.conf. No minimal creation.
if [ -f "$TEMPLATE" ]; then
  log "Rendering FPM pool from template: $TEMPLATE (port=${WORDPRESS_PORT})"
  mkdir -p "$POOL_DIR"
  if [ -n "$HAS_ENVSUBST" ]; then
    envsubst '${WORDPRESS_PORT}' < "$TEMPLATE" > "$POOL_CONF"
  else
    sed "s|\${WORDPRESS_PORT}|${WORDPRESS_PORT}|g" "$TEMPLATE" > "$POOL_CONF"
  fi
else
  if [ -f "$POOL_CONF" ]; then
    log "Template not found; updating existing $POOL_CONF via sed (port=${WORDPRESS_PORT})"
    sed -ri "s~^\s*listen\s*=.*$~listen = 0.0.0.0:${WORDPRESS_PORT}~" "$POOL_CONF" || true
    sed -ri "s~^;?\s*clear_env\s*=.*$~clear_env = no~" "$POOL_CONF" || true
    grep -q "^ping.path" "$POOL_CONF" || echo "ping.path = /ping" >> "$POOL_CONF"
    grep -q "^pm.status_path" "$POOL_CONF" || echo "pm.status_path = /status" >> "$POOL_CONF"
  else
    log "ERROR: Neither template ($TEMPLATE) nor existing pool config ($POOL_CONF) found."
    exit 1
  fi
fi

# ---------------------------
# WordPress files & perms
# ---------------------------
mkdir -p /var/www/html
if [ ! -e /var/www/html/wp-settings.php ] || [ ! -d /var/www/html/wp-includes ]; then
  log "Populating WordPress core into /var/www/html (missing wp-includes/wp-settings.php)"
  rm -f /var/www/html/index.nginx-debian.html 2>/dev/null || true
  cp -a /usr/src/wordpress/. /var/www/html/
fi
chown -R www-data:www-data /var/www/html

# ---------------------------
# DB wait using MariaDB/MySQL CLI
# ---------------------------
DB_HOST="${WORDPRESS_DB_HOST}"
DB_PORT="${WORDPRESS_DB_PORT}"
DB_NAME="${WORDPRESS_DB_NAME}"
DB_USER="${WORDPRESS_DB_USER}"
DB_PASS="${WORDPRESS_DB_PASSWORD}"

DB_CLI="$(command -v mariadb || true)"
[ -z "$DB_CLI" ] && DB_CLI="$(command -v mysql || true)"
if [ -z "$DB_CLI" ]; then
  log "ERROR: Neither 'mariadb' nor 'mysql' client found. Please install mariadb-client in the image."
  exit 1
fi

log "Waiting for DB at ${DB_HOST}:${DB_PORT} (database=${DB_NAME}) using ${DB_CLI}" 
i=0
until $DB_CLI -h"$DB_HOST" -P"$DB_PORT" -u"$DB_USER" -p"$DB_PASS" "$DB_NAME" -e "SELECT 1" >/dev/null 2>&1; do
  i=$((i+1))
  if [ $i -gt 120 ]; then
    log "DB not reachable after 120s"
    exit 1
  fi
  sleep 1
done
log "DB is reachable."

# ---------------------------
# WordPress provision (WP-CLI)
# ---------------------------
as_www() { su -s /bin/sh -c "$*" www-data; }

# Install wp-cli if missing
if ! command -v wp >/dev/null 2>&1; then
  log "wp-cli not found; installing locally"
  curl -fsSL https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar -o /usr/local/bin/wp
  chmod +x /usr/local/bin/wp
fi

# Generate passwords if blank
gen_pass() { tr -dc 'A-Za-z0-9!@#%^&*' </dev/urandom | head -c 20; }
[ -z "${WORDPRESS_ADMIN_PASS:-}" ] && WORDPRESS_ADMIN_PASS="$(gen_pass)" && export WORDPRESS_ADMIN_PASS && log "Generated WORDPRESS_ADMIN_PASS (hidden)"
[ -z "${WORDPRESS_USER_PASS:-}" ] && WORDPRESS_USER_PASS="$(gen_pass)" && export WORDPRESS_USER_PASS && log "Generated WORDPRESS_USER_PASS (hidden)"

# Ensure wp-config.php
if [ ! -f /var/www/html/wp-config.php ]; then
  log "Creating wp-config.php"
  as_www "wp config create --skip-check --dbname='${DB_NAME}' --dbuser='${DB_USER}' --dbpass='${DB_PASS}' --dbhost='${DB_HOST}:${DB_PORT}' --path=/var/www/html --allow-root"
fi

# Install core if needed
if ! as_www "wp core is-installed --path=/var/www/html --allow-root" >/dev/null 2>&1; then
  log "Installing WordPress core at ${WORDPRESS_SITE_URL}"
  as_www "wp core install --url='${WORDPRESS_SITE_URL}' --title='${WORDPRESS_SITE_TITLE}' --admin_user='${WORDPRESS_ADMIN_USER}' --admin_password='${WORDPRESS_ADMIN_PASS}' --admin_email='${WORDPRESS_ADMIN_EMAIL}' --path=/var/www/html --allow-root"
else
  log "WordPress core already installed"
fi

# Ensure admin user (update password/email if exists)
if as_www "wp user get '${WORDPRESS_ADMIN_USER}' --path=/var/www/html --allow-root" >/dev/null 2>&1; then
  log "Admin user '${WORDPRESS_ADMIN_USER}' exists; updating password/email"
  as_www "wp user update '${WORDPRESS_ADMIN_USER}' --user_pass='${WORDPRESS_ADMIN_PASS}' --user_email='${WORDPRESS_ADMIN_EMAIL}' --path=/var/www/html --allow-root"
else
  log "Creating admin user '${WORDPRESS_ADMIN_USER}'"
  as_www "wp user create '${WORDPRESS_ADMIN_USER}' '${WORDPRESS_ADMIN_EMAIL}' --role=administrator --user_pass='${WORDPRESS_ADMIN_PASS}' --path=/var/www/html --allow-root"
fi

# Ensure common user
if as_www "wp user get '${WORDPRESS_USER}' --path=/var/www/html --allow-root" >/dev/null 2>&1; then
  log "User '${WORDPRESS_USER}' exists; updating password/email/role=${WORDPRESS_USER_ROLE}"
  as_www "wp user update '${WORDPRESS_USER}' --user_pass='${WORDPRESS_USER_PASS}' --user_email='${WORDPRESS_USER_EMAIL}' --role='${WORDPRESS_USER_ROLE}' --path=/var/www/html --allow-root"
else
  log "Creating user '${WORDPRESS_USER}' with role='${WORDPRESS_USER_ROLE}'"
  as_www "wp user create '${WORDPRESS_USER}' '${WORDPRESS_USER_EMAIL}' --role='${WORDPRESS_USER_ROLE}' --user_pass='${WORDPRESS_USER_PASS}' --path=/var/www/html --allow-root"
fi

log "Provision complete. Starting php-fpm on port ${WORDPRESS_PORT}"
exec "$PHP_FPM_BIN" -F
