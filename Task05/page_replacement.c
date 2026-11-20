#include <stdio.h>
#include <string.h>

typedef struct { int page, present, use, ref; } Frame;

static int find_frame(Frame *f, int n, int page) {
    for (int i=0;i<n;i++) if (f[i].present && f[i].page==page) return i;
    return -1;
}

static int fifo(int *refs, int nr, int n) {
    Frame f[n]; memset(f,0,sizeof f); int faults=0, hand=0;
    for(int i=0;i<nr;i++){int h=find_frame(f,n,refs[i]);if(h>=0)continue;faults++;
        int pos= -1; for(int j=0;j<n;j++)if(!f[j].present){pos=j;break;}
        if(pos<0){pos=hand;hand=(hand+1)%n;} f[pos]=(Frame){refs[i],1,0,0};}
    return faults;
}

static int lru(int *refs, int nr, int n) {
    Frame f[n]; memset(f,0,sizeof f); int faults=0,time=1;
    for(int i=0;i<nr;i++){int h=find_frame(f,n,refs[i]);if(h>=0){f[h].use=time++;continue;}faults++;
        int pos=-1;for(int j=0;j<n;j++)if(!f[j].present){pos=j;break;}
        if(pos<0){pos=0;for(int j=1;j<n;j++)if(f[j].use<f[pos].use)pos=j;}
        f[pos]=(Frame){refs[i],1,time++,0};}
    return faults;
}

static int optimal(int *refs,int nr,int n) {
    Frame f[n]; memset(f,0,sizeof f);int faults=0;
    for(int i=0;i<nr;i++){int h=find_frame(f,n,refs[i]);if(h>=0)continue;faults++;
        int pos=-1;for(int j=0;j<n;j++)if(!f[j].present){pos=j;break;}
        if(pos<0){
            pos=0;
            int farthest=-1;
            for(int j=0;j<n;j++){
                int next=nr;
                for(int k=i+1;k<nr;k++) if(refs[k]==f[j].page){next=k;break;}
                if(next>farthest){farthest=next;pos=j;}
            }
        }
        f[pos]=(Frame){refs[i],1,0,0};}
    return faults;
}

static int clock(int *refs,int nr,int n) {
    Frame f[n]; memset(f,0,sizeof f);int faults=0,hand=0;
    for(int i=0;i<nr;i++){int h=find_frame(f,n,refs[i]);if(h>=0){f[h].ref=1;continue;}faults++;
        int pos=-1;for(int j=0;j<n;j++)if(!f[j].present){pos=j;break;}
        if(pos<0){while(f[hand].ref){f[hand].ref=0;hand=(hand+1)%n;}pos=hand;hand=(hand+1)%n;}
        f[pos]=(Frame){refs[i],1,0,1};}
    return faults;
}

int main(void) {
    int refs[]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int nr=(int)(sizeof refs/sizeof refs[0]);
    puts("algorithm,frames,faults");
    for(int n=3;n<=4;n++)printf("FIFO,%d,%d\nLRU,%d,%d\nOptimal,%d,%d\nClock,%d,%d\n",
        n,fifo(refs,nr,n),n,lru(refs,nr,n),n,optimal(refs,nr,n),n,clock(refs,nr,n));
    return 0;
}
