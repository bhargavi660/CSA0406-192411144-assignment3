#!/usr/bin/env bash
set -euo pipefail
mkdir -p results
{
  echo "Executable sizes:"
  stat -c "%n %s bytes" app_static app_dynamic app_dynamic_dlopen
  echo "Dynamic dependencies:"
  ldd app_dynamic
} | tee results/linking_comparison.txt
