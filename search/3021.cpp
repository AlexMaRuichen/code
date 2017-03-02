#include <stdio.h>
#include <bitset>
using namespace std;
const int maxn=110;
const int maxm=20010;

class SwitchingOnTheLights
{

	int n,m;

	int tox[maxm];
	int toy[maxm];
	int next[maxm];
	int head[maxn][maxn];
	int tot;
	void add(int x,int y,int a,int b)
	{
		tox[++tot]=a;
		toy[tot]=b;
		next[tot]=head[x][y];
		head[x][y]=tot;
	}

	int dx[4];
	int dy[4];

	int ans;

	bitset <maxn> v[maxn];
	bitset <maxn> p[maxn];

	void process(int x,int y)
	{
		p[x][y]=true;
		for(int i=head[x][y];i;i=next[i])
		{
			v[tox[i]][toy[i]]=true;
			if(!p[tox[i]][toy[i]])
				for(int j=0;j<4;j++)
					if(p[tox[i]+dx[j]][toy[i]+dy[j]])
					{
						process(tox[i],toy[i]);
						break;
					}
		}
		for(int i=0;i<4;i++)
			if(v[x+dx[i]][y+dy[i]]&&!p[x+dx[i]][y+dy[i]])
				process(x+dx[i],y+dy[i]);
	}

public:

	SwitchingOnTheLights()
	{
		tot=0;
		ans=0;
		dx[0]=0,dy[0]=1;
		dx[1]=1,dy[1]=0;
		dx[2]=0,dy[2]=-1;
		dx[3]=-1,dy[3]=0;
	}

	int solve()
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
		{
			static int x,y,a,b;
			scanf("%d%d%d%d",&x,&y,&a,&b);
			add(x,y,a,b);
		}

		for(int i=1;i<=n;i++)
			v[i].reset(),p[i].reset();
		v[1][1]=true;

		process(1,1);

		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(v[i][j])
					++ans;
		return ans;
	}
}cls;
int main()
{
	printf("%d\n",cls.solve());
}
