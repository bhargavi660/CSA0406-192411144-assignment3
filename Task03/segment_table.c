#include <stdio.h>
#include <stdlib.h>

typedef struct { long base; long limit; } Segment;

int translate(Segment s, long offset, long *physical) {
    if (offset < 0 || offset > s.limit) return 0;
    *physical = s.base + offset;
    return 1;
}

int main(void) {
    Segment segments[] = {{100, 100}, {500, 200}, {1000, 150}, {300, 80},
                          {700, 120}, {1500, 300}, {200, 60}, {900, 90}};
    long addresses[][2] = {{0,0},{0,100},{0,101},{1,150},{1,200},{2,149},{7,90},{7,91}};
    for (size_t i = 0; i < sizeof(addresses)/sizeof(addresses[0]); ++i) {
        long segment = addresses[i][0], offset = addresses[i][1], physical;
        if (translate(segments[segment], offset, &physical))
            printf("segment %ld offset %ld -> physical %ld\n", segment, offset, physical);
        else
            printf("segment %ld offset %ld -> LIMIT VIOLATION (limit %ld)\n",
                   segment, offset, segments[segment].limit);
    }
    return 0;
}
