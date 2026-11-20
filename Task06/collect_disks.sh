#!/usr/bin/env bash
set -euo pipefail
mkdir -p results
lsblk -o NAME,SIZE,TYPE,FSTYPE,MOUNTPOINTS | tee results/lsblk.txt
if command -v fdisk >/dev/null 2>&1; then
  echo "REVIEW DEVICE IDENTIFIERS BEFORE SHARING" | tee results/fdisk.txt
  fdisk -l 2>&1 | tee -a results/fdisk.txt
else
  echo "fdisk unavailable" | tee results/fdisk.txt
fi
