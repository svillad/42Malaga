#!/usr/bin/env sh
set -e

log() {
  printf "[ftp][%s] %s\n" "$(date -u +"%Y-%m-%dT%H:%M:%SZ")" "$*" >&2
}

# 1. Load FTP password from *_FILE if provided
[ -n "${FTP_PASS_FILE:-}" ] && [ -f "${FTP_PASS_FILE}" ] && export FTP_PASSWORD="$(cat "${FTP_PASS_FILE}")"

# 2. Print startup information (hide password unless in development mode)
if [ -n "${APP_ENV:-}" ] && [ "${APP_ENV}" = "development" ]; then
  log "Starting service ftp with USER=${FTP_USER} PORT=${FTP_PORT} PASSWORD=${FTP_PASSWORD} TLS_ENABLE=${FTP_TLS_ENABLE}"
else
  log "Starting service ftp with USER=${FTP_USER} PORT=${FTP_PORT} PASSWORD=*** TLS_ENABLE=${FTP_TLS_ENABLE}"
fi

# 3. Create FTP user (ignore if it already exists)
useradd -m -s /bin/sh "${FTP_USER}" 2>/dev/null || true

# 4. Set FTP user password
echo "${FTP_USER}:${FTP_PASSWORD}" | chpasswd

# 5. Create userlist file for vsftpd and secure permissions
printf '%s\n' "${FTP_USER}" > /etc/vsftpd.userlist
chmod 600 /etc/vsftpd.userlist

# 6. Create FTP directory for the user and set ownership
mkdir -p "/home/${FTP_USER}/ftp"
chown "${FTP_USER}:${FTP_USER}" "/home/${FTP_USER}/ftp"

# 7. Ensure secure chroot directory exists with proper permissions
mkdir -p /var/empty
chown root:root /var/empty
chmod 0555 /var/empty

# 8. Map FTP_TLS_ENABLE (true/false) to YES/NO for vsftpd
TLS_FLAG="NO"
case "${FTP_TLS_ENABLE:-}" in
  true|TRUE|yes|YES|on|ON|1) TLS_FLAG="YES" ;;
esac

# 9. Resolve PASV address: if hostname, convert to IP; if unresolved, skip
RESOLVED_PASV="${FTP_PASV_ADDRESS:-}"
if [ -n "${RESOLVED_PASV}" ]; then
  if ! echo "${RESOLVED_PASV}" | grep -Eq '^[0-9]+(\.[0-9]+){3}$'; then
    if command -v getent >/dev/null 2>&1; then
      RESOLVED_PASV_IP="$(getent hosts "${RESOLVED_PASV}" | awk 'NR==1{print $1}')"
    else
      RESOLVED_PASV_IP=""
    fi
    if [ -n "${RESOLVED_PASV_IP}" ]; then
      RESOLVED_PASV="${RESOLVED_PASV_IP}"
    else
      RESOLVED_PASV=""
    fi
  fi
fi

# 10. Define PASV configuration line depending on resolution
if [ -n "${RESOLVED_PASV}" ]; then
  PASV_ADDRESS_LINE="pasv_address=${RESOLVED_PASV}"
else
  PASV_ADDRESS_LINE="# pasv_address not set (using interface address)"
fi

# 11. Generate /etc/vsftpd.conf from environment variables
cat > /etc/vsftpd.conf <<EOF
listen=YES
listen_ipv6=NO
anonymous_enable=NO
local_enable=YES
write_enable=YES
use_localtime=YES
chroot_local_user=YES
allow_writeable_chroot=YES
secure_chroot_dir=/var/empty
pam_service_name=vsftpd

# Userlist
userlist_enable=YES
userlist_file=/etc/vsftpd.userlist
userlist_deny=NO

# Passive mode settings
pasv_enable=YES
pasv_min_port=21000
pasv_max_port=21010
${PASV_ADDRESS_LINE}
local_root=/var/www/html

# Port
listen_port=${FTP_PORT}

# TLS/SSL
ssl_enable=${TLS_FLAG}
rsa_cert_file=/etc/ssl/certs/ssl-cert-snakeoil.pem
rsa_private_key_file=/etc/ssl/private/ssl-cert-snakeoil.key

# Umask
local_umask=022

# Connection limits
max_clients=50
max_per_ip=5
EOF

# 12. Start vsftpd with the generated configuration
log "✅ Provision complete. Launching ftp-server"
exec vsftpd /etc/vsftpd.conf