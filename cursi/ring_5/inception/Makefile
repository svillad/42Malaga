# ---------------------------------------------
# Makefile — Inception (Docker)
# ---------------------------------------------
# Usage:
#   make <target>
#
# Project layout:
#   srcs/docker-compose.yml
#
# ---------------------------------------------

# Detect compose CLI: prefer docker-compose if present, else docker compose
COMPOSE := $(shell command -v docker-compose >/dev/null 2>&1 && echo docker-compose || echo docker compose)

# Paths
COMPOSE_DIR := srcs
COMPOSE_FILE := $(COMPOSE_DIR)/docker-compose.yml
ENV_FILE := $(COMPOSE_DIR)/.env

# Read values from .env
ifneq ("$(wildcard $(ENV_FILE))","")
  WORDPRESS_DB_VOLUME   := $(shell grep -E '^WORDPRESS_DB_VOLUME=' $(ENV_FILE) | cut -d= -f2-)
  WORDPRESS_DATA_VOLUME := $(shell grep -E '^WORDPRESS_DATA_VOLUME=' $(ENV_FILE) | cut -d= -f2-)
  REDIS_DATA_VOLUME     := $(shell grep -E '^REDIS_DATA_VOLUME=' $(ENV_FILE) | cut -d= -f2-)
  STACK_NETWORK   := $(shell grep -E '^STACK_NETWORK='  $(ENV_FILE) | cut -d= -f2-)
  DOMAIN          := $(shell grep -E '^DOMAIN='         $(ENV_FILE) | cut -d= -f2-)
  MARIADB_IMAGE   := $(shell grep -E '^MARIADB_IMAGE='  $(ENV_FILE) | cut -d= -f2-)
  ADMINER_IMAGE   := $(shell grep -E '^ADMINER_IMAGE='  $(ENV_FILE) | cut -d= -f2-)
  NGINX_IMAGE     := $(shell grep -E '^NGINX_IMAGE='    $(ENV_FILE) | cut -d= -f2-)
  WORDPRESS_IMAGE := $(shell grep -E '^WORDPRESS_IMAGE=' $(ENV_FILE) | cut -d= -f2-)
  FTP_IMAGE       := $(shell grep -E '^FTP_IMAGE='      $(ENV_FILE) | cut -d= -f2-)
  WEBSITE_IMAGE   := $(shell grep -E '^WEBSITE_IMAGE='  $(ENV_FILE) | cut -d= -f2-)
  REDIS_IMAGE     := $(shell grep -E '^REDIS_IMAGE='    $(ENV_FILE) | cut -d= -f2-)
  LOGIN           := $(shell grep -E '^LOGIN='          $(ENV_FILE) | cut -d= -f2-)
  FTP_USER        := $(shell grep -E '^FTP_USER='      $(ENV_FILE) | cut -d= -f2-)
  FTP_PORT        := $(shell grep -E '^FTP_PORT='      $(ENV_FILE) | cut -d= -f2-)
  FTP_HOST        := $(shell grep -E '^FTP_HOST='      $(ENV_FILE) | cut -d= -f2-)
endif

# Compose command helper (echo the exact command, run from $(COMPOSE_DIR))
define DC
	@echo "$(CYAN)$(COMPOSE) $(1)$(RESET)"
	@cd $(COMPOSE_DIR) && $(COMPOSE) $(1)
endef

# Generic runner: echo the command then execute it
define RUN
	@echo "$(CYAN)$(1)$(RESET)"
	@$(1)
endef

