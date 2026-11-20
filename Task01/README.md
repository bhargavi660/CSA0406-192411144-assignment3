# Task 01 — Linking, Loading and Address Binding

```bash
chmod +x build.sh experiment_library_replacement.sh
./build.sh
./app_static
./app_dynamic
LD_LIBRARY_PATH="$PWD/lib_versions/one:$PWD/lib_versions/two" ./app_dynamic_dlopen
bash experiment_library_replacement.sh
python3 print_process_mappings.py
```

Outputs are actual only after local execution. Put real captures in `results/`.
