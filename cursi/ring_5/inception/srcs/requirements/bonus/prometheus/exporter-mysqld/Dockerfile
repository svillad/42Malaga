FROM debian:bookworm-slim

ARG EXPORTER_USER=redis_exporter
ENV DEBIAN_FRONTEND=noninteractive \
    EXPORTER_VERSION=0.15.1 \
    EXPORTER_USER=${EXPORTER_USER}

# 1. Minimal required packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates curl tar gzip \
 && rm -rf /var/lib/apt/lists/*

# 2. Create non-root user
RUN useradd --no-create-home --shell /usr/sbin/nologin ${EXPORTER_USER}

# 3. Download official binary (linux-amd64)
RUN curl -fsSL https://github.com/prometheus/mysqld_exporter/releases/download/v${EXPORTER_VERSION}/mysqld_exporter-${EXPORTER_VERSION}.linux-amd64.tar.gz \
  | tar xz -C /tmp \
 && mv /tmp/mysqld_exporter-${EXPORTER_VERSION}.linux-amd64/mysqld_exporter /usr/local/bin/mysqld_exporter \
 && rm -rf /tmp/mysqld_exporter-${EXPORTER_VERSION}.linux-amd64 \
 && chmod +x /usr/local/bin/mysqld_exporter

# 4. Copy external script and normalize line endings/BOM
COPY entrypoint.sh /usr/local/bin/entrypoint.sh
RUN sed -i 's/\r$//' /usr/local/bin/entrypoint.sh && \
    sed -i '1s/^\xEF\xBB\xBF//' /usr/local/bin/entrypoint.sh && \
    chmod +x /usr/local/bin/entrypoint.sh

# 5. Create directory for .my.cnf
RUN mkdir -p /etc/mysqld_exporter && chown -R ${EXPORTER_USER}:${EXPORTER_USER} /etc/mysqld_exporter

# 6. Switch to non-root user and define entrypoint
USER ${EXPORTER_USER}
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]