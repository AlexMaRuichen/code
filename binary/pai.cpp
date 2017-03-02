#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define min(x,y) (x)<(y)?(x):(y)
#define max(x,y) (x)>(y)?(x):(y)
void gen()
{
    FILE *p=fopen("a.in","w");
    int n=rand()%10000+1;
    int m=rand()%n+1;
    fprintf(p,"%d %d\n",n,m);
    for(int i=1;i<=n;i++)
        fprintf(p,"%d ",rand()%2000+1);
    fprintf(p,"\n");
    for(int i=1;i<=m;i++)
    {
        int x=rand()%1000+1;
        int l=rand()%n+1;
        int r=rand()%n+1;
        fprintf(p,"%d %d %d\n",x,min(l,r),max(l,r));
    }
    fclose(p);
}
int main()
{
    srand(time(NULL));
    rand();
    system("g++ 1783.cpp -o 1783 -g -Wall");
    system("g++ 1783_.cpp -o 1783_ -g -Wall");
    int cnt=0;
    while(true)
    {
        gen();
        system("./1783<a.in>a.out");
        system("./1783_<a.in>b.out");
        if(system("diff a.out b.out -bw > /dev/null"))
        {
            puts("WA");
            break;
        }
        printf("%d AC\n",++cnt);
    }
}
