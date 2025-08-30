FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

# 1. Install packages (vsftpd and netcat) and clean apt cache
RUN apt update && apt upgrade -y && \
    apt install -y vsftpd netcat-openbsd && \
    rm -rf /var/lib/apt/lists/*

# 2. Create required directories for FTP and secure chroot
RUN mkdir -p /var/ftp && \
    mkdir -p /var/empty && \
    chown root:root /var/empty && chmod 0555 /var/empty

# 3. Copy entrypoint script and make it executable
COPY ftpserver-setup.sh /usr/local/bin/ftpserver-setup.sh
RUN chmod +x /usr/local/bin/ftpserver-setup.sh

# 4. Healthcheck for FTP server (expect 220 banner on port 21)
HEALTHCHECK --interval=60s --timeout=5s --retries=5 \
  CMD sh -lc 'printf "QUIT\r\n" | nc -w 3 127.0.0.1 ${FTP_PORT:-21} | grep -q "^220"'

# 5. Default command: start FTP server setup
CMD ["/usr/local/bin/ftpserver-setup.sh"]