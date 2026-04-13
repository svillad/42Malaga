*This project has been created as part of the 42 curriculum by svillad*

# Inception

## Description
This project consists of building a small Docker-based infrastructure running inside a virtual machine.
The main stack includes NGINX as the single entry point over HTTPS, WordPress with php-fpm, and MariaDB. Additional bonus services are incorporated, such as Adminer for database management, an FTP server for WordPress file transfers, a static website, Redis for caching, and Prometheus along with exporters for stack monitoring.
The goal is to understand containerization, service isolation, persistence, networking, secure secret management, and environment-based configuration.

## Project architecture
- **NGINX:** Exposes port 443 with TLSv1.2/TLSv1.3 only. Acts as reverse proxy and static file server.
- **WordPress + php-fpm:** Core web application running on port 9000 internally.
- **MariaDB:** Relational database backend for WordPress.
- **Adminer:** Lightweight database management tool, routed through NGINX.
- **FTP Server:** Allows uploading/managing files in the WordPress volume via FTP (port 21 + passive ports).
- **Website:** A secondary static HTML website served via NGINX.
- **Redis:** In-memory data structure store used as an object cache for WordPress.
- **Prometheus & Exporters:** Monitoring stack collecting metrics from MariaDB, Redis, and other services.
- **Networking:** Dedicated custom bridge network (`stack_net` by default).
- **Volumes:** Four persistent named volumes mapped to host directories:
  - Database storage (`wp_db`)
  - WordPress files storage (`wp_data`)
  - Redis cache data (`redis_data`)
  - Prometheus metrics data (`prometheus_data`)
- **Secrets Management:** Docker secrets and mapped file paths are strictly utilized to avoid hardcoding credentials.

## Main design choices
- Alpine/Debian base images.
- One Dockerfile per service (processes daemonized internally).
- Centralized environment setup using an interactive `app-setup.sh` script to generate `.env` and `secrets/` without storing them in Git.
- NGINX exposed on port 443 with self-signed certificate generation available during setup.
- Comprehensive `Makefile` mapping complex Docker Compose and maintenance commands.
- Secure credential injection: passwords read inside containers at runtime via files from the `/run/secrets` path.

## Comparison topics
### Virtual Machines vs Docker
A Virtual Machine (VM) emulates a full physical hardware system, including a complete Operating System (OS). This results in high isolation but significant resource overhead and slow startup times. Docker containers, on the other hand, share the host system's OS kernel, virtualizing only the application layer. This makes Docker lightweight, fast to start, and highly portable, while still providing sufficient process isolation for most microservice architectures.

### Secrets vs Environment Variables
Environment variables are readily visible to anyone with access to the container or machine's process list (`env` command or `docker inspect`). For sensitive data like database passwords, using Docker Secrets (or file-based secret injection) is significantly safer, as the values are mounted as files in a secure read-only filesystem (e.g., `/run/secrets`) rather than injected broadly into the container's environment space.

### Docker Network vs Host Network
Using the host network maps a container's network stack directly to the host, meaning ports expose directly without network translation. It is performant but breaks port isolation and creates port conflicts. A custom Docker Network (like a `bridge`) places containers on an isolated virtual network where they can easily discover and communicate with each other via DNS names (container names) without exposing any internal ports to the host machine. Ports are explicitly published to the host only when required (e.g., 443 for NGINX).

### Docker Volumes vs Bind Mounts
Bind mounts map a specific existing directory from the host machine directly into a container (`/path/on/host:/path/in/container`). They are very dependent on the host file system structure and permissions. Docker Volumes are managed strictly by Docker itself (often stored in `/var/lib/docker/volumes`), offering better integration with Docker CLI, simpler backups, and safer lifecycle management. In this project, to meet subject constraints of storing data in `/home/login/data`, local volumes are configured using bind options (`device: /home/login/data/...`).

## Instructions
### Prerequisites
- Virtual machine ready (Linux) or macOS environment.
- Docker & Docker Compose installed.
- `make` installed.
- Correct `/etc/hosts` entry routing `<login>.42.fr` to `127.0.0.1` (or VM IP).

### Setup
1. Clone the repository.
2. Run configuration wizard:
   ```bash
   make setup
   ```
   (This executes `app-setup.sh`, asking for desired usernames, passwords, and volumes to create `.env` and `secrets/`).
3. Start the stack:
   ```bash
   make up
   ```

### Common commands
```bash
make help        # Show all available commands
make build       # Build all images
make up          # Start the containers in background
make down        # Stop the containers
make fclean      # Remove containers, networks, images, volumes, .env, and secrets
make url         # Show all active service URLs for the specified domain
```

## Resources
- Docker & Compose official documentation
- Alpine Linux documentation
- NGINX & TLS configurations
- WordPress CLI & Core configurations
- Adminer, Redis, FTP (vsftpd) configuration pages
- Prometheus metrics documentation

## AI usage
AI was used strictly as a support tool for repetitive tasks, documentation drafting, debugging script syntax (`app-setup.sh`), and conceptual clarification. All generated content was fully reviewed, tested locally, and adapted to fit the specific needs of this architecture. No code or configuration was kept without being fully understood.
