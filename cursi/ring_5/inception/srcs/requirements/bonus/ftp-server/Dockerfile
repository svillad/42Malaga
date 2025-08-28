FROM debian:bullseye

RUN apt update && apt upgrade -y && \
    apt install -y vsftpd netcat-openbsd && \
    rm -rf /var/lib/apt/lists/*

# 1) Create directories for FTP
RUN mkdir -p /var/ftp && \
    mkdir -p /var/empty && \
    chown root:root /var/empty && chmod 0555 /var/empty


# 2) Copy ftpserver-setup script and make it executable
COPY ftpserver-setup.sh /usr/local/bin/ftpserver-setup.sh
RUN chmod +x /usr/local/bin/ftpserver-setup.sh

# 3) Healthcheck for FTP server (expect 220 banner on port 21)
HEALTHCHECK --interval=10s --timeout=5s --retries=5 \
  CMD sh -lc 'printf "QUIT\r\n" | nc -w 3 127.0.0.1 ${FTP_PORT:-21} | grep -q "^220"'

CMD ["/usr/local/bin/ftpserver-setup.sh"]
