FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

# 1) Apache + PHP + mini extensions
RUN apt-get update && apt-get install -y --no-install-recommends \
    apache2 libapache2-mod-php php php-mysqli php-mbstring php-xml ca-certificates curl \
 && rm -rf /var/lib/apt/lists/*

RUN printf "ServerName localhost\n" > /etc/apache2/conf-available/servername.conf \
 && a2enconf servername

# 2) Adminer Version
ARG ADMINER_VERSION=5.3.0

# 3) Directorio propio para Adminer y descarga
RUN mkdir -p /var/www/html/adminer \
 && curl -fsSL "https://github.com/vrana/adminer/releases/download/v${ADMINER_VERSION}/adminer-${ADMINER_VERSION}.php" \
      -o /var/www/html/adminer/index.php \
 && chown -R www-data:www-data /var/www/html

# 4) Variable with the default host in the login
ENV ADMINER_DEFAULT_SERVER=mariadb

EXPOSE 80

# 5) Healthcheck to the /adminer route
HEALTHCHECK --interval=10s --timeout=5s --retries=5 \
  CMD curl -fsS http://127.0.0.1/adminer/ || exit 1

CMD ["apachectl", "-D", "FOREGROUND"]
