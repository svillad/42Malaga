FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive
WORKDIR /app

# 1. Node.js + npm + tools to build and serve
RUN apt-get update && apt-get install -y --no-install-recommends \
    nodejs npm ca-certificates curl \
 && rm -rf /var/lib/apt/lists/*

# 2. Copy package*.json first to leverage Docker cache for dependencies
COPY src/package*.json ./

# 3. Install dependencies
RUN npm install

# 4. Copy the rest of the source code and build
COPY src/ ./
RUN npm run build \
 && npm cache clean --force \
 && rm -rf node_modules

# 5. Static server for production
RUN npm install -g serve

# 6. Entrypoint: generates config.js with environment variables
COPY website-setup.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/website-setup.sh

# 7. Non-root user and adjust permissions for /app directory
RUN useradd -m appuser \
 && chown -R appuser:appuser /app
USER appuser

# 8. Healthcheck for Website (check if port 3000 responds)
HEALTHCHECK --interval=60s --timeout=5s --retries=5 \
  CMD curl -fsS http://127.0.0.1:3000/ >/dev/null || exit 1

# 9. Define entrypoint
ENTRYPOINT ["website-setup.sh"]
CMD ["serve", "-s", "build", "-l", "3000"]