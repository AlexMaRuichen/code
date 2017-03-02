#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=1e6+10;
int n,m;
long long r[maxn];
long long d[maxn];
int b[maxn];
int e[maxn];
long long c[maxn];
int cur,las;
bool check(int mid)
{
    static long long x;
    x=0;
    memcpy(d,r,sizeof(r));
    for(int i=1;i<=mid;i++)
        d[b[i]]-=c[i],d[e[i]+1]+=c[i];
    for(int i=1;i<=n;i++)
    {
        x+=d[i];
        if(x<0)
            return false;
    }
    return true;
}
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
        scanf("%lld%d%d",&c[i],&b[i],&e[i]);
    int l=0,r=m+1,mid;
    while(l<r)
        mid=(l+r)>>1,check(mid)?l=mid+1:r=mid;
    if(l!=m+1)
        printf("-1\n%d\n",l);
    else
        puts("0");
}
