#include <stdio.h>
#include <string.h>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn=5e5+10;
int n,m;
int start,p;
int pub[maxn];
int money[maxn];
long long moneyb[maxn];

int to[maxn];
int to_[maxn];
int next[maxn];
int next_[maxn];
int head[maxn];
int head_[maxn];
int tot;
int tot_;
void add(int x,int y)
{
    to[++tot]=y;
    next[tot]=head[x];
    head[x]=tot;
}
void add_(int x,int y)
{
    to_[++tot_]=y;
    next_[tot_]=head_[x];
    head_[x]=tot_;
}

int size[maxn];
int scc;
int belong[maxn];
stack <int> s;
bool v[maxn];
bool ins[maxn];
int low[maxn];
int dfn[maxn];
int cnt;
void dfs(int x)
{
    dfn[x]=low[x]=++cnt;
    v[x]=ins[x]=true;
    s.push(x);
    for(int i=head[x];i;i=next[i])
    if(!v[to[i]])
    {
        dfs(to[i]);
        low[x]=min(low[x],low[to[i]]);
    }
    else if(ins[to[i]])
    low[x]=min(low[x],dfn[to[i]]);
    if(dfn[x]==low[x])
    {
        int now=0;
        ++scc;
        while(now!=x)
        {
            now=s.top();
            s.pop();
            ins[now]=false;
            belong[now]=scc;
            moneyb[scc]+=money[now];
            ++size[scc];
        }
    }
}
void rebuild()
{
    for(int x=1;x<=n;x++)
        for(int i=head[x];i;i=next[i])
            if(belong[x]!=belong[to[i]])
                add_(belong[x],belong[to[i]]);
}
void tarjan()
{
    for(int i=1;i<=n;i++)
        if(!v[i])
            dfs(i);
    rebuild();
}

queue <int> q;
long long f[maxn];
void spfa()
{
    memset(v,0,sizeof(v));
    q.push(belong[start]);
    v[belong[start]]=true;
    f[belong[start]]=moneyb[belong[start]];
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        v[x]=false;
        for(int i=head_[x];i;i=next_[i])
        {
            if(f[x]+moneyb[to_[i]]>f[to_[i]])
            {
                f[to_[i]]=f[x]+moneyb[to_[i]];
                if(!v[to_[i]])
                {
                    v[to_[i]]=true;
                    q.push(to_[i]);
                }
            }
        }
    }
}


int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        static int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&money[i]);
    scanf("%d%d",&start,&p);
    for(int i=1;i<=p;i++)
        scanf("%d",&pub[i]);

    tarjan();
    spfa();

    long long ans=0;
    for(int i=1;i<=p;i++)
        ans=max(ans,f[belong[pub[i]]]);

    printf("%lld\n",ans);
}
