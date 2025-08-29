#!/bin/sh
set -e

# ============================================================================== 
# WordPress container entrypoint
# Order of execution:
# [0] Helpers & runtime checks
# [1] PHP-FPM pool configuration
# [2] Environment (Redis & Database)
# [3] WordPress files & permissions
# [4] Database wait (MariaDB/MySQL)
# [5] WP-CLI bootstrap
# [6] Generate credentials
# [7] Create wp-config.php
# [8] Configure Redis constants
# [9] Install WordPress core
# [10] Language & locale
# [11] Users (admin & common)
# [12] Redis Object Cache plugin
# [13] Start php-fpm
# ==============================================================================

# [0] Helpers & runtime checks
# ---------------------------
# Logging helper
log() {
  printf "[wordpress-setup][%s] %s\n" "$(date -u +"%Y-%m-%dT%H:%M:%SZ")" "$*" >&2
}

# Run a command as www-data user
as_www() { su -s /bin/sh -c "$*" www-data; }

# Detect php-fpm binary
PHP_FPM_BIN="$(command -v php-fpm || command -v php-fpm8.2 || true)"
if [ -z "$PHP_FPM_BIN" ]; then
  log "php-fpm binary not found"
  exit 1
fi

# [1] PHP-FPM pool configuration
# ------------------------------
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

# [2] Environment – Redis (Object Cache)
# --------------------------------------
REDIS_HOST="${WORDPRESS_REDIS_HOST:-}"
REDIS_PORT="${WORDPRESS_REDIS_PORT:-6379}"
REDIS_PASS="${WORDPRESS_REDIS_PASS:-}"

if [ -n "$REDIS_HOST" ]; then
  log "Redis enabled: host='${REDIS_HOST}', port=${REDIS_PORT}"
else
  log "Redis not configured (set WORDPRESS_REDIS_HOST to enable)."
fi

# [2] Environment – Database
# --------------------------
DB_HOST="${WORDPRESS_DB_HOST}"
DB_PORT="${WORDPRESS_DB_PORT}"
DB_NAME="${WORDPRESS_DB_NAME}"
DB_USER="${WORDPRESS_DB_USER}"
DB_PASS="${WORDPRESS_DB_PASSWORD}"

# [3] WordPress files & permissions
# ---------------------------------
mkdir -p /var/www/html
if [ ! -e /var/www/html/wp-settings.php ] || [ ! -d /var/www/html/wp-includes ]; then
  log "Populating WordPress core into /var/www/html (missing wp-includes/wp-settings.php)"
  rm -f /var/www/html/index.nginx-debian.html 2>/dev/null || true
  cp -a /usr/src/wordpress/. /var/www/html/
fi
chown -R www-data:www-data /var/www/html

# [4] Database wait (MariaDB/MySQL)
# ---------------------------------
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

# [5] WP-CLI bootstrap
# --------------------
# Install wp-cli if missing
if ! command -v wp >/dev/null 2>&1; then
  log "wp-cli not found; installing locally"
  curl -fsSL https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar -o /usr/local/bin/wp
  chmod +x /usr/local/bin/wp
fi

# [6] Generate credentials
# ------------------------
# Generate passwords if blank
gen_pass() { tr -dc 'A-Za-z0-9!@#%^&*' </dev/urandom | head -c 20; }
[ -z "${WORDPRESS_ADMIN_PASS:-}" ] && WORDPRESS_ADMIN_PASS="$(gen_pass)" && export WORDPRESS_ADMIN_PASS && log "Generated WORDPRESS_ADMIN_PASS (hidden)"
[ -z "${WORDPRESS_USER_PASS:-}" ] && WORDPRESS_USER_PASS="$(gen_pass)" && export WORDPRESS_USER_PASS && log "Generated WORDPRESS_USER_PASS (hidden)"

# [7] Create wp-config.php
# ------------------------
if [ ! -f /var/www/html/wp-config.php ]; then
  log "Creating wp-config.php"
  as_www "wp config create --skip-check --dbname='${DB_NAME}' --dbuser='${DB_USER}' --dbpass='${DB_PASS}' --dbhost='${DB_HOST}:${DB_PORT}' --path=/var/www/html --allow-root"
fi

# [8] Configure Redis constants (idempotent)
# ------------------------------------------
if [ -n "$REDIS_HOST" ]; then
  as_www "wp config set WP_CACHE true --type=constant --raw --path=/var/www/html --allow-root" || true
  as_www "wp config set WP_REDIS_HOST '${REDIS_HOST:-redis}' --type=constant --path=/var/www/html --allow-root" || true
  as_www "wp config set WP_REDIS_PORT ${REDIS_PORT} --type=constant --raw --path=/var/www/html --allow-root" || true
  if [ -n "$REDIS_PASS" ]; then
    as_www "wp config set WP_REDIS_PASSWORD '${REDIS_PASS}' --type=constant --path=/var/www/html --allow-root" || true
  fi
