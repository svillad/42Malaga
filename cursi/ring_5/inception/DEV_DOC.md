# DEV_DOC

## Development prerequisites
- A virtual machine (Debian/Ubuntu recommended) or macOS environment.
- Docker installed and the daemon running.
- Docker Compose installed (v2 is invoked via `docker compose` or `docker-compose`).
- Make installed (`build-essential`).
- A valid `/etc/hosts` entry redirecting `<login>.42.fr` to `127.0.0.1` or the IP of your Virtual Machine.

## Required files
- `srcs/docker-compose.yml`: main orchestration manifest.
- `srcs/app-setup.sh`: an interactive bash script to initialize `.env` and secret files.
- `srcs/.env`: dynamic generation of environment mappings (added to `.gitignore`).
- Service Dockerfiles and their entrypoint scripts (located in `srcs/requirements/`).
- System secrets stored entirely as physical files inside the `secrets/` directory (added to `.gitignore`).

## Environment setup
Starting from a fresh repository fetch:
1. Clone the repository.
2. Ensure you have permissions to execute scripts.
3. Run the setup wizard:
   ```bash
   make setup
   ```
   This command executes `app-setup.sh`. It will prompt you interactively for configuration variables (e.g. database names, admin passwords, ports, user logins). It will automatically construct `srcs/.env` and the `secrets/` directory containing text files of the passwords.
4. The wizard will create necessary data directories on the host system (dynamically mapped to `/home/<login>/data/` or `/Users/<login>/data/` on macOS).
5. Ensure `<login>.42.fr` resolves locally by adding a line like `127.0.0.1 <login>.42.fr` to `/etc/hosts`.

## Build and launch
Build the custom Docker images configured in `docker-compose.yml`:
```bash
make build
```

Launch the stack in detached mode:
```bash
make up
```

Alternatively, combine build and launch in one step:
```bash
make up-build
```

## Useful commands
The project's `Makefile` heavily abstracts complex docker management commands. Recommended shortcuts:

```bash
make logs         # Tail logs for all containers
make logs-db      # Tail logs specifically for MariaDB
make sh-nginx     # Drop into a shell inside the NGINX container
make exec-db      # Drop immediately into the `mysql` CLI inside MariaDB
make restart      # Stop and start containers quickly
make down         # Gracefully kill and remove containers and network
make rebuild      # 'make re' triggers down, build, clean and up
make fclean       # Destructive command: wipes volumes, networks, .env, and secrets.
```

Standard Docker CLI usage is actively supported:
```bash
docker ps
docker images
docker volume ls
docker network ls
```

## Data persistence
The application leverages robust named docker volumes. In development, the `.env` configuration maps these to static paths on your local drive to survive container removal:
- **`wp_db`**: Stores MariaDB database internals.
- **`wp_data`**: Stores the raw PHP/HTML files of WordPress.
- **`redis_data`**: Persists Redis cache elements.
- **`prometheus_data`**: Holds monitoring time series metrics.

These named volumes explicitly utilize the local driver with bind options pointing to:
`/home/<login>/data/<volume_name>`

*(⚠️ Warning: Running `make down-v`, `make reset-wp-db` or `make fclean` will permanently destroy this tracked host data).*

## Notes for developers
- **Image Tagging:** Avoid `latest` tags anywhere in `docker-compose.yml` or `Dockerfile` from directives (e.g., `FROM debian:bullseye`).
- **Secrets Protocol:** Never write passwords or tokens manually into `docker-compose.yml`. Applications are built to strictly read from `/run/secrets/...` initialized dynamically by `app-setup.sh`.
- **Environment Driven:** Any path, port, or logical fork must be configurable through variables propagated from `srcs/.env`.
- **Prohibited Patterns:** `tail -f /dev/null`, `sleep infinity`, or `while true` loops to keep containers artificially alive are banned. Processes must hook natively into the daemon (e.g., `nginx -g 'daemon off;'` or `php-fpm -F`). Host networking (`network_mode: "host"`) is also strictly prohibited.

## Essential Docker Compose commands
The most common commands for managing the multi-container stack.

```bash
docker-compose up -d --build    # Build images and start the stack in the background
docker-compose down             # Stop and remove all containers and networks
docker-compose ps               # Check the status of your services
docker-compose logs -f <svc>    # View live logs (omit <svc> for all logs)
docker-compose exec <svc> sh    # Open a terminal inside a running service
```

## Common Docker commands
Useful commands for managing individual containers and images.

```bash
docker ps                       # List running containers
docker images                   # List downloaded/built images
docker stop <container>         # Stop a running container
docker start <container>        # Start a stopped container
docker pause <container>        # Freeze all processes in a container (SIGSTOP)
docker unpause <container>      # Resume a paused container (SIGCONT)
docker rm -f <container>        # Force remove a container
docker rmi <image>              # Remove an image
docker system prune -a          # Cleanup: remove all unused containers, networks, and images
```

## SQL commands (inside MariaDB CLI)
You can enter the MariaDB shell using the following shortcut: `make exec-db`. Alternatively, use the direct Docker command: `docker exec -it mariadb mariadb -uroot`. Once inside, use these queries to explore databases, tables, and WordPress user data.

```sql
SHOW DATABASES;
USE mysql;
SHOW TABLES;
SELECT User, Password, Host, plugin, authentication_string FROM user;

USE appdb;
SELECT * FROM <table>;
SHOW TABLES;
SELECT * FROM wp_users;
SELECT user_login, user_email FROM wp_users;
```

## Debugging and verification
Handy one-liners for verifying HTTPS connectivity, checking environment variables inside containers, and confirming that theme assets are correctly mounted.

```bash
# Test HTTPS access to the site
curl -vk https://svilla-d.42.fr/

# Health check through NGINX
docker compose -f srcs/docker-compose.yml exec nginx curl -vk https://localhost/healthz

# Verify WordPress environment variables
docker compose -f srcs/docker-compose.yml exec wordpress sh -lc \
  'env | grep -E "WORDPRESS_DB_HOST|MARIADB_(DATABASE|USER|PASSWORD)"'

# Check theme CSS files in NGINX
docker compose -f srcs/docker-compose.yml exec nginx sh -lc \
  'ls -l /var/www/html/wp-content/themes/twentytwentyfive/assets/css/style.min.css || true'

docker compose -f srcs/docker-compose.yml exec nginx sh -lc \
  'ls -l /var/www/html/wp-content/themes/twentytwentyfive/assets/css/editor-style.css || true'

# Check theme CSS files in WordPress
docker compose -f srcs/docker-compose.yml exec wordpress sh -lc \
  'ls -l /var/www/html/wp-content/themes/twentytwentyfive/assets/css/editor-style.css || true'
```

## Port connectivity checks
Use `curl` and `nc` (netcat) to verify that each service port is reachable from the host. A "No publicado" message indicates the port is not exposed or the service is down.

```bash
# HTTPS (443)
curl -vk https://localhost:443
nc -vz 127.0.0.1 443 || echo "No publicado"

# HTTP (80)
curl -vk https://localhost:80
nc -vz 127.0.0.1 80 || echo "No publicado"

# MariaDB (3306)
curl -vk https://localhost:3306
nc -vz 127.0.0.1 3306 || echo "No publicado"

# PHP-FPM (9000)
curl -vk https://localhost:9000
nc -vz 127.0.0.1 9000 || echo "No publicado"
```
