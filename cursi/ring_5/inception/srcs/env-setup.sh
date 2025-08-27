#!/usr/bin/env sh

set -e

# ANSI color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELL='\033[1;33m'
CYAN='\033[0;36m'
MAGENTA='\033[1;35m'
RESET='\033[0m'
BOLD='\033[1m'

ENV_FILE=".env"

 # Si existe, salir
if [ -f "$ENV_FILE" ]; then
  echo "${YELL}⚠️  El archivo $ENV_FILE ya existe.${RESET}"
  exit 0
fi

echo "${CYAN}==> Creando archivo $ENV_FILE...${RESET}"

ask() {
  local prompt=$1
  local default=$2
  read -r -p "$prompt [$default]: " var
  echo "${var:-$default}"
}

echo "\n${BOLD}${MAGENTA}########################################${RESET}"
echo "${BOLD}${MAGENTA}###   Services configuration        ###${RESET}"
echo "${BOLD}${MAGENTA}########################################${RESET}\n"

# Services
MARIADB_IMAGE=$(ask "MariaDB image" "mariadb-local:bookworm")
ADMINER_IMAGE=$(ask "Adminer image" "adminer-local:bookworm")
NGINX_IMAGE=$(ask "Nginx image" "nginx-local:bookworm")
WORDPRESS_IMAGE=$(ask "WordPress image" "wordpress-local:bookworm")

echo "\n${BOLD}${MAGENTA}########################################${RESET}"
echo "${BOLD}${MAGENTA}###   Database configuration        ###${RESET}"
echo "${BOLD}${MAGENTA}########################################${RESET}\n"

# Database credentials
DATABASE_SERVER=mariadb
MARIADB_DATABASE=$(ask "Database name" "appdb")
MARIADB_USER=$(ask "Database user" "svillad")
MARIADB_PASSWORD=$(ask "Database password" "12345678")
MARIADB_PORT=$(ask "Database port" "3306")
MARIADB_ROOT_PASSWORD=$(ask "Database root password" "rootpass")

echo "\n${BOLD}${MAGENTA}########################################${RESET}"
echo "${BOLD}${MAGENTA}###   Nginx configuration           ###${RESET}"
echo "${BOLD}${MAGENTA}########################################${RESET}\n"

# Nginx configuration
USER42=$(whoami)
DEFAULT_DOMAIN="${USER42}.42.fr"
DOMAIN=$(ask "Public domain (for TLS/server_name)" "$DEFAULT_DOMAIN")
UPSTREAM="http://adminer:80"
NGINX_PORT=$(ask "Nginx port" "443")
GENERATE_SELF_SIGNED=$(ask "Generate self-signed certificates? (true/false)" "false")

echo "\n${BOLD}${MAGENTA}########################################${RESET}"
echo "${BOLD}${MAGENTA}###   WordPress configuration       ###${RESET}"
echo "${BOLD}${MAGENTA}########################################${RESET}\n"

# WordPress configuration
echo "${BOLD}${CYAN}=== WordPress volume ===${RESET}"
WORDPRESS_DB_VOLUME=$(ask "DB volume name (WordPress DB)" "wordpress_db")
WORDPRESS_DATA_VOLUME=$(ask "Site volume name (WordPress files)" "wordpress_data")

echo "\n${BOLD}${CYAN}=== WordPress site ===${RESET}"
WORDPRESS_SITE_URL=$(ask "WordPress site URL" "https://$DOMAIN/")
WORDPRESS_SITE_TITLE=$(ask "WordPress site title" "My Site")
WORDPRESS_PORT=$(ask "WordPress port" "9000")

echo "\n${BOLD}${CYAN}=== WordPress admin ===${RESET}"
WORDPRESS_ADMIN_USER=$(ask "WordPress admin user" "svillad")
WORDPRESS_ADMIN_EMAIL=$(ask "WordPress admin email" "svillad@example.com")
WORDPRESS_ADMIN_PASS=$(ask "WordPress admin password" "1234")

echo "\n${BOLD}${CYAN}=== WordPress user ===${RESET}"
WORDPRESS_USER=$(ask "WordPress user" "jesi")
WORDPRESS_USER_EMAIL=$(ask "WordPress user email" "jesi@example.com")
WORDPRESS_USER_PASS=$(ask "WordPress user password" "4321")

echo "\n${BOLD}${MAGENTA}########################################${RESET}"
echo "${BOLD}${MAGENTA}###   Networking and volumes        ###${RESET}"
echo "${BOLD}${MAGENTA}########################################${RESET}\n"

# Networking and volumes
STACK_NETWORK=$(ask "Network name" "inception_net")

cat > "$ENV_FILE" <<EOL
# Services
MARIADB_IMAGE=$MARIADB_IMAGE
ADMINER_IMAGE=$ADMINER_IMAGE
NGINX_IMAGE=$NGINX_IMAGE
WORDPRESS_IMAGE=$WORDPRESS_IMAGE

# Database credentials
DATABASE_SERVER=$DATABASE_SERVER
MARIADB_DATABASE=$MARIADB_DATABASE
MARIADB_USER=$MARIADB_USER
MARIADB_PASSWORD=$MARIADB_PASSWORD
MARIADB_PORT=$MARIADB_PORT
MARIADB_ROOT_PASSWORD=$MARIADB_ROOT_PASSWORD

# Nginx configuration
DOMAIN=$DOMAIN
UPSTREAM=$UPSTREAM
NGINX_PORT=$NGINX_PORT
GENERATE_SELF_SIGNED=$GENERATE_SELF_SIGNED

# WordPress configuration
WORDPRESS_DB_VOLUME=$WORDPRESS_DB_VOLUME
WORDPRESS_DATA_VOLUME=$WORDPRESS_DATA_VOLUME
WORDPRESS_PORT=$WORDPRESS_PORT

WORDPRESS_SITE_URL=$WORDPRESS_SITE_URL
WORDPRESS_SITE_TITLE=$WORDPRESS_SITE_TITLE

WORDPRESS_ADMIN_USER=$WORDPRESS_ADMIN_USER
WORDPRESS_ADMIN_EMAIL=$WORDPRESS_ADMIN_EMAIL
WORDPRESS_ADMIN_PASS=$WORDPRESS_ADMIN_PASS

WORDPRESS_USER=$WORDPRESS_USER
WORDPRESS_USER_EMAIL=$WORDPRESS_USER_EMAIL
WORDPRESS_USER_PASS=$WORDPRESS_USER_PASS

# Networking
STACK_NETWORK=$STACK_NETWORK

EOL

echo "${GREEN}✅ Archivo $ENV_FILE creado exitosamente.${RESET}"