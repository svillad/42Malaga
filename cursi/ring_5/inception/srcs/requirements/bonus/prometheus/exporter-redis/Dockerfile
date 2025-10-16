FROM debian:bookworm-slim

ARG EXPORTER_USER=redis_exporter
ENV DEBIAN_FRONTEND=noninteractive \
    EXPORTER_VERSION=1.62.0 \
    EXPORTER_USER=${EXPORTER_USER}

# 1. Install minimal required packages
RUN apt-get update && apt-get install -y --no-install-recommends \
      ca-certificates curl tar gzip \
    && rm -rf /var/lib/apt/lists/*

# 2. Create non-root user
RUN useradd --no-create-home --shell /usr/sbin/nologin ${EXPORTER_USER}

# 3. Download official binary
RUN curl -fsSL https://github.com/oliver006/redis_exporter/releases/download/v${EXPORTER_VERSION}/redis_exporter-v${EXPORTER_VERSION}.linux-amd64.tar.gz \
  | tar xz -C /tmp && \
  mv /tmp/redis_exporter-v${EXPORTER_VERSION}.linux-amd64/redis_exporter /usr/local/bin/redis_exporter && \
  rm -rf /tmp/redis_exporter-v${EXPORTER_VERSION}.linux-amd64 && \
  chmod +x /usr/local/bin/redis_exporter

# 4. Copy external script and normalize line endings/BOM
COPY entrypoint.sh /usr/local/bin/entrypoint.sh
RUN sed -i 's/\r$//' /usr/local/bin/entrypoint.sh && \
    sed -i '1s/^\xEF\xBB\xBF//' /usr/local/bin/entrypoint.sh && \
    chmod +x /usr/local/bin/entrypoint.sh

# 5. Switch to non-root user and define entrypoint
USER ${EXPORTER_USER}
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]