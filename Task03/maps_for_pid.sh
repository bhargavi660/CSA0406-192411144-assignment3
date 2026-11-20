#!/usr/bin/env bash
set -euo pipefail
if [ "$#" -ne 1 ]; then echo "Usage: $0 PID"; exit 1; fi
pid="$1"
if [ -r "/proc/$pid/maps" ]; then cat "/proc/$pid/maps"; else echo "/proc/$pid/maps unavailable"; fi
