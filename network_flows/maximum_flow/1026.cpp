#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
#define assign(x) x=++cnt
#define judge(x,y) ((x)>=1&&(x)<=n&&(y)>=1&&(y)<=m)
using namespace std;
const int maxn=30*30*4;
const int maxm=maxn*5;
const int inf=1e9;
 
int to[maxm];
int next[maxm];
int len[maxm];
int head[maxn];
int tot=1;
void add(int x,int y,int z)
{
    to[++tot]=y;
    next[tot]=head[x];
    len[tot]=z;
    head[x]=tot;
     
    to[++tot]=x;
    next[tot]=head[y];
    len[tot]=0;
    head[y]=tot;
}
 
queue <int> q;
int S=maxn-1,T=maxn-2;
int dep[maxn];
bool bfs()
{
    memset(dep,-1,sizeof(dep));
    q.push(S);
    dep[S]=1;   
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        for(int i=head[x];i;i=next[i])
            if(dep[to[i]]==-1&&len[i])
                dep[to[i]]=dep[x]+1,q.push(to[i]);
    }
    return dep[T]^-1;
}
int dfs(int x,int f)
{
    if(x==T)
        return f;
    int w,used=0;
    for(int i=head[x];i;i=next[i])
        if(len[i]&&dep[to[i]]==dep[x]+1)
        {
            w=dfs(to[i],min(len[i],f-used));
            len[i]-=w;
            len[i^1]+=w;
            used+=w;
            if(used==f)
                return f;
        }
    if(used!=f)
        dep[x]=-1;
    return used;
}
int dinic()
{
    int ans=0;
    while(bfs())
        ans+=dfs(S,~0u>>1);
    return ans;
}
 
int n,m,x,y;
int cnt;
bool map[30][30];
int id[30][30];
int dx[]={ 1, 2, 1, 2,-1,-2,-1,-2};
int dy[]={ 2, 1,-2,-1, 2, 1,-2,-1};
int sum;
int ans;
int val;
int main()
{
    scanf("%d%d",&n,&m);
    sum=n*m;
    while(scanf("%d%d",&x,&y)==2)
        map[x][y]=true,--sum;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            assign(id[i][j]);
         
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(!map[i][j])
            {
                if((i+j)&1)
                {
                    add(S,id[i][j],1);
                    for(int k=0;k<8;k++)
                        if(judge(i+dx[k],j+dy[k])&&!map[i+dx[k]][j+dy[k]])
                            add(id[i][j],id[i+dx[k]][j+dy[k]],1);
                }
                else
                    add(id[i][j],T,1);
            }
    printf("%d\n",sum-dinic());
}
