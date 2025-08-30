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
SECRETS_DIR="../secrets"

write_secret() {
  mkdir -p "$(dirname "$1")"
  ( umask 077; printf "%s" "$2" > "$1" )
}

write_credentials_file() {
  mkdir -p "$(dirname "$1")"
  ( umask 077; cat > "$1" )
}

 # Si existe, salir
if [ -f "$ENV_FILE" ]; then
  echo "${YELL}⚠️  The file $ENV_FILE already exists.${RESET}"
  exit 0
fi

echo "${CYAN}==> Creating enviroments and secrets...${RESET}"

ask() {
  local prompt=$1
  local default=$2
  read -r -p "$prompt [$default]: " var
  echo "${var:-$default}"
}

echo "\n${BOLD}${MAGENTA}########################################${RESET}"
echo "${BOLD}${MAGENTA}###        App configuration        ###${RESET}"
echo "${BOLD}${MAGENTA}########################################${RESET}\n"
LOGIN=$(whoami)
echo "You are logged in as: $LOGIN"
APP_ENV=$(ask "Applicaction enviroment" "development")

if [ "$(uname)" = "Darwin" ]; then
  HOST_DATA_DIR="/Users/$LOGIN/data"
else
  HOST_DATA_DIR="/home/$LOGIN/data"
fi

echo "\n${BOLD}${MAGENTA}########################################${RESET}"
echo "${BOLD}${MAGENTA}###   Services configuration        ###${RESET}"
echo "${BOLD}${MAGENTA}########################################${RESET}\n"

# Services
MARIADB_IMAGE=$(ask "MariaDB image" "mariadb-local:1.0.0")
ADMINER_IMAGE=$(ask "Adminer image" "adminer-local:1.0.0")
NGINX_IMAGE=$(ask "Nginx image" "nginx-local:1.0.0")
WORDPRESS_IMAGE=$(ask "WordPress image" "wordpress-local:1.0.0")
FTP_IMAGE=$(ask "FTP image" "ftp-local:1.0.0")
WEBSITE_IMAGE=$(ask "Website image" "website-local:1.0.0")
REDIS_IMAGE=$(ask "Redis image" "redis-local:1.0.0")

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
DEFAULT_DOMAIN="${LOGIN}.42.fr"
DOMAIN=$(ask "Public domain (for TLS/server_name)" "$DEFAULT_DOMAIN")
UPSTREAM="http://adminer:80"
GENERATE_SELF_SIGNED=$(ask "Generate self-signed certificates? (true/false)" "true")

echo "\n${BOLD}${MAGENTA}########################################${RESET}"
echo "${BOLD}${MAGENTA}###   WordPress configuration       ###${RESET}"
echo "${BOLD}${MAGENTA}########################################${RESET}\n"

# WordPress configuration
echo "${BOLD}${CYAN}=== WordPress volume ===${RESET}"
WORDPRESS_DB_VOLUME=$(ask "DB volume name (WordPress DB)" "wordpress_db")
WORDPRESS_DATA_VOLUME=$(ask "Site volume name (WordPress files)" "wordpress_data")

echo "\n${BOLD}${CYAN}=== WordPress site ===${RESET}"
# Lista de algunos locales comunes para WordPress:
# en_US (Inglés EE.UU.), es_ES (Español España), fr_FR (Francés Francia), de_DE (Alemán Alemania),
# it_IT (Italiano Italia), pt_PT (Portugués Portugal), ru_RU (Ruso), ja_JP (Japonés), zh_CN (Chino simplificado),
# nl_NL (Neerlandés), pl_PL (Polaco), tr_TR (Turco), sv_SE (Sueco), fi_FI (Finlandés), el_GR (Griego)
WORDPRESS_LOCALE=$(ask "WordPress locale (language/region:en_US,es_ES,fr_FR,de_DE,it_IT,pt_PT,ru_RU,ja_JP,zh_CN,nl_NL,pl_PL,tr_TR,sv_SE,fi_FI,el_GR)" "en_US")
WORDPRESS_SITE_URL="https://$DOMAIN/"
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
echo "${BOLD}${MAGENTA}###   FTP configuration              ###${RESET}"
echo "${BOLD}${MAGENTA}########################################${RESET}\n"

FTP_USER=$(ask "FTP user" "$LOGIN")
FTP_PASSWORD=$(ask "FTP password" "1234")
FTP_HOST=$DOMAIN
FTP_PORT=21
FTP_PASV_ADDRESS=$DOMAIN
FTP_TLS_ENABLE=$(ask "Enable FTPS (TLS)? (true/false)" "false")

echo "\n${BOLD}${MAGENTA}########################################${RESET}"
echo "${BOLD}${MAGENTA}###   Redis configuration            ###${RESET}"
echo "${BOLD}${MAGENTA}########################################${RESET}\n"

REDIS_HOST=redis
REDIS_PORT=$(ask "Redis port" "6379")
REDIS_PASS=$(ask "Redis password" "redispass")
REDIS_DATA_VOLUME=$(ask "Redis data volume name" "redis_data")

