#!/usr/bin/env sh

# 1. Logging helper
log() {
  printf "[website][%s] %s\n" "$(date -u +"%Y-%m-%dT%H:%M:%SZ")" "$*" >&2
}

# 2. Generate frontend runtime configuration (config.js) from environment
cat <<EOF > /app/build/config.js
window.RUNTIME_CONFIG = {
  LOGIN: "${LOGIN:-guest}"
};
EOF

# 3. Start the main process passed as CMD/ENTRYPOINT
log "✅ Provision complete. Launching website"
exec "$@"