#!/usr/bin/env sh
set -e

# 1. Logging helper
log() {
  printf "[nginx][%s] %s\n" "$(date -u +"%Y-%m-%dT%H:%M:%SZ")" "$*" >&2
}

# 2. Default configuration (env fallbacks)
: "${CERTS_DIR:=/etc/nginx/certs}"
: "${RSA_BITS:=2048}"
: "${CERT_DAYS:=365}"

# 3. Startup log (context)
log "Starting service nginx with DOMAIN=${DOMAIN} UPSTREAM=${UPSTREAM} WORDPRESS_PORT=${WORDPRESS_PORT} GENERATE_SELF_SIGNED=${GENERATE_SELF_SIGNED}"

# 4. Ensure certificates directory exists
mkdir -p "${CERTS_DIR}"

# 5. Generate self-signed certificates if enabled
if [ "${GENERATE_SELF_SIGNED}" = "true" ]; then
  log "Generating self-signed certificate for ${DOMAIN} (bits=${RSA_BITS}, days=${CERT_DAYS})"
  if [ ! -f "${CERTS_DIR}/privkey.pem" ] || [ ! -f "${CERTS_DIR}/fullchain.pem" ]; then
    openssl req -x509 -nodes -newkey "rsa:${RSA_BITS}" \
      -keyout "${CERTS_DIR}/privkey.pem" \
      -out "${CERTS_DIR}/fullchain.pem" \
      -days "${CERT_DAYS}" \
      -subj "/CN=${DOMAIN}" \
      -addext "subjectAltName=DNS:${DOMAIN}" \
      2>&1 >/dev/null
    chmod 600 "${CERTS_DIR}/privkey.pem"
  else
    log "Using existing certificates in ${CERTS_DIR}"
  fi
fi

# 6. Clean previous Nginx vhost configs
rm -f /etc/nginx/conf.d/*.conf 2>/dev/null || true

# 7. Render TLS-enabled server block from template
envsubst '${DOMAIN} ${UPSTREAM} ${WORDPRESS_PORT}' \
  < /etc/nginx/templates/default.conf.template \
  > /etc/nginx/conf.d/default.conf

# 8. Ensure runtime directory
mkdir -p /run/nginx

# 9. Launch Nginx (CMD/ARGS passed by Docker)
log "✅ Provision complete. Launching nginx"
exec "$@"