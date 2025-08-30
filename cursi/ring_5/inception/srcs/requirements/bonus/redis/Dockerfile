FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

# 1. Install Redis, redis-cli, and envsubst
RUN apt-get update && apt-get install -y --no-install-recommends \
    redis-server redis-tools gettext-base \
 && rm -rf /var/lib/apt/lists/*

# 2. Copy custom redis.conf and entrypoint script
COPY conf/redis.conf /etc/redis/redis.conf
COPY redis-setup.sh /redis-setup.sh
RUN chmod +x /redis-setup.sh

# 3. Healthcheck to ping Redis
HEALTHCHECK --interval=60s --timeout=5s --retries=5 \
  CMD redis-cli -p "${REDIS_PORT:-6379}" --no-auth-warning --user default \
      --passfile /etc/redis/healthcheck.conf ping | grep -q PONG || exit 1

# 4. Define entrypoint
ENTRYPOINT ["/redis-setup.sh"]