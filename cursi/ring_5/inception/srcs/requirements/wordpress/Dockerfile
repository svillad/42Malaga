# srcs/requirements/wordpress/Dockerfile
FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive \
    WORDPRESS_PORT= \
    WORDPRESS_VERSION=latest

# Install PHP-FPM and common extensions for WordPress + tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    gettext-base ca-certificates curl tar unzip mariadb-client \
    php-fpm php-mysql php-xml php-mbstring php-curl php-zip php-gd php-intl \
 && rm -rf /var/lib/apt/lists/*


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

WORKDIR /var/www/html
ENTRYPOINT ["/usr/local/bin/wordpress-setup.sh"]