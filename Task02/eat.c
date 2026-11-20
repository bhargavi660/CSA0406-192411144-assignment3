#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    double hit_ratio = argc > 1 ? strtod(argv[1], NULL) : 0.95;
    double memory_ns = argc > 2 ? strtod(argv[2], NULL) : 100.0;
    double tlb_ns = argc > 3 ? strtod(argv[3], NULL) : 10.0;
    double miss_ns = argc > 4 ? strtod(argv[4], NULL) : 100.0;
    if (hit_ratio < 0.0 || hit_ratio > 1.0) { fprintf(stderr, "invalid hit ratio\n"); return 1; }
    double no_tlb = memory_ns;
    double tlb = hit_ratio * (tlb_ns + memory_ns) + (1.0 - hit_ratio) * (tlb_ns + miss_ns + memory_ns);
    printf("No-TLB EAT: %.3f ns\nTLB EAT: %.3f ns\n", no_tlb, tlb);
    return 0;
}
