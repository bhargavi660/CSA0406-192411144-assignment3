#!/usr/bin/env bash
set -euo pipefail
mkdir -p lib_versions/one lib_versions/two results

gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -fPIC -c demo_app.c -o demo_app.o
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -fPIC -c demo.c -o demo.o
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -fPIC -c demo_v2.c -o demo_v2.o
ar rcs libdemo.a demo.o
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 demo_app.o libdemo.a -o app_static
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -fPIC -shared demo.c -o lib_versions/one/libdemo.so
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -fPIC -shared demo_v2.c -o lib_versions/two/libdemo.so
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -fPIC demo_app.c -Llib_versions/one -ldemo -Wl,-rpath,'$ORIGIN/lib_versions/one' -o app_dynamic
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 dlopen_app.c -ldl -o app_dynamic_dlopen
