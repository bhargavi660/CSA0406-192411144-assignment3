# Task 03 — Segmentation

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 segment_table.c -o segment_table
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 safe_seg_fault.c -o safe_seg_fault
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 segment_alloc.c -o segment_alloc
./segment_table
./safe_seg_fault
./segment_alloc
```

The segmentation fault demo is child-process guarded and may differ by OS.
