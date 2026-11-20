# Task 04 — Virtual Memory and Demand Paging

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 fault_access.c -o fault_access
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 cow_demo.c -o cow_demo
./fault_access 67108864 1000000 1
./cow_demo
python3 page_fault_calculator.py
python3 reference_string_faults.py
```

The access program warns before allocations and accepts only safe explicit values.
