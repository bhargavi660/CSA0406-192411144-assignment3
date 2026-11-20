#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

static unsigned long long now_ns(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (unsigned long long)t.tv_sec * 1000000000ULL + t.tv_nsec;
}

int main(int argc, char **argv) {
    size_t bytes = argc > 1 ? strtoull(argv[1], NULL, 10) : 67108864;
    size_t accesses = argc > 2 ? strtoull(argv[2], NULL, 10) : 1000000;
    int random_mode = argc > 3 ? atoi(argv[3]) : 1;
    if (bytes > (size_t)512*1024*1024 || accesses > 20000000) {
        fprintf(stderr, "Refusing: use <=512 MiB and <=20 million accesses\n");
        return 1;
    }
    unsigned char *p = calloc(bytes, 1);
    if (!p) { perror("calloc"); return 1; }
    struct rusage before, after;
    getrusage(RUSAGE_SELF, &before);
    unsigned long long start = now_ns();
    unsigned long state = 1234567;
    volatile unsigned char sink = 0;
    for (size_t i = 0; i < accesses; ++i) {
        size_t index;
        if (random_mode) {
            state = state * 1103515245UL + 12345UL;
            index = (state % bytes);
        } else index = (i * 4096) % bytes;
        sink ^= p[index];
    }
    unsigned long long elapsed = now_ns() - start;
    getrusage(RUSAGE_SELF, &after);
    printf("bytes=%zu accesses=%zu mode=%s elapsed_ns=%llu minor_faults=%ld\n",
           bytes, accesses, random_mode ? "random" : "sequential",
           elapsed, after.ru_minflt - before.ru_minflt);
    (void)sink;
    free(p);
    return 0;
}
