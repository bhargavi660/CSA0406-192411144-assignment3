#include <stdio.h>
#include <string.h>

typedef struct { int page, time, present; } Frame;

int main(void) {
    int refs[]={1,2,3,4,1,2,5,1,2,3,4,5};
    int n=3,time=1,faults=0;
    Frame f[3]; memset(f,0,sizeof f);
    for(size_t i=0;i<sizeof refs/sizeof refs[0];i++){
        int hit=-1;
        for(int j=0;j<n;j++)if(f[j].present&&f[j].page==refs[i])hit=j;
        if(hit>=0){f[hit].time=time++;continue;} faults++;
        int pos=-1;
        for(int j=0;j<n;j++)if(!f[j].present){pos=j;break;}
        if(pos<0){pos=0;for(int j=1;j<n;j++)if(f[j].time<f[pos].time)pos=j;}
        f[pos]=(Frame){refs[i],time++,1};
    }
    printf("LRU supplied-TODO faults=%d\n",faults);
    return 0;
}
