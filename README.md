# CSA0496-192411144-Assignment3

**Name:** `[STUDENT NAME TO FILL]`  
**Register Number:** `192411144`  
**Repository Name:** `CSA0406-192411144-Assignment3`

> GitHub is intentionally not created or published. Add the verified URL here after you create it:
> **Repository URL:** https://github.com/bhargavi660/CSA0406-192411144-assignment3.git

## Environment collection

- Compiler: **Collected by GCC 15.2.0** (`gcc (Ubuntu 15.2.0-16ubuntu1)`)
- Linux distribution: **Collected: Ubuntu 26.04 LTS (WSL2)**
- OS running these tasks: **Ubuntu 26.04 LTS under WSL2, kernel 6.18.33.2-microsoft-standard-WSL2**

## Project layout

```text
Task01/ Task02/ Task03/ Task04/ Task05/ Task06/ Task07/
report/ evidence/
```

Every task has source/configuration/scripts and a `results/` directory. Actual output is saved only after execution.

## Build/run commands

Each task README contains exact commands. On Linux or WSL:

```bash
# Task 1
cd Task01
bash build.sh
./app_dynamic
./app_dynamic_dlopen
bash experiment_library_replacement.sh
python3 print_process_mappings.py

# Task 2
cd ../Task02
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 page_table.c -o page_table
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 page_table_size.c -o page_table_size
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 eat.c -o eat
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 fragmentation.c -o fragmentation
./page_table
./fragmentation

# Task 3
cd ../Task03
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 segment_table.c -o segment_table
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 safe_seg_fault.c -o safe_seg_fault
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 segment_alloc.c -o segment_alloc
./segment_table
./safe_seg_fault
./segment_alloc

# Task 4
cd ../Task04
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 fault_access.c -o fault_access
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 cow_demo.c -o cow_demo
./fault_access 67108864 1000000 1
./cow_demo
python3 page_fault_calculator.py
python3 reference_string_faults.py

# Task 5
cd ../Task05
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 page_replacement.c -o page_replacement
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 lru_todo.c -o lru_todo
./page_replacement
python3 generate_workloads.py
python3 benchmark_placeholder.py

# Task 6
cd ../Task06
python3 disk_calculator.py
bash collect_disks.sh

# Task 7
cd ../Task07
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 edge_latencies.c -o edge_latencies
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 edge_model.c -o edge_model
./edge_latencies 16777216 1000
./edge_model
python3 memory_budget.py
```

Windows PowerShell cannot execute Linux `/proc`, shared-library, fork, or POSIX memory APIs as native Windows binaries. Use WSL or a Linux machine for these tasks.

## Short result notes

- WSL Ubuntu compilation and safe tests were executed with GCC 15.2.0.
- Actual library replacement output: `demo-library-output-v1` and `demo-library-output-v2`.
- Page-replacement actual faults: FIFO 15/10, LRU 12/8, Optimal 9/8, Clock 14/9 for 3/4 frames.
- Paging tests produced address 4096 and 8192 as invalid (page 4 beyond 4 allocated pages).
- WSL benchmark for 100,000 references measured 0.001069 seconds; timing is noisy and not a purchase claim.
- Edge latency test measured 324748 ns total over 1000 loops with `mlock()` successful.

## Evidence checklist

- [ ] Capture `gcc --version`, `lsb_release -a`, and `uname -a`
- [ ] Capture Task 01 executable sizes and `ldd`, plus library-replacement output
- [ ] Capture Task 02 page-table output at 1024 and 2048 bytes/page
- [ ] Capture `/usr/bin/time -v` and `getconf PAGESIZE` if available
- [ ] Capture Task 03 `/proc/<pid>/maps` while a process is running
- [ ] Capture Task 04 `getrusage` results and the 24 GB/16 GB scenario labels
- [ ] Capture Task 05 benchmark machine details and elapsed times
- [ ] Capture Task 06 `lsblk`; review/redact device identifiers before sharing
- [ ] Capture Task 07 `mlock` status and control-loop latency
