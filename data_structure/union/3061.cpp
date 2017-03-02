#include <stdio.h>
#include <bitset>
#include <algorithm>
using namespace std;
const int maxn=3010;
const int maxm=6010;
class ClosingTheFarm
{
	int n,m;
	int fa[maxn];
	int size[maxn];
	int cnt;
	void init()
	{
		for(int i=1;i<=n;i++)
			fa[i]=i,size[i]=1;
	}
	int getfa(int x)
	{
		if(fa[x]!=x)
			fa[x]=getfa(fa[x]);
		return fa[x];
	}

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

	int q[maxn];
	bitset <maxn> v;
public:
	void solve()
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
		{
			static int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);
		}
		for(int i=1;i<=n;i++)
			scanf("%d",&q[i]);
		reverse(q+1,q+n+1);

		init();
		for(int t=1;t<=n;t++)
		{
			++cnt;
			for(int i=head[q[t]];i;i=next[i])
				if(v[to[i]])
				{
		            int x=getfa(q[t]),y=getfa(to[i]);
		            if(x==y)
						continue;
		            --cnt;
					if(size[x]>size[y])
						swap(x,y);
					size[y]+=size[x];
		            fa[x]=y;
	        	}
	        v[q[t]]=true;
	        q[t]=cnt==1;
		}
		reverse(q+1,q+n+1);
		for(int i=1;i<=n;i++)
			printf("%s\n",q[i]?"YES":"NO");
	}
}cls;
int main()
{
	cls.solve();
}
