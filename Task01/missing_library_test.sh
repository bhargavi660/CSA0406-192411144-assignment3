#!/usr/bin/env bash
set -u
mkdir -p /tmp/assignment3_missing_test
./app_dynamic_dlopen /tmp/assignment3_missing_test/libmissing.so
