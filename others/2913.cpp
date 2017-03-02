#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=100010;
int n;
int ans;
int pos[maxn];
int s[maxn];
long long t;
int last;
int main()
{
    scanf("%d%lld",&n,&t);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&pos[i],&s[i]);
    pos[n+1]=s[n+1]=~0u>>1;
    last=n+1;
    for(int i=n;i;i--)
    {
        if(pos[i]+s[i]*t<pos[last]+s[last]*t)
            ++ans,last=i;
    }
    printf("%d\n",ans);
}
