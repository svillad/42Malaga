#!/bin/sh
set -e

log() {
  printf "[nginx-setup][%s] %s\n" "$(date -u +"%Y-%m-%dT%H:%M:%SZ")" "$*" >&2
}

: "${CERTS_DIR:=/etc/nginx/certs}"
: "${RSA_BITS:=2048}"
: "${CERT_DAYS:=365}"

log "Starting service nginx with DOMAIN=${DOMAIN} UPSTREAM=${UPSTREAM} WORDPRESS_PORT=${WORDPRESS_PORT} GENERATE_SELF_SIGNED=${GENERATE_SELF_SIGNED}"

mkdir -p "${CERTS_DIR}"
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

rm -f /etc/nginx/conf.d/*.conf 2>/dev/null || true

# TLS template rendering
envsubst '${DOMAIN} ${UPSTREAM} ${WORDPRESS_PORT}' \
  < /etc/nginx/templates/default.conf.template \
  > /etc/nginx/conf.d/default.conf

mkdir -p /run/nginx
log "Launching nginx..."
exec "$@"
