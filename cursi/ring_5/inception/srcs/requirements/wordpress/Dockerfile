FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive \
    WORDPRESS_VERSION=6.8.2
    
# 1. Install PHP-FPM, WordPress dependencies, MySQL client, and helper tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    gettext-base ca-certificates curl tar unzip mariadb-client \
    php-fpm php-mysql php-xml php-mbstring php-curl php-zip php-gd php-intl procps \
    php-cli php-redis \
 && rm -rf /var/lib/apt/lists/*

# 2. Verify that the Redis PHP extension is loaded (fail build if missing)
RUN php -m | grep -qi '^redis$' || (echo 'ERROR: php-redis not loaded' >&2; exit 1)

# 3. Download and extract WordPress sources into /usr/src/wordpress
RUN mkdir -p /usr/src/wordpress \
 && curl -fsSL "https://wordpress.org/wordpress-${WORDPRESS_VERSION}.tar.gz" -o /tmp/wp.tar.gz \
 && tar -xzf /tmp/wp.tar.gz -C /usr/src \
 && rm -f /tmp/wp.tar.gz

# 4. Provide FPM pool template and ensure pool.d exists with a default www.conf
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

# 5. Copy entrypoint script, normalize line endings, and make it executable
COPY wordpress-setup.sh /usr/local/bin/wordpress-setup.sh
RUN sed -i 's/\r$//' /usr/local/bin/wordpress-setup.sh && \
    chmod +x /usr/local/bin/wordpress-setup.sh

# 6. Ensure /run/php exists with correct ownership
RUN mkdir -p /run/php && chown www-data:www-data /run/php

# 7. Healthcheck: ensure php-fpm process is running
HEALTHCHECK --interval=60s --timeout=5s --retries=5 --start-period=45s \
  CMD sh -lc 'pgrep -x php-fpm >/dev/null || pgrep -x php-fpm8.2 >/dev/null'

# 8. Set working directory and define entrypoint
WORKDIR /var/www/html
ENTRYPOINT ["/usr/local/bin/wordpress-setup.sh"]
