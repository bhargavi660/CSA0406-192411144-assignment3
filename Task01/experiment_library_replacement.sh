#!/usr/bin/env bash
set -euo pipefail
mkdir -p results
LD_LIBRARY_PATH="$PWD/lib_versions/one" ./app_dynamic | tee results/library_v1.txt
LD_LIBRARY_PATH="$PWD/lib_versions/two" ./app_dynamic | tee results/library_v2.txt
