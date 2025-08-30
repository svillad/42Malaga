FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

# 1. Base packages + MariaDB server
RUN apt-get update && apt-get install -y --no-install-recommends \
  mariadb-server mariadb-client ca-certificates tzdata curl \
 && rm -rf /var/lib/apt/lists/*

# 2. Directories and permissions
RUN mkdir -p /var/lib/mysql /var/run/mysqld /docker-entrypoint-initdb.d \
 && chown -R mysql:mysql /var/lib/mysql /var/run/mysqld \
 && chmod 1777 /var/run/mysqld

# 3. Entry script (initializes if the datadir is empty)
COPY mariadb-setup.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/mariadb-setup.sh

# 4. Healthcheck for MariaDB (using mariadb-admin ping)
HEALTHCHECK --interval=60s --timeout=5s --retries=5 \
  CMD mariadb-admin ping -uroot --silent || exit 1

# 5. Define entrypoint
ENTRYPOINT ["mariadb-setup.sh"]
CMD ["mysqld", "--user=mysql", "--datadir=/var/lib/mysql", "--bind-address=0.0.0.0"]
