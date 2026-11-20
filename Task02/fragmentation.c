#include <stdio.h>
#include <stdlib.h>

int main(void) {
    unsigned long seed = 0xC5A0496UL;
    const size_t sizes[] = {1024, 4096, 2097152};
    for (size_t s = 0; s < sizeof(sizes)/sizeof(sizes[0]); ++s) {
        unsigned long state = seed;
        unsigned long wasted = 0;
        printf("PAGE_SIZE,%zu\n", sizes[s]);
        for (int i = 0; i < 100; ++i) {
            state = state * 1103515245UL + 12345UL;
            size_t process_size = (state % 1048576UL) + 1UL;
            size_t frag = (sizes[s] - (process_size % sizes[s])) % sizes[s];
            wasted += frag;
            printf("%d,%zu,%zu\n", i + 1, process_size, frag);
        }
        printf("TOTAL_WASTE,%lu\n", wasted);
    }
    return 0;
}
