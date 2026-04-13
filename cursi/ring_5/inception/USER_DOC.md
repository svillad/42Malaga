# USER_DOC

## Overview
This stack provides a complete, modern web infrastructure containing:
- A secure HTTPS entry point through NGINX.
- A fully functional WordPress website configured with PHP-FPM.
- A MariaDB database used by WordPress.
- Adminer for easy database administration via a web UI.
- An FTP server to transfer files directly to the WordPress content volume.
- A static HTML demonstration website.
- Redis as an in-memory object cache to speed up WordPress load times.
- Prometheus for monitoring and collecting metrics across the stack.

## How to start the project
To initially setup configuration (variables, secrets) and start the project:
```bash
make setup
make up
```

If you have already run `setup`, simply start the project in the background with:
```bash
make up
```

## How to stop the project
To simply stop the running containers without losing data:
```bash
make stop
```

To stop and remove the containers and network:
```bash
make down
```

## How to access the main services

First, run the command below to have the Makefile print out all active URLs and credentials for your configured domain:
```bash
make url
```

**Website Entry:**
Open: `https://<login>.42.fr` (ensure your local hosts file points this domain to your machine's IP address).

**WordPress Admin Panel:**
Open: `https://<login>.42.fr/wp-admin`
Log in using the WordPress administrator credentials you established during `make setup`.

**Adminer (Database Manager):**
Open: `https://<login>.42.fr/adminer`

**Prometheus Dashboard:**
Open: `https://prometheus.<login>.42.fr` (if configured in your routing), or check internal routing depending on NGINX config.

**Static Website:**
Open: `https://<login>.42.fr/me` (or route assigned in configuration).

**FTP Uploads:**
Use any FTP client (like FileZilla) to connect to `ftp://<login>.42.fr` on port `21` using the FTP credentials established during setup.

## Credentials management
Credentials are automatically generated and securely stored outside the source code during the `make setup` process.
They are located in the `srcs/.env` file and the `secrets/` directory. They are passed directly to containers using Docker Secrets (or file paths) at runtime. They are never hardcoded inside Dockerfiles or committed to the Git repository.

## Health checks
Useful commands provided by the Makefile:
```bash
make ps           # Summary of running containers
make logs         # Shows logs of all services
make logs-wp      # Show only WordPress logs
make logs-nginx   # Show only NGINX logs
make health       # Perform a curl check against the NGINX /healthz endpoint
```

Standard Docker checks:
```bash
docker ps
docker volume ls
docker network ls
```

Checks to perform:
- NGINX is running and responds securely over HTTPS.
- WordPress loads without database error pages.
- Data successfully persists after a `make restart` or `make down` -> `make up` cycle.
