#!/usr/bin/env bash
set -euo pipefail
mkdir -p results
{
  echo "1024-byte pages:"
  printf "1023\n1024\n4095\n4096\n-1\n" | ./page_table 1024
  echo "2048-byte pages:"
  printf "2047\n2048\n8191\n8192\n-1\n" | ./page_table 2048
} | tee results/page_table_tests.txt
