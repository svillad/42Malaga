FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive \
    PROMETHEUS_VERSION=2.54.1 \
    PROMETHEUS_USER=prometheus

# 1. Required packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    curl ca-certificates tar gzip \
    && rm -rf /var/lib/apt/lists/*

# 2. Create non-root user
RUN useradd --no-create-home --shell /usr/sbin/nologin ${PROMETHEUS_USER}

# 3. Download Prometheus
RUN curl -fsSL https://github.com/prometheus/prometheus/releases/download/v${PROMETHEUS_VERSION}/prometheus-${PROMETHEUS_VERSION}.linux-amd64.tar.gz \
    | tar xz -C /tmp \
    && mv /tmp/prometheus-${PROMETHEUS_VERSION}.linux-amd64 /opt/prometheus \
    && ln -s /opt/prometheus/prometheus /usr/local/bin/prometheus \
    && ln -s /opt/prometheus/promtool /usr/local/bin/promtool \
    && rm -rf /tmp/*

# 4. Data and configuration directories
RUN mkdir -p /etc/prometheus /prometheus \
    && chown -R ${PROMETHEUS_USER}:${PROMETHEUS_USER} /etc/prometheus /prometheus /opt/prometheus

# 5. Copy configuration files
COPY conf/prometheus.yml /etc/prometheus/prometheus.yml
COPY conf/rules.yml /etc/prometheus/rules.yml
COPY conf/rules-extra.yml /etc/prometheus/rules-extra.yml

# 6. Switch to non-root user
USER ${PROMETHEUS_USER}

# 7. Default command
ENTRYPOINT ["/usr/local/bin/prometheus"]
CMD ["--config.file=/etc/prometheus/prometheus.yml", \
     "--storage.tsdb.path=/prometheus", \
     "--web.enable-lifecycle"]
