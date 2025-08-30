# srcs/requirements/nginx/Dockerfile
FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

# 1. nginx + envsubst + openssl for TLS
RUN apt-get update && apt-get install -y --no-install-recommends \
    nginx gettext-base ca-certificates curl openssl \
    && rm -rf /var/lib/apt/lists/*

# 2. Template and nginx-setup
COPY conf/default.conf.template /etc/nginx/templates/default.conf.template
COPY nginx-setup.sh /usr/local/bin/nginx-setup.sh

#3.  Normalize line endings and strip UTF-8 BOM if present, then make executable
RUN sed -i 's/\r$//' /usr/local/bin/nginx-setup.sh && \
    sed -i '1s/^\xEF\xBB\xBF//' /usr/local/bin/nginx-setup.sh && \
    chmod +x /usr/local/bin/nginx-setup.sh

# 4. Default variables
ENV DOMAIN= \
    UPSTREAM= 

# 5. Health via HTTPS (use -k if self-signed cert)
HEALTHCHECK --interval=60s --timeout=5s --retries=5 \
  CMD curl -fsSk https://127.0.0.1/healthz || exit 1

# 6.Define entrypoint
ENTRYPOINT ["/bin/sh", "/usr/local/bin/nginx-setup.sh"]
CMD ["nginx", "-g", "daemon off;"]
