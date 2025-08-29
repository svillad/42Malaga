FROM debian:bookworm-slim

# Install Redis, redis-cli and envsubst
RUN apt-get update && apt-get install -y --no-install-recommends \
    redis-server redis-tools gettext-base \
 && rm -rf /var/lib/apt/lists/*


# Copy custom redis.conf if provided
COPY conf/redis.conf /etc/redis/redis.conf

# Healthcheck script
RUN printf '#!/bin/sh\nredis-cli -a "$REDIS_PASS" -p "${REDIS_PORT:-6379}" ping | grep -q PONG\n' > /healthcheck.sh && chmod +x /healthcheck.sh

HEALTHCHECK --interval=10s --timeout=5s --retries=5 \
  CMD /healthcheck.sh || exit 1

# Run Redis with our config
CMD ["sh", "-c", "envsubst < /etc/redis/redis.conf > /tmp/redis.conf && exec redis-server /tmp/redis.conf"]