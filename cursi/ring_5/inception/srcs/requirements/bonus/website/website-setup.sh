#!/bin/sh

# Generate config.js at startup with environment variables
cat <<EOF > /app/build/config.js
window.RUNTIME_CONFIG = {
  LOGIN: "${LOGIN:-guest}"
};
EOF

# Execute the command passed to the container (serve)
exec "$@"
