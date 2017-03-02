#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=1e6+10;
int n,m;
int r[maxn];
int d[maxn];
int b[maxn];
int e[maxn];
int c[maxn];
int cur,las;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&cur);
        r[i]=cur-las;
        las=cur;
    }
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&c[i],&b[i],&e[i]);
    for(int i=1;i<=m;i++)
    {
        int x=0;
        r[b[i]]-=c[i],r[e[i]+1]+=c[i];
        for(int j=1;j<=n;j++)
        {
            x+=r[j];
            if(x<0)
            {
                printf("-1\n%d\n",i);
                return 0;
            }
        }
    }
    puts("0");
}
