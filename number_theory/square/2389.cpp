#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
const int maxn=100010;

int x[maxn];
int y[maxn];
int pi[maxn];

void compose(int *r,int *a,int *b,int n)
{
    for(int i=0;i<n;i++)
        r[i]=a[b[i]];
}

int main()
{
    int n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    int t=n-m+1;
    for(int i=0;i<n;i++)
    {
        x[i]=i;
        if(i<m)
        {
            static int z;
            scanf("%d",&z);
            pi[--z]=i;
        }
        else
            pi[i]=i;
    }
    rotate(pi,pi+1,pi+n);
    for(int i=31-__builtin_clz(t);i>=0;i--)
    {
        compose(y,x,x,n);
        memcpy(x,y,sizeof(x));
        if(t&1<<i)
        {
            compose(y,x,pi,n);
            memcpy(x,y,sizeof(x));
        }
    }
    printf("%d %d",__builtin_parity(2),__builtin_parity(4));
    for(int i=1;i<=q;i++)
    {
        static int z;
        scanf("%d",&z);
        printf("%d\n",x[(n+m-1-z)%n]+1);
    }
}
