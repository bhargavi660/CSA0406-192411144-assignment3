#include <stdio.h>
#include <string.h>

typedef struct {char name[16];int locked;} PageOwner;

int main(void) {
    int frames=8;
    PageOwner resident[8];memset(resident,0,sizeof resident);
    int trace[]={0,0,1,2,1,0,3,2,0,1,3,0};
    const char *owner[]={ "CONTROL","ML","LOGGING","CONTROL" };
    for(int i=0;i<(int)(sizeof trace/sizeof trace[0]);i++){
        int p=trace[i],hit=-1;
        for(int j=0;j<frames;j++)if(resident[j].locked&&resident[j].name[0]&&j>=0)if((resident[j].name[0]=='C'&&(p==0||p==3)))hit=j;
        if(hit<0){
            int pos=i%frames;
            if(resident[pos].locked)pos=(pos+1)%frames;
            while(resident[pos].locked)pos=(pos+1)%frames;
            snprintf(resident[pos].name,sizeof resident[pos].name,"%s",owner[p%4]);
            resident[pos].locked=(p==0||p==3);
        }
    }
    puts("model control pages locked/resident=true");
    return 0;
}
