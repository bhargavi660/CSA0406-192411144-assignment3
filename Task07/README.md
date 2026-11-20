# Task 07 — Smart-Factory Edge Memory Plan

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 edge_latencies.c -o edge_latencies
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 edge_model.c -o edge_model
./edge_latencies 16777216 1000
./edge_model
python3 memory_budget.py
```

`mlock()` is attempted only with the same user and can fail with EPERM or EAGAIN.
