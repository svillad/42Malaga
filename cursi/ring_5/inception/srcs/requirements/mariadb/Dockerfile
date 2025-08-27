FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

# 1) Base packages + MariaDB server
RUN apt-get update && apt-get install -y --no-install-recommends \
  mariadb-server mariadb-client ca-certificates tzdata curl \
 && rm -rf /var/lib/apt/lists/*

# 2) Directories and permissions
RUN mkdir -p /var/lib/mysql /var/run/mysqld /docker-entrypoint-initdb.d \
 && chown -R mysql:mysql /var/lib/mysql /var/run/mysqld \
 && chmod 1777 /var/run/mysqld

# 3) Expected environment variables (can be overwritten at runtime)
ENV MARIADB_DATABASE= \
    MARIADB_USER= \
    MARIADB_PASSWORD= \
    MARIADB_ROOT_PASSWORD=

# 4) Entry script (initializes if the datadir is empty)
COPY mariadb-setup.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/mariadb-setup.sh

VOLUME ["/var/lib/mysql"]

HEALTHCHECK --interval=10s --timeout=5s --retries=5 \
  CMD mariadb-admin ping -uroot --silent || exit 1

ENTRYPOINT ["mariadb-setup.sh"]
CMD ["mysqld", "--user=mysql", "--datadir=/var/lib/mysql", "--bind-address=0.0.0.0"]
