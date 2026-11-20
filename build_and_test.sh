#!/usr/bin/env bash
set -u
ROOT="$(cd "$(dirname "$0")" && pwd)"
LOG="$ROOT/results-build-test.txt"
: > "$LOG"
run() {
    echo "\$ $*" >> "$LOG"
    "$@" >> "$LOG" 2>&1
    status=$?
    echo "exit=$status" >> "$LOG"
    return 0
}

cd "$ROOT/Task01" && run bash build.sh
cd "$ROOT/Task02" &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 page_table.c -o page_table &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 page_table_size.c -o page_table_size &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 eat.c -o eat &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 fragmentation.c -o fragmentation &&
  run ./eat 0.95 100 10 100 &&
  run python3 tlb_ratio.py

cd "$ROOT/Task03" &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 segment_table.c -o segment_table &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 safe_seg_fault.c -o safe_seg_fault &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 segment_alloc.c -o segment_alloc &&
  run ./segment_table &&
  run ./safe_seg_fault &&
  run ./segment_alloc

cd "$ROOT/Task04" &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 fault_access.c -o fault_access &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 cow_demo.c -o cow_demo &&
  run ./cow_demo &&
  run python3 page_fault_calculator.py &&
  run python3 reference_string_faults.py

cd "$ROOT/Task05" &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 page_replacement.c -o page_replacement &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 lru_todo.c -o lru_todo &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 benchmark.c -o benchmark &&
  run ./page_replacement &&
  run ./lru_todo &&
  run ./benchmark &&
  run python3 generate_workloads.py

cd "$ROOT/Task06" &&
  run python3 disk_calculator.py &&
  run python3 read_file_benchmark.py README.md --mi-b 1

cd "$ROOT/Task07" &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 edge_latencies.c -o edge_latencies &&
  run gcc -std=c11 -Wall -Wextra -Wpedantic -O2 edge_model.c -o edge_model &&
  run ./edge_latencies 16777216 1000 &&
  run ./edge_model &&
  run python3 memory_budget.py

cd "$ROOT"
run uname -a
run lsb_release -a
run gcc --version
