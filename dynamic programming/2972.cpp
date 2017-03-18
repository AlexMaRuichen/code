#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
const int maxn=1010;
const int maxm=(maxn*10)<<1;
int n,e;
int dis[maxn];
struct cow
{
    int id,q;
    bool operator < (const cow &s) const
    {
        return q>s.q;
    }
}c[maxn];

int to[maxm];
int next[maxm];
int head[maxn];
int tot;
void add(int x,int y)
{
    to[++tot]=y;
    next[tot]=head[x];
    head[x]=tot;

    to[++tot]=x;
    next[tot]=head[y];
    head[y]=tot;
}

queue <int> q;
int f[maxn];
int ans;
void bfs()
{
	int k,i,t,S;
    for(k=1;k<=n;k++)
    {
        S=c[k].id;
        memset(dis,-1,sizeof(int)*(n+2));
        q.push(S);
        dis[S]=0;
        while(!q.empty())
        {
            static int x;
            x=q.front();
            q.pop();
            for(int i=head[x];i;i=next[i])
                if(dis[to[i]]<0)
                    dis[to[i]]=dis[x]+1,q.push(to[i]);
        }
        t=c[k].q;
        for(i=1;i<=n;i++)
            if(dis[i]!=-1)
                t=max(t,c[k].q+f[i]-e*dis[i]);
        f[S]=t;
        ans=max(ans,t);
    }
}
int main()
{

    scanf("%d%d",&n,&e);
    for(int i=1;i<=n;i++)
    {
        static int d;
        c[i].id=i;
        scanf("%d%d",&c[i].q,&d);
        while(d--)
        {
            static int x;
            scanf("%d",&x);
            add(i,x);
        }
    }
    sort(c+1,c+n+1);
    bfs();
    printf("%d\n",ans);
}