fi

# [9] Install WordPress core (idempotent)
# ---------------------------------------
if ! as_www "wp core is-installed --path=/var/www/html --allow-root" >/dev/null 2>&1; then
  log "Installing WordPress core at ${WORDPRESS_SITE_URL}"
  log "Data: title='${WORDPRESS_SITE_TITLE}', admin_user='${WORDPRESS_ADMIN_USER}', admin_email='${WORDPRESS_ADMIN_EMAIL}', locale='${WORDPRESS_LOCALE}'"
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

# [10] Language & locale
# ----------------------
if [ -n "${WORDPRESS_LOCALE:-}" ]; then
  log "Ensuring core language '${WORDPRESS_LOCALE}' is installed and active"
  # Try to install if not present (don't fail the script if it doesn't exist upstream)
  if ! as_www "wp language core is-installed '${WORDPRESS_LOCALE}' --path=/var/www/html --allow-root" >/dev/null 2>&1; then
    as_www "wp language core install '${WORDPRESS_LOCALE}' --path=/var/www/html --allow-root" || true
  fi

  # Proceed only if it's really installed; otherwise, skip gracefully
  if as_www "wp language core is-installed '${WORDPRESS_LOCALE}' --path=/var/www/html --allow-root" >/dev/null 2>&1; then
    as_www "wp site switch-language '${WORDPRESS_LOCALE}' --path=/var/www/html --allow-root"
    as_www "wp option update WPLANG '${WORDPRESS_LOCALE}' --path=/var/www/html --allow-root"
    as_www "printf 'Current WPLANG='; wp option get WPLANG --path=/var/www/html --allow-root"
    # Also set the admin user's dashboard language to match
    as_www "wp user meta update '${WORDPRESS_ADMIN_USER}' locale '${WORDPRESS_LOCALE}' --path=/var/www/html --allow-root" || true
    if [ -n "${WORDPRESS_USER:-}" ]; then
      as_www "wp user meta update '${WORDPRESS_USER}' locale '${WORDPRESS_LOCALE}' --path=/var/www/html --allow-root" || true
    fi
  else
    log "Language '${WORDPRESS_LOCALE}' not available; skipping language switch and keeping current site language."
  fi
fi

# [11] Users (admin & common)
# ---------------------------
# Ensure admin user (update password/email if exists)
if as_www "wp user get '${WORDPRESS_ADMIN_USER}' --path=/var/www/html --allow-root" >/dev/null 2>&1; then
  log "Admin user '${WORDPRESS_ADMIN_USER}' exists; updating password/email"
  as_www "wp user update '${WORDPRESS_ADMIN_USER}' --user_pass='${WORDPRESS_ADMIN_PASS}' --user_email='${WORDPRESS_ADMIN_EMAIL}' --skip-email --path=/var/www/html --allow-root"
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

# [12] Redis Object Cache plugin (install & enable)
# -------------------------------------------------
if [ -n "$REDIS_HOST" ]; then
  log "Configuring Redis Object Cache (best-effort)"

  # Ensure plugin is installed (do not fail the script if it can't be installed)
  if ! as_www "wp plugin is-installed redis-cache --path=/var/www/html --allow-root" >/dev/null 2>&1; then
    if as_www "wp plugin install redis-cache --path=/var/www/html --allow-root" >/dev/null 2>&1; then
      log "Installed 'redis-cache' plugin"
    else
      log "WARNING: could not install 'redis-cache' plugin; continuing without Redis cache"
    fi
  fi

  # Try to activate plugin (non-fatal)
  if as_www "wp plugin activate redis-cache --path=/var/www/html --allow-root" >/dev/null 2>&1; then
    log "Plugin 'redis-cache' is active"
  else
    log "WARNING: could not activate 'redis-cache' plugin; continuing"
  fi

  # Try to enable object cache. If Redis is down, this may fail — that's OK.
  if as_www "wp redis enable --path=/var/www/html --allow-root" >/dev/null 2>&1; then
    log "Redis object cache enabled"
  else
    log "WARNING: Redis not enabled (likely unreachable or plugin inactive). Site will run without object cache."
  fi
fi

# [13] Start php-fpm
# ------------------
log "Provision complete. Starting php-fpm on port ${WORDPRESS_PORT}"
exec "$PHP_FPM_BIN" -F
