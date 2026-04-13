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
