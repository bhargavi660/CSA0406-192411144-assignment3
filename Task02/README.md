# Task 02 — Paging

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 page_table.c -o page_table
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 page_table_size.c -o page_table_size
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 eat.c -o eat
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 fragmentation.c -o fragmentation
./page_table
./eat
./page_table_size
./fragmentation
getconf PAGESIZE
/usr/bin/time -v ./page_table
```

No output has been filled with guessed values.