DB_DIR="$HOST_DATA_DIR/$WORDPRESS_DB_VOLUME"
SITE_DIR="$HOST_DATA_DIR/$WORDPRESS_DATA_VOLUME"
REDIS_DIR="$HOST_DATA_DIR/$REDIS_DATA_VOLUME"

echo "\n${BOLD}${MAGENTA}########################################${RESET}"
echo "${BOLD}${MAGENTA}###   Networking and volumes        ###${RESET}"
echo "${BOLD}${MAGENTA}########################################${RESET}\n"

# Networking and volumes
STACK_NETWORK=$(ask "Network name" "inception_net")

echo "\n${CYAN}Creating host directories for volumes in $HOST_DATA_DIR...${RESET}"
mkdir -p "$DB_DIR" "$SITE_DIR" "$REDIS_DIR"

echo "${CYAN}Creating $ENV_FILE...${RESET}"
cat > "$ENV_FILE" <<EOL
# App configuration
APP_ENV=$APP_ENV
LOGIN=$LOGIN
HOST_DATA_DIR=$HOST_DATA_DIR

# Services
MARIADB_IMAGE=$MARIADB_IMAGE
ADMINER_IMAGE=$ADMINER_IMAGE
NGINX_IMAGE=$NGINX_IMAGE
WORDPRESS_IMAGE=$WORDPRESS_IMAGE
FTP_IMAGE=$FTP_IMAGE
WEBSITE_IMAGE=$WEBSITE_IMAGE
REDIS_IMAGE=$REDIS_IMAGE

# Database credentials
DATABASE_SERVER=$DATABASE_SERVER
MARIADB_DATABASE=$MARIADB_DATABASE
MARIADB_USER=$MARIADB_USER
MARIADB_PORT=$MARIADB_PORT

# Adminer configuration
ADMINER_DEFAULT_SERVER=${DATABASE_SERVER}:${MARIADB_PORT}

# Nginx configuration
DOMAIN=$DOMAIN
UPSTREAM=$UPSTREAM
GENERATE_SELF_SIGNED=$GENERATE_SELF_SIGNED

# WordPress configuration
WORDPRESS_DB_HOST=${DATABASE_SERVER}
WORDPRESS_DB_NAME=${MARIADB_DATABASE}
WORDPRESS_DB_USER=${MARIADB_USER}
WORDPRESS_DB_PORT=${MARIADB_PORT}

WORDPRESS_DB_VOLUME=$WORDPRESS_DB_VOLUME
WORDPRESS_DATA_VOLUME=$WORDPRESS_DATA_VOLUME
WORDPRESS_PORT=$WORDPRESS_PORT

WORDPRESS_SITE_URL=$WORDPRESS_SITE_URL
WORDPRESS_SITE_TITLE=$WORDPRESS_SITE_TITLE
WORDPRESS_LOCALE=$WORDPRESS_LOCALE

WORDPRESS_REDIS_HOST=${REDIS_HOST}
WORDPRESS_REDIS_PORT=${REDIS_PORT}

# FTP configuration
FTP_HOST=$FTP_HOST
FTP_PORT=$FTP_PORT
FTP_PASV_ADDRESS=$FTP_PASV_ADDRESS
FTP_TLS_ENABLE=$FTP_TLS_ENABLE

# Redis configuration
REDIS_HOST=$REDIS_HOST
REDIS_PORT=$REDIS_PORT
REDIS_DATA_VOLUME=$REDIS_DATA_VOLUME

# Networking
STACK_NETWORK=$STACK_NETWORK

EOL

echo "${CYAN}Creating secrets...${RESET}"
write_secret "${SECRETS_DIR}/db_password.txt"        "$MARIADB_PASSWORD"
write_secret "${SECRETS_DIR}/db_root_password.txt"   "$MARIADB_ROOT_PASSWORD"
write_secret "${SECRETS_DIR}/redis_password.txt"     "$REDIS_PASS"

write_credentials_file "${SECRETS_DIR}/wp_admin_credentials.txt" <<EOF
WORDPRESS_ADMIN_USER=${WORDPRESS_ADMIN_USER}
WORDPRESS_ADMIN_PASS=${WORDPRESS_ADMIN_PASS}
WORDPRESS_ADMIN_EMAIL=${WORDPRESS_ADMIN_EMAIL}
EOF

write_credentials_file "${SECRETS_DIR}/wp_user_credentials.txt" <<EOF
WORDPRESS_USER=${WORDPRESS_USER}
WORDPRESS_USER_PASS=${WORDPRESS_USER_PASS}
WORDPRESS_USER_EMAIL=${WORDPRESS_USER_EMAIL}
EOF

write_credentials_file "${SECRETS_DIR}/ftp_credentials.txt" <<EOF
FTP_USER=${FTP_USER}
FTP_PASSWORD=${FTP_PASSWORD}
EOF

echo "${GREEN}✅ Files created successfully.${RESET}\n"