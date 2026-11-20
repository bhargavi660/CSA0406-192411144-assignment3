#include <stdio.h>
#include <stdlib.h>

typedef struct { int used; size_t size; } Block;

int main(void) {
    const size_t memory_size = 4096;
    Block memory[memory_size];
    for (size_t i = 0; i < memory_size; ++i) memory[i].used = 0, memory[i].size = 1;
    unsigned long state = 0x5EA2026UL;
    size_t allocated = 0;
    printf("policy=first-fit; seed=0x%lX; external_fragmentation=unallocated_noncontiguous_runs\n", state);
    for (int k = 0; k < 20; ++k) {
        state = state * 1103515245UL + 12345UL;
        size_t size = (state % 250UL) + 16UL;
        size_t hole = 0;
        for (size_t i = 0; i + size <= memory_size; ++i) {
            int fit = 1;
            for (size_t j = 0; j < size; ++j) if (memory[i + j].used) fit = 0;
            if (fit) { hole = i; break; }
        }
        if (hole == 0 && (memory[0].used || size > memory_size)) {
            printf("LOAD %d size=%zu rejected\n", k + 1, size);
        } else {
            for (size_t j = hole; j < hole + size; ++j) memory[j].used = 1;
            allocated += size;
            printf("LOAD %d size=%zu at=%zu\n", k + 1, size, hole);
        }
        if (k == 9) {
            printf("REMOVE indices 0-9; conceptual deterministic removal complete\n");
            for (size_t i = 0; i < memory_size / 2; ++i) memory[i].used = 0;
        }
    }
    printf("allocated_bytes=%zu\n", allocated);
    return 0;
}
