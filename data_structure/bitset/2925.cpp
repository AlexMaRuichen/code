#include <stdio.h>
#include <algorithm>
#include <bitset>
#include <queue>
using namespace std;
const int maxn=110;
const int maxm=maxn*maxn;
int n,m;
int to[maxm];
int next[maxm];
int len1[maxm];
int len2[maxm];
int head[maxn];
int dg[maxn];
int tot;
void add(int x,int y,int a,int b)
{
    to[++tot]=y;
    ++dg[y];
    next[tot]=head[x];
    len1[tot]=a;
    len2[tot]=b;
    head[x]=tot;
}
bitset <10001> b[101],e[101];
queue <int> q;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        static int x,y,a,b;
        scanf("%d%d%d%d",&x,&y,&a,&b);
        add(x,y,a,b);
    }
    for(int i=1;i<=n;i++)
        if(!dg[i])
            q.push(i);
    b[1][0]=e[1][0]=true;
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        for(int i=head[x];i;i=next[i])
        {
            --dg[to[i]];
            b[to[i]]|=b[x]<<len1[i];
            e[to[i]]|=e[x]<<len2[i];
            if(!dg[to[i]])
                q.push(to[i]);
        }
    }
    for(int i=1;i<=10000;i++)
        if(b[n][i]&&e[n][i])
            return printf("%d\n",i),0;
    puts("IMPOSSIBLE");
}
