#include <inttypes.h>
#include <stdio.h>

int main(void) {
    puts("Assumption: PTE=8 bytes, page=4 KiB");
    puts("32-bit flat table: 1,048,576 entries, 8 MiB");
    puts("48-bit flat 4-KiB-PTE table: 2^36 entries/leaf level, 512 GiB for a full leaf table");
    puts("A 48-bit 4-level walk has 512 entries per 9-bit PTE level; only 9 bits are used in a complete flat leaf.");
    return 0;
}