# Colors
CYAN  := \033[36m
GREEN := \033[32m
YELL  := \033[33m
RED   := \033[31m
RESET := \033[0m

.PHONY: \
	help setup build up up-build start stop restart \
	logs logs-f logs-db logs-adminer logs-nginx logs-wp logs-ftp logs-website logs-redis sh-ftp sh-website sh-redis \
	ps exec-db sh-db sh-adminer sh-nginx sh-wp \
	down down-v clean re reset-wp-db reset-wp-data \
	config url rmi health require-env fclean ensure-dirs

# Ensure .env exists before continuing
require-env:
	@if [ ! -f "$(ENV_FILE)" ]; then \
	  echo "$(RED)$(ENV_FILE) not found. Run 'make setup' first.$(RESET)"; \
	  exit 1; \
	fi

# Ensure host directories for bind mounts exist (macOS vs Linux)
ensure-dirs: require-env
	@echo "$(CYAN)==> Ensuring host directories for volumes exist$(RESET)"
	@bash -lc '\
	  LOGIN_VAL="$(LOGIN)"; \
	  if [ -z "$$LOGIN_VAL" ]; then LOGIN_VAL="$$(grep -E "^LOGIN=" $(ENV_FILE) | cut -d= -f2-)"; fi; \
	  if [ "$$LOGIN_VAL" = "" ]; then echo "$(RED)LOGIN not set in $(ENV_FILE)$(RESET)"; exit 1; fi; \
	  if [ "$$(uname)" = "Darwin" ]; then HOST_DATA_DIR="/Users/$$LOGIN_VAL/data"; else HOST_DATA_DIR="/home/$$LOGIN_VAL/data"; fi; \
	  DB_DIR="$$HOST_DATA_DIR/$(WORDPRESS_DB_VOLUME)"; \
	  SITE_DIR="$$HOST_DATA_DIR/$(WORDPRESS_DATA_VOLUME)"; \
	  REDIS_DIR="$$HOST_DATA_DIR/$(REDIS_DATA_VOLUME)"; \
	  echo "Creating (if not exists): $$DB_DIR"; \
	  echo "Creating (if not exists): $$SITE_DIR"; \
	  echo "Creating (if not exists): $$REDIS_DIR"; \
	  mkdir -p "$$DB_DIR" "$$SITE_DIR" "$$REDIS_DIR"; \
	  echo -e "$(GREEN)OK: host volume directories are present$(RESET)"; \
	'

help:
	@echo ""
	@echo " $(CYAN)MariaDB + Adminer stack$(RESET)"
	@echo " $(YELL)Targets:$(RESET)"
	@echo "   $(CYAN)Setup & Build$(RESET)"
	@echo "   make setup       - Create .env if missing and build images"
	@echo "   make build       - Build images"
	@echo "   make up          - Start stack (detached)"
	@echo "   make up-build    - Build and start"
	@echo "   make start       - Start existing containers"
	@echo "   make stop        - Stop containers"
	@echo "   make restart     - Stop then start containers"
	@echo "   $(CYAN)Logs$(RESET)"
	@echo "   make logs        - Show logs"
	@echo "   make logs-f      - Follow logs"
	@echo "   make logs-db      - Show logs of MariaDB service"
	@echo "   make logs-adminer - Show logs of Adminer service"
	@echo "   make logs-nginx   - Show logs of Nginx service"
	@echo "   make logs-wp      - Show logs of WordPress service"
	@echo "   make logs-ftp     - Show logs of FTP service"
	@echo "   make logs-website - Show logs of Website service"
	@echo "   make logs-redis   - Show logs of Redis service"
	@echo "   $(CYAN)Service Management$(RESET)"
	@echo "   make ps           - List services"
	@echo "   make exec-db      - Open mysql client inside DB container"
	@echo "   make sh-db        - /bin/sh in DB container"
	@echo "   make sh-adminer   - /bin/sh in Adminer container"
	@echo "   make sh-nginx     - /bin/sh in Nginx container"
	@echo "   make sh-wp        - /bin/sh in WordPress container"
	@echo "   make sh-ftp       - /bin/sh in FTP container"
	@echo "   make sh-website   - /bin/sh in Website container"
	@echo "   make sh-redis     - /bin/sh in Redis container"
	@echo "   $(CYAN)Cleanup & Reset$(RESET)"
	@echo "   make down        - Stop and remove containers + default network"
	@echo "   make down-v      - Down + remove named volumes (⚠️ deletes data)"
	@echo "   make reset-wp-db    - Remove WordPress DB volume only (⚠️ deletes data)"
	@echo "   make reset-wp-data  - Remove WordPress site files volume only (⚠️ deletes data)"
	@echo "   make clean       - Prune dangling images/volumes/networks"
	@echo "   make re          - Rebuild and restart"
	@echo "   make config      - Show resolved docker compose config"
	@echo "   make url         - Print useful URLs (Adminer, Website) and FTP client settings"
	@echo "   make rmi         - Remove built images for all services"
	@echo "   make health      - Check Nginx health endpoint (/healthz)"
	@echo "   make fclean      - Clean everything (containers, volumes, images, .env) (⚠️ deletes data)"

# Create .env if missing and build images
setup:
	@echo "$(CYAN)==> Setup$(RESET)"
	@if [ ! -f "$(ENV_FILE)" ]; then \
			echo "$(YELL)Creating $(ENV_FILE) and secrets/*$(RESET)"; \
			cd $(COMPOSE_DIR) && chmod +x ./app-setup.sh && ./app-setup.sh \
		else \
			echo "$(GREEN)$(ENV_FILE) exists$(RESET)"; \
		fi
	$(call DC,build)

# Build images
build:
	@$(MAKE) require-env
	@echo "$(CYAN)==> Build$(RESET)"
	$(call DC,build)

# Start stack (detached)
up:
	@$(MAKE) require-env
	@$(MAKE) --no-print-directory ensure-dirs
	@echo "$(CYAN)==> Up (detached)$(RESET)"
	$(call DC,up -d)
	@$(MAKE) --no-print-directory url

# Build + up
up-build:
	@$(MAKE) require-env
	@$(MAKE) --no-print-directory ensure-dirs
	@echo "$(CYAN)==> Up (build + detached)$(RESET)"
	$(call DC,up -d --build)
	@$(MAKE) --no-print-directory url

# Start existing containers
start:
	@$(MAKE) require-env ensure-dirs
	@echo "$(CYAN)==> Start$(RESET)"
	$(call DC,start)

# Stop containers
stop:
	@echo "$(CYAN)==> Stop$(RESET)"
	$(call DC,stop)

# Restart containers
restart:
	@echo "$(CYAN)==> Restart$(RESET)"
	$(call DC,stop)
	$(call DC,start)

# Logs
logs:
	@echo "$(CYAN)==> Logs$(RESET)"
	$(call DC,logs)

# Follow logs
logs-f:
	@echo "$(CYAN)==> Logs (follow)$(RESET)"
	$(call DC,logs -f)

# Logs per service
logs-db:
	@echo "$(CYAN)==> Logs (MariaDB)$(RESET)"
	$(call DC,logs mariadb)

logs-adminer:
	@echo "$(CYAN)==> Logs (Adminer)$(RESET)"
	$(call DC,logs adminer)

logs-nginx:
	@echo "$(CYAN)==> Logs (Nginx)$(RESET)"
	$(call DC,logs nginx)

logs-wp:
	@echo "$(CYAN)==> Logs (WordPress)$(RESET)"
	$(call DC,logs wordpress)

# Logs (FTP)
logs-ftp:
	@echo "$(CYAN)==> Logs (FTP)$(RESET)"
	$(call DC,logs ftp-server)

# Logs (Website)
logs-website:
	@echo "$(CYAN)==> Logs (Website)$(RESET)"
	$(call DC,logs website)

# Logs (Redis)
logs-redis:
	@echo "$(CYAN)==> Logs (Redis)$(RESET)"
	$(call DC,logs redis)

# List services
ps:
	@echo "$(CYAN)==> Services status$(RESET)"
	$(call DC,ps)

# Exec into DB (MariaDB client)
exec-db:
	@echo "$(CYAN)==> MariaDB shell (root via unix socket)$(RESET)"
	$(call DC,exec mariadb mariadb -uroot -p)

# /bin/sh inside DB container
sh-db:
	@echo "$(CYAN)==> Shell (MariaDB)$(RESET)"
	$(call DC,exec mariadb /bin/sh)

# /bin/sh inside Adminer container
sh-adminer:
	@echo "$(CYAN)==> Shell (Adminer)$(RESET)"
	$(call DC,exec adminer /bin/sh)

# /bin/sh inside Nginx container
sh-nginx:
	@echo "$(CYAN)==> Shell (Nginx)$(RESET)"
	$(call DC,exec nginx /bin/sh)

# /bin/sh inside WordPress container
sh-wp:
	@echo "$(CYAN)==> Shell (WordPress)$(RESET)"
	$(call DC,exec wordpress /bin/sh)

# /bin/sh inside FTP container
sh-ftp:
	@echo "$(CYAN)==> Shell (FTP)$(RESET)"
	$(call DC,exec ftp-server /bin/sh)

# /bin/sh inside Website container
sh-website:
	@echo "$(CYAN)==> Shell (Website)$(RESET)"
	$(call DC,exec website /bin/sh)

# /bin/sh inside Redis container
sh-redis:
	@echo "$(CYAN)==> Shell (Redis)$(RESET)"
	$(call DC,exec redis /bin/sh)

# Down (remove containers + default network)
down:
	@echo "$(CYAN)==> Down$(RESET)"
	$(call DC,down)

# Down + remove named volumes (⚠️ destructive)
down-v:
	@echo "$(RED)==> Down + remove volumes (DESTRUCTIVE)$(RESET)"
	$(call DC,down -v)

# Remove ONLY the WordPress DB data volume (⚠️ destructive)
reset-wp-db:
	@if [ -z "$(WORDPRESS_DB_VOLUME)" ]; then \
	  echo "$(RED)WORDPRESS_DB_VOLUME is not set (check $(ENV_FILE))$(RESET)"; \
	  exit 1; \
	fi
	@echo "$(RED)==> Removing volume $(WORDPRESS_DB_VOLUME) (DESTRUCTIVE)$(RESET)"
	$(call RUN,docker volume rm -f "$(WORDPRESS_DB_VOLUME)" || true)

# Remove ONLY the WordPress site data volume (⚠️ destructive)
reset-wp-data:
	@if [ -z "$(WORDPRESS_DATA_VOLUME)" ]; then \
	  echo "$(RED)WORDPRESS_DATA_VOLUME is not set (check $(ENV_FILE))$(RESET)"; \
	  exit 1; \
	fi
	@echo "$(RED)==> Removing volume $(WORDPRESS_DATA_VOLUME) (DESTRUCTIVE)$(RESET)"
	$(call RUN,docker volume rm -f "$(WORDPRESS_DATA_VOLUME)" || true)

# Clean dangling resources
clean:
	@echo "$(CYAN)==> Docker system prune (dangling)$(RESET)"
	$(call RUN,docker image prune -f)
	$(call RUN,docker volume prune -f)
	$(call RUN,docker network prune -f)

# Rebuild & restart
re: down build up

# Show effective compose config
config:
	@echo "$(CYAN)==> Compose config$(RESET)"
	$(call DC,config)

# Print Adminer URL
url:
	@echo "$(CYAN)==> Useful URLs$(RESET)"
ifneq ($(strip $(DOMAIN)),)
	@echo "$(GREEN)Home page:     https://$(DOMAIN)/$(RESET)"
	@echo "$(GREEN)Login page:    https://$(DOMAIN)/wp-login.php$(RESET)"
	@echo "$(GREEN)Post page:     https://$(DOMAIN)/?page_id=1$(RESET)"
	@echo "$(GREEN)Static page:   https://$(DOMAIN)/me$(RESET)"
	@echo "$(GREEN)Database page: https://$(DOMAIN)/adminer$(RESET)"
	@echo ""
	@echo "$(CYAN)==> FTP settings$(RESET)"
	@echo "$(GREEN)Host:          $$( [ -n \"$(FTP_HOST)\" ] && echo $(FTP_HOST) || echo $(DOMAIN) )$(RESET)"
	@echo "$(GREEN)Port:          $$( [ -n \"$(FTP_PORT)\" ] && echo $(FTP_PORT) || echo 21 )$(RESET)"
	@echo "$(GREEN)TLS enable:    $$( [ \"$(FTP_TLS_ENABLE)\" = \"true\" ] && echo true || echo false )$(RESET)"
else
	@echo "$(YELL)Set environment variables in $(ENV_FILE). Or run 'make setup' first.$(RESET)"
endif

# Remove built images for services
rmi:
	@echo "$(RED)==> Removing service images (if exist)$(RESET)"
	$(call RUN,docker rmi -f $(MARIADB_IMAGE) || true)
	$(call RUN,docker rmi -f $(ADMINER_IMAGE) || true)
	$(call RUN,docker rmi -f $(NGINX_IMAGE) || true)
	$(call RUN,docker rmi -f $(WORDPRESS_IMAGE) || true)
	$(call RUN,docker rmi -f $(FTP_IMAGE) || true)
	$(call RUN,docker rmi -f $(WEBSITE_IMAGE) || true)
	$(call RUN,docker rmi -f $(REDIS_IMAGE) || true)

# Health check for Nginx
health:
ifneq ($(strip $(DOMAIN)),)
	@echo "$(CYAN)==> Checking https://$(DOMAIN)/healthz$(RESET)"
	$(call RUN,curl -vk https://$(DOMAIN)/healthz || true)
else
	@echo "$(RED)DOMAIN is not set in $(ENV_FILE)$(RESET)"
endif

# Clean everything (containers, volumes, images, .env, certs, secrets)
fclean:
	@read -p "⚠️  This will NUKE your environment (containers, volumes, images, .env, certs, secrets). Continue? [Y/n] " ans; \
	if [ "$$ans" = "n" ] || [ "$$ans" = "N" ]; then \
		echo "❌ Aborted."; \
		exit 1; \
	fi; \
	echo "$(RED)==> Nuking environment (DESTRUCTIVE: containers, volumes, images, .env)$(RESET)"; \
	$(MAKE) --no-print-directory down-v || true; \
	$(MAKE) --no-print-directory rmi || true; \
	echo "$(RED)Removing $(ENV_FILE)$(RESET)"; \
	rm -f $(ENV_FILE); \
	echo "$(RED)Removing $(COMPOSE_DIR)/requirements/nginx/certs$(RESET)"; \
	rm -rf $(COMPOSE_DIR)/requirements/nginx/certs; \
	echo "$(RED)Removing secrets$(RESET)"; \
	rm -rf secrets; \
	echo "$(GREEN)Nuke complete.$(RESET)"
