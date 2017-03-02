#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e3+10;
int n,m;
long long k;
int l[maxn];
int r[maxn];
char s[10];
bool v[maxn];
int to[maxn];

int main()
{

    scanf("%d%d%lld",&n,&m,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&l[i],&r[i]);
        to[i]=i;
    }

    for(int i=1;i<=m;i++)
    {
        scanf("%s",s);
        if(s[0]=='L')
            for(int i=1;i<=n;i++)
                to[i]=l[to[i]];
        else
            for(int i=1;i<=n;i++)
                to[i]=r[to[i]];
    }

    int c=1;
    for(;k;k--)
    {
        if(v[c])
            break;
        v[c]=true;
        c=to[c];
    }

    if(k)
    {
        int t=0;
        int start=c;
        do
        {
            ++t;
            c=to[c];
        }
        while(c!=start);
        k%=t;
        while(k--)
            start=to[start];
        printf("%d\n",start);
    }
    else
        printf("%d\n",c);
}
