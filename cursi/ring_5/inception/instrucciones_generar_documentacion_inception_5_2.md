# Instrucciones para generar los documentos faltantes — Inception 5.2

Este documento explica qué archivos te faltan para adaptar un proyecto **Inception** de la especificación **3.2** a la **5.2**, y cómo generarlos correctamente.

## Documentos obligatorios que faltan

Si tu proyecto estaba preparado según la 3.2, en la 5.2 normalmente te faltarán estos archivos en la raíz del repositorio:

- `README.md`
- `USER_DOC.md`
- `DEV_DOC.md`

> Todos deben estar escritos en **inglés**.

---

## Estructura recomendada del repositorio

```text
.
├── Makefile
├── README.md
├── USER_DOC.md
├── DEV_DOC.md
├── secrets/
└── srcs/
    ├── .env
    ├── docker-compose.yml
    └── requirements/
```

---

## 1. README.md

## Objetivo
El `README.md` debe permitir que cualquier persona que no conozca el proyecto entienda rápidamente:

- qué hace el proyecto,
- cómo se ejecuta,
- cómo está diseñado,
- qué tecnologías usa,
- y cómo se utilizó IA durante el desarrollo.

## Requisitos obligatorios
El `README.md` debe incluir como mínimo:

1. **Primera línea obligatoria en cursiva** con este formato:

```md
*This project has been created as part of the 42 curriculum by <login>*
```

Si hay varios autores:

```md
*This project has been created as part of the 42 curriculum by <login1>, <login2>*
```

2. Una sección **Description**.
3. Una sección **Instructions**.
4. Una sección **Resources**.
5. Una explicación de **cómo se usó la IA** en el proyecto.
6. Una explicación del uso de Docker y de las fuentes o componentes incluidos en el proyecto.
7. Una comparación entre:
   - Virtual Machines vs Docker
   - Secrets vs Environment Variables
   - Docker Network vs Host Network
   - Docker Volumes vs Bind Mounts

## Plantilla recomendada para README.md

```md
*This project has been created as part of the 42 curriculum by <login>*

# Inception

## Description
This project consists of building a small Docker-based infrastructure running inside a virtual machine.
The stack includes NGINX as the single entry point over HTTPS, WordPress with php-fpm, and MariaDB.
The goal is to understand containerization, service isolation, persistence, networking, and environment-based configuration.

## Project architecture
- NGINX container with TLSv1.2/TLSv1.3 only
- WordPress + php-fpm container
- MariaDB container
- Dedicated Docker network
- Two persistent named volumes:
  - database storage
  - WordPress files storage

## Main design choices
- Debian/Alpine base images
- One Dockerfile per service
- Environment-based configuration using `.env`
- Secrets kept outside the repository or handled with Docker secrets
- NGINX exposed on port 443 only

## Comparison topics
### Virtual Machines vs Docker
<explain differences>

### Secrets vs Environment Variables
<explain differences>

### Docker Network vs Host Network
<explain differences>

### Docker Volumes vs Bind Mounts
<explain differences>

## Instructions
### Prerequisites
- Virtual machine ready
- Docker installed
- Docker Compose available
- Correct `/etc/hosts` entry for `<login>.42.fr`

### Setup
1. Clone the repository.
2. Create the secrets files.
3. Fill the `.env` file.
4. Run `make`.

### Common commands
```bash
make
make up
make down
make re
```

## Resources
- Docker documentation
- Docker Compose documentation
- NGINX documentation
- MariaDB documentation
- WordPress documentation
- TLS / OpenSSL references

## AI usage
AI was used only as a support tool for repetitive tasks, documentation drafting, and conceptual clarification.
All generated content was reviewed, tested, and rewritten when necessary.
No code or configuration was kept without being fully understood.
```

## Instrucciones para generarlo
Puedes redactarlo tú o pedir ayuda a una IA, pero debes revisarlo y adaptarlo a tu proyecto real.

### Prompt sugerido

```text
Write a complete README.md in English for a 42 Inception project.
The project runs inside a virtual machine and uses Docker Compose.
It includes three containers: NGINX with TLS 1.2/1.3 only, WordPress with php-fpm, and MariaDB.
It uses two named Docker volumes stored under /home/<login>/data and one custom Docker network.
The README must include:
- first italicized line: This project has been created as part of the 42 curriculum by <login>
- Description
- Instructions
- Resources
- AI usage explanation
- explanation of Docker usage and project sources/components
- comparisons between: Virtual Machines vs Docker, Secrets vs Environment Variables, Docker Network vs Host Network, Docker Volumes vs Bind Mounts
Keep it clear, accurate, and suitable for evaluation.
```

---

## 2. USER_DOC.md

## Objetivo
`USER_DOC.md` debe explicar de forma simple cómo usar el proyecto desde el punto de vista de usuario o administrador.

## Requisitos obligatorios
Debe explicar:

- qué servicios ofrece la stack,
- cómo arrancar y parar el proyecto,
- cómo acceder al sitio web y al panel de administración,
- dónde están las credenciales y cómo gestionarlas,
- cómo comprobar que los servicios funcionan correctamente.

## Plantilla recomendada para USER_DOC.md

