# srcs/requirements/wordpress/Dockerfile
FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive \
    WORDPRESS_PORT= \
    WORDPRESS_VERSION=latest \
    WORDPRESS_REDIS_HOST= \
    WORDPRESS_REDIS_PORT= \
    WORDPRESS_REDIS_PASS=

# Install PHP-FPM and common extensions for WordPress + tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    gettext-base ca-certificates curl tar unzip mariadb-client \
    php-fpm php-mysql php-xml php-mbstring php-curl php-zip php-gd php-intl procps \
    php-cli php-redis \
 && rm -rf /var/lib/apt/lists/*

# Verify redis extension is available in CLI (fail build if not)
RUN php -m | grep -qi '^redis$' || (echo 'ERROR: php-redis not loaded' >&2; exit 1)

# Download WordPress sources to a staging dir
RUN mkdir -p /usr/src/wordpress \
 && curl -fsSL "https://wordpress.org/${WORDPRESS_VERSION}.tar.gz" -o /tmp/wp.tar.gz \
 && tar -xzf /tmp/wp.tar.gz -C /usr/src \
 && rm -f /tmp/wp.tar.gz

# Provide FPM pool template and ensure pool.d exists with a seed www.conf
COPY conf/www.conf.template /usr/local/share/wordpress-fpm/www.conf.template
RUN set -eux; \
    POOL_DIR=$(echo /etc/php/*/fpm/pool.d || true); \
    if [ ! -d "$POOL_DIR" ]; then \
      BASE_DIR=$(echo /etc/php/*/fpm | head -n1); \
      mkdir -p "$BASE_DIR/pool.d"; \
      POOL_DIR="$BASE_DIR/pool.d"; \
    fi; \
    if [ ! -f "$POOL_DIR/www.conf" ]; then \
      printf "[www]\nlisten = /run/php/php-fpm.sock\n" > "$POOL_DIR/www.conf"; \
    fi

# Use external entrypoint script
COPY wordpress-setup.sh /usr/local/bin/wordpress-setup.sh
RUN sed -i 's/\r$//' /usr/local/bin/wordpress-setup.sh && \
    chmod +x /usr/local/bin/wordpress-setup.sh

RUN mkdir -p /run/php && chown www-data:www-data /run/php

# Simple healthcheck: PHP-FPM process exists
HEALTHCHECK --interval=10s --timeout=5s --retries=5 --start-period=45s \
  CMD sh -lc 'pgrep -x php-fpm >/dev/null || pgrep -x php-fpm8.2 >/dev/null'

WORKDIR /var/www/html
ENTRYPOINT ["/usr/local/bin/wordpress-setup.sh"]