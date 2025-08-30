FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

# 1. Install Apache, PHP, and required extensions
RUN apt-get update && apt-get install -y --no-install-recommends \
    apache2 libapache2-mod-php php php-mysqli php-mbstring php-xml ca-certificates curl \
 && rm -rf /var/lib/apt/lists/*

# 2. Configure Apache server name
RUN printf "ServerName localhost\n" > /etc/apache2/conf-available/servername.conf \
 && a2enconf servername

# 3. Define Adminer version to install
ARG ADMINER_VERSION=5.3.0

# 4. Create directory for Adminer, download and set permissions
RUN mkdir -p /var/www/html/adminer \
 && curl -fsSL "https://github.com/vrana/adminer/releases/download/v${ADMINER_VERSION}/adminer-${ADMINER_VERSION}.php" \
      -o /var/www/html/adminer/index.php \
 && chown -R www-data:www-data /var/www/html

# 5. Set default database server for Adminer login
ENV ADMINER_DEFAULT_SERVER=${DATABASE_SERVER}:${MARIADB_PORT}

# 6. Healthcheck: ensure Adminer is reachable on /adminer
HEALTHCHECK --interval=60s --timeout=5s --retries=5 \
  CMD curl -fsS http://127.0.0.1/adminer/ || exit 1

# 7. Default command: start Apache in foreground
CMD ["apachectl", "-D", "FOREGROUND"]