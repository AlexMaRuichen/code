#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
#define p(x,y) (x-1)*m+y
using namespace std;
const int maxn=610;
const int maxm=800010;
const int inf=1e9;
int n,m;
char ch;
bool flag;
char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
void read(int &x)
{
	flag=x=0;
	ch=getc();
	while(ch<'0'||ch>'9')
	{	
		if(ch=='-')
			flag=true;
		ch=getc();
	}
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+ch-'0',ch=getc();
	x=flag?-x:x;
}

bool del[maxn];
queue <int> q;
int a[maxn];
int sum;
namespace Topo
{
	int to[maxm>>1];
	int next[maxm>>1];
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
	
	void kill(int x)
	{
		del[x]=true;
		for(int i=head[x];i;i=next[i])
			if(!del[to[i]])
				kill(to[i]);
	}
	void topo()
	{
		for(int i=1;i<=n*m;i++)
			if(!deg[i])
				q.push(i);
			else
				del[i]=true;
		while(!q.empty())
		{
			int x=q.front();
			q.pop();
			del[x]=false;
			for(int i=head[x];i;i=next[i])
			{
				--deg[to[i]];
				if(!deg[to[i]])
					q.push(to[i]);
			}
		}
		for(int i=1;i<=n*m;i++)
			if(del[i])
				kill(i);
	}
}

namespace Maximum_Flow
{
	int to[maxm];
	int next[maxm];
	int len[maxm];
	int head[maxn];
	int tot=1;
	int S=maxn-1,T=maxn-2;
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
	
	int dep[maxn];
	bool bfs()
	{
		memset(dep,-1,sizeof(dep));
		dep[S]=1;
		q.push(S);
		while(!q.empty())
		{
			int x=q.front();
			q.pop();
			for(int i=head[x];i;i=next[i])
				if(len[i]&&dep[to[i]]<0)
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
		if(used^f)
			dep[x]=-1;
		return used;
	}
	int MF()
	{
		int ans=0;
		while(bfs())
			ans+=dfs(S,inf);
		return ans;
	}
	void rebuild()
	{
		for(int x=1;x<=n*m;x++)
			if(!del[x])
			{
				if(a[x]>0)
					sum+=a[x],add(x,T,a[x]);
				else 
					add(S,x,-a[x]);
				for(int i=Topo::head[x];i;i=Topo::next[i])
					if(!del[Topo::to[i]])
						add(x,Topo::to[i],inf);
			}  
	}

}
int go()
{
	Topo::topo();
	Maximum_Flow::rebuild();
	return sum-Maximum_Flow::MF();
}
int main()
{
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			static int x;
			read(a[p(i,j)]);
			read(x);
			while(x--)
			{
				static int a,b;
				read(a);
				read(b);
				++a,++b;
				Topo::add(p(i,j),p(a,b)); 
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=m;j>1;j--)
			Topo::add(p(i,j),p(i,j-1));
	printf("%d\n",go());
}
