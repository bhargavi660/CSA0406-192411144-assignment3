#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>

static unsigned long long now_ns(void) {
    struct timespec t; clock_gettime(CLOCK_MONOTONIC,&t);
    return (unsigned long long)t.tv_sec*1000000000ULL+t.tv_nsec;
}

int main(int argc,char **argv) {
    size_t n=argc>1?strtoull(argv[1],NULL,10):16777216;
    int loops=argc>2?atoi(argv[2]):1000;
    if(n>256*1024*1024||loops>100000){puts("refusing oversized test");return 1;}
    unsigned char *p=malloc(n);if(!p){perror("malloc");return 1;}
    memset(p,1,n);
    int lock_status=mlock(p,n);
    if(lock_status!=0)printf("mlock failed errno=%d (%s)\n",errno,strerror(errno));
    else puts("mlock succeeded");
    unsigned long long start=now_ns();
    unsigned long long latency_sum=0;
    for(int i=0;i<loops;i++){
        unsigned long long l=now_ns();
        volatile unsigned char x=p[(i*4096)%n];(void)x;
        latency_sum+=now_ns()-l;
    }
    unsigned long long elapsed=now_ns()-start;
    printf("buffer_bytes=%zu loops=%d elapsed_ns=%llu average_sample_ns=%llu\n",
           n,loops,elapsed,latency_sum/(unsigned long)loops);
    if(lock_status==0)munlock(p,n);
    free(p);return 0;
}