```md
# USER_DOC

## Overview
This stack provides:
- a secure HTTPS entry point through NGINX
- a WordPress website
- a MariaDB database used by WordPress

## How to start the project
```bash
make
```

Or, depending on the Makefile:

```bash
make up
```

## How to stop the project
```bash
make down
```

## How to access the website
Open:

```text
https://<login>.42.fr
```

Make sure your local hosts file points `<login>.42.fr` to your local machine IP address.

## How to access the WordPress admin panel
Open:

```text
https://<login>.42.fr/wp-admin
```

Use the administrator credentials configured during setup.

## Credentials management
Credentials are stored outside the source code, using environment variables and/or secret files.
They must never be hardcoded inside Dockerfiles or committed to the Git repository.

## Health checks
Useful commands:

```bash
docker ps
docker compose logs
docker volume ls
docker network ls
```

Checks to perform:
- NGINX is running
- WordPress is reachable via HTTPS
- MariaDB is running
- WordPress can log in to the database
- Persistent data remains after restart
```

## Prompt sugerido

```text
Write a USER_DOC.md in English for a 42 Inception project.
It must explain in simple terms:
- what services the stack provides,
- how to start and stop the project,
- how to access the website and WordPress admin panel,
- where credentials are managed,
- how to verify that the services are running correctly.
Assume the stack contains NGINX, WordPress with php-fpm, and MariaDB.
Keep it concise, clear, and practical for an evaluator or end user.
```

---

## 3. DEV_DOC.md

## Objetivo
`DEV_DOC.md` debe explicar cómo un desarrollador puede preparar, construir, ejecutar y mantener el proyecto.

## Requisitos obligatorios
Debe describir:

- cómo preparar el entorno desde cero,
- qué prerrequisitos existen,
- qué ficheros de configuración y secretos hacen falta,
- cómo construir y lanzar el proyecto con Makefile y Docker Compose,
- qué comandos sirven para gestionar contenedores y volúmenes,
- dónde se almacenan los datos y cómo persisten.

## Plantilla recomendada para DEV_DOC.md

```md
# DEV_DOC

## Development prerequisites
- A virtual machine
- Docker installed
- Docker Compose installed or available through Docker CLI
- Make installed
- A valid `/etc/hosts` entry for `<login>.42.fr`

## Required files
- `srcs/docker-compose.yml`
- `srcs/.env`
- service Dockerfiles
- secret files such as database password files

## Environment setup
1. Clone the repository.
2. Create the required secret files.
3. Fill the `.env` file with domain name, database values, and WordPress settings.
4. Ensure `/home/<login>/data` exists and is writable.
5. Ensure `<login>.42.fr` resolves locally.

## Build and launch
```bash
make
```

Alternative commands depending on the Makefile:

```bash
make up
make down
make re
```

## Useful Docker commands
```bash
docker ps
docker images
docker volume ls
docker network ls
docker compose logs
docker compose up --build
docker compose down
```

## Data persistence
Two named volumes are used:
- one for MariaDB data
- one for WordPress files

They persist data across container recreation and are mapped to storage under:

```text
/home/<login>/data
```

## Notes for developers
- Do not use `latest` tags.
- Do not hardcode passwords in Dockerfiles.
- Use `.env` for environment configuration.
- Prefer Docker secrets for sensitive values.
- Avoid forbidden patterns such as `tail -f`, `sleep infinity`, `while true`, or host networking.
```

## Prompt sugerido

```text
Write a DEV_DOC.md in English for a 42 Inception project.
It must explain:
- how to set up the environment from scratch,
- prerequisites,
- required configuration and secret files,
- how to build and launch the project with Makefile and Docker Compose,
- useful commands to manage containers, networks, and volumes,
- where project data is stored and how persistence works.
The project uses NGINX, WordPress with php-fpm, MariaDB, named volumes, a custom Docker network, and a `.env` file.
Make it practical and suitable for another developer joining the project.
```

---

## Checklist final antes de entregar

Comprueba todo esto:

- [ ] Existe `README.md` en la raíz.
- [ ] Existe `USER_DOC.md` en la raíz.
- [ ] Existe `DEV_DOC.md` en la raíz.
- [ ] Los 3 documentos están en **inglés**.
- [ ] El `README.md` empieza con la línea en cursiva obligatoria.
- [ ] El `README.md` explica el proyecto, Docker y las comparativas obligatorias.
- [ ] El `README.md` incluye cómo se usó IA.
- [ ] `USER_DOC.md` explica uso, acceso y verificación.
- [ ] `DEV_DOC.md` explica setup, build, ejecución y persistencia.
- [ ] El contenido coincide con tu implementación real.
- [ ] No has metido passwords ni secretos en el repositorio.

---

## Recomendación práctica

La forma más segura de hacerlo es esta:

1. Genera un primer borrador con una IA usando los prompts anteriores.
2. Ajusta el contenido a tu proyecto real.
3. Revisa que todos los comandos existen de verdad en tu `Makefile`.
4. Revisa que rutas, dominios, volúmenes y nombres de servicios coinciden con tu implementación.
5. Haz una lectura final pensando en la defensa: todo lo que pongas debes poder explicarlo.

