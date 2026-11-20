#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    const int n=100000;
    int *refs=malloc((size_t)n*sizeof *refs);
    if(!refs){perror("malloc");return 1;}
    for(int i=0;i<n;i++)refs[i]=(i*37)%256;
    struct timespec start,end;clock_gettime(CLOCK_MONOTONIC,&start);
    int frames=16,resident=0;
    int frameset[16];for(int i=0;i<16;i++)frameset[i]=-1;
    long faults=0;
    for(int i=0;i<n;i++){int hit=-1;for(int j=0;j<resident;j++)if(frameset[j]==refs[i])hit=j;
        if(hit>=0) continue;
        faults++;
        if(resident<frames)frameset[resident++]=refs[i];
        else frameset[i%frames]=refs[i];}
    clock_gettime(CLOCK_MONOTONIC,&end);
    double elapsed=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1e9;
    printf("references=%d faults=%ld elapsed_seconds=%.6f\n",n,faults,elapsed);
    free(refs);return 0;
}
