#!/bin/bash

# Create FTP user from environment variables
useradd -m -s /bin/bash ${FTP_USER} 2>/dev/null || true
echo "${FTP_USER}:${FTP_PASSWORD}" | chpasswd

# Create userlist file
echo "${FTP_USER}" > /etc/vsftpd.userlist
chmod 600 /etc/vsftpd.userlist

# Create FTP directory and set permissions
mkdir -p /home/${FTP_USER}/ftp
chown ${FTP_USER}:${FTP_USER} /home/${FTP_USER}/ftp

# Ensure secure chroot dir exists with correct permissions
mkdir -p /var/empty
chown root:root /var/empty
chmod 0555 /var/empty

# Map FTP_TLS_ENABLE (true/false) to YES/NO for vsftpd
TLS_FLAG="NO"
case "${FTP_TLS_ENABLE}" in
  true|TRUE|yes|YES|on|ON|1) TLS_FLAG="YES" ;;
esac

# Resolve PASV address: if hostname is provided, resolve to IP; if empty or unresolved, omit pasv_address
RESOLVED_PASV="${FTP_PASV_ADDRESS}"
if [ -n "$RESOLVED_PASV" ]; then
  if ! echo "$RESOLVED_PASV" | grep -Eq '^[0-9]+(\.[0-9]+){3}$'; then
    RESOLVED_PASV_IP=$(getent hosts "$RESOLVED_PASV" | awk '{print $1}' | head -n1)
    if [ -n "$RESOLVED_PASV_IP" ]; then
      RESOLVED_PASV="$RESOLVED_PASV_IP"
    else
      RESOLVED_PASV=""
    fi
  fi
fi

if [ -n "$RESOLVED_PASV" ]; then
  PASV_ADDRESS_LINE="pasv_address=$RESOLVED_PASV"
else
  PASV_ADDRESS_LINE="# pasv_address not set (using interface address)"
fi

# Generate vsftpd configuration from environment variables
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

# Start vsftpd with generated configuration
exec vsftpd /etc/vsftpd.conf
