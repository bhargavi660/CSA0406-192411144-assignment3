# Task 05 — Page Replacement

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 page_replacement.c -o page_replacement
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 lru_todo.c -o lru_todo
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 benchmark.c -o benchmark
./page_replacement
./lru_todo
./benchmark
python3 generate_workloads.py
```
