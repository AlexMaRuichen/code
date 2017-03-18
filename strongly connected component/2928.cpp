#include <stdio.h>
#include <stack>
#include <queue>
#include <map>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
int n,m;
struct Adjacency_List
{
    int to[maxn];
    int next[maxn];
    int head[maxn];
    int deg[maxn];
    int tot;
    void add(int x,int y)
    {
        to[++tot]=y;
        ++deg[y];
        next[tot]=head[x];
        head[x]=tot;
    }
	Adjacency_List()
	{
		tot=0;
		memset(head,0,sizeof(head));
	}
}*G,*T,*R;

struct Tarjan
{
    bool v[maxn];
    bool ins[maxn];
    int scc;
    int size[maxn];
    int dfn[maxn];
    int low[maxn];
    int belong[maxn];
    int cnt;
    stack <int> s;
    void dfs(int x)
    {
        v[x]=ins[x]=true;
        dfn[x]=low[x]=++cnt;
        s.push(x);
        for(int i=G->head[x];i;i=G->next[i])
            if(!v[G->to[i]])
                dfs(G->to[i]),low[x]=min(low[x],low[G->to[i]]);
            else if(ins[G->to[i]])
                low[x]=min(low[x],dfn[G->to[i]]);
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
                ++size[scc];
            }
        }
    }
    void rebuild()
    {
        for(int x=1;x<=n;x++)
            for(int i=G->head[x];i;i=G->next[i])
                if(belong[G->to[i]]!=belong[x])
                    T->add(belong[x],belong[G->to[i]]),R->add(belong[G->to[i]],belong[x]);
    }
    void process()
    {
        for(int i=1;i<=n;i++)
            if(!v[i])
                dfs(i);
        rebuild();
    }
}tarjan;

queue <int> q;
int f[maxn];
int r[maxn];
int ans;
void longest_path(Adjacency_List* &G,int (&f)[maxn])
{
    memset(f,0xef,sizeof(f));
    f[tarjan.belong[1]]=tarjan.size[tarjan.belong[1]];
    for(int i=1;i<=tarjan.scc;i++)
        if(!G->deg[i])
            q.push(i);
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        for(int i=G->head[x];i;i=G->next[i])
        {
            f[G->to[i]]=max(f[x]+tarjan.size[G->to[i]],f[G->to[i]]);
            --G->deg[G->to[i]];
            if(!G->deg[G->to[i]])
                q.push(G->to[i]);
        }
    }
}

int main()
{
	G=new Adjacency_List();
	T=new Adjacency_List();
	R=new Adjacency_List();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        static int x,y;
        scanf("%d%d",&x,&y);
        G->add(x,y);
    }
    tarjan.process();
    longest_path(T,f);
    longest_path(R,r);
    ans=tarjan.size[tarjan.belong[1]]<<1;
    for(int x=1;x<=n;x++)
        for(int i=G->head[x];i;i=G->next[i])
            ans=max(ans,f[tarjan.belong[G->to[i]]]+r[tarjan.belong[x]]);
    printf("%d\n",ans-tarjan.size[tarjan.belong[1]]);
}
