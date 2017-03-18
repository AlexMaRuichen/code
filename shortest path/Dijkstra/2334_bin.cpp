#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <set>
using namespace std;
typedef pair<int,int> point;
const int maxn=510;
int s[maxn];
int to[maxn*2];
int next[maxn*2];
int lat[maxn*2];
int cap[maxn*2];
int tot;
int head[maxn];
point p[maxn*2];
int size;
int f[maxn];
int n,m,x;
void add(int x,int y,int z,int a)
{
    to[++tot]=y;
    lat[tot]=z;
    cap[tot]=a;
    next[tot]=head[x];
    head[x]=tot;
    to[++tot]=x;
    lat[tot]=z;
    cap[tot]=a;
    next[tot]=head[y];
    head[y]=tot;
}
bool v[maxn];
int dijkstra(int S,int T,int c)
{
    memset(v,0,sizeof(v));
    memset(f,0x3f,sizeof(f));
    memset(p,0,sizeof(p));
    size=0;
    f[S]=0;
    p[++size]=point(f[S],S);
    make_heap(p+1,p+size+1,greater<point>());
    while(size)
    {
        int x=p[1].second;
        int dis=p[1].first;
        pop_heap(p+1,p+size+1,greater<point>());
        --size;
        if(v[x])
            continue;
        if(x==T)
            return f[x];
        v[x]=true;
        for(int i=head[x];i;i=next[i])
            if(cap[i]>=c&&f[to[i]]>dis+lat[i])
            {
                f[to[i]]=f[x]+lat[i];
                p[++size]=point(f[to[i]],to[i]);
                push_heap(p+1,p+size+1,greater<point>());
            }
    }
    return ~0u>>2;
}
int ans=~0u>>2;
int cnt;
int main()
{
    scanf("%d%d%d",&n,&m,&x);
    for(int i=1;i<=m;i++)
    {
        static int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        add(a,b,c,d);
        s[++cnt]=d;
    }   
    sort(s+1,s+cnt+1);
    int l=0,r=cnt;
    while(r-l>1)
    {
    	int mid=l+r>>1;
		int t=dijkstra(1,n,s[mid]);
		if(t!=~0u>>2)
			l=mid;
		else
			r=mid-1;
    }
    printf("%d\n",dijkstra(1,n,l)+x/s[l]);
}
