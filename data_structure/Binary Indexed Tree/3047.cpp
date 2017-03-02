#include <stdio.h>
#include <bitset>
#include <string.h>
#include <algorithm>
#define lowbit(x) (x&-(x))
using namespace std;
const int maxn=1100;
class LoadBalancing
{
	int n;
	typedef pair<int,int> point;
	point p[maxn];

	int x[maxn];
	int y[maxn];

	bitset <maxn> v;

	int ans;

	struct BIT
	{
		int ans;
		int a[maxn];
		int n;
		BIT(int x)
		{
			n=x;
		}
		void update(int x)
		{
			for(int i=x;i<=n;i+=lowbit(i))
				++a[i];
		}
		int query(int x)
		{
			ans=0;
			for(int i=x;i;i-=lowbit(i))
				ans+=a[i];
			return ans;
		}
		void clear()
		{
			memset(a,0,sizeof(a));
		}
	};
	void Discrete()
	{
		sort(x+1,x+n+1);
		sort(y+1,y+n+1);
		x[0]=unique(x+1,x+n+1)-x;
		y[0]=unique(y+1,y+n+1)-y;
		--x[0],--y[0];
		for(int i=1;i<=n;i++)
			p[i].first=lower_bound(x+1,x+x[0]+1,p[i].first)-x,
			p[i].second=lower_bound(y+1,y+y[0]+1,p[i].second)-y;
		for(int i=1;i<=x[0];i++)
			x[i]=i;
		for(int i=1;i<=y[0];i++)
			y[i]=i;
	}
public:
	int solve()
	{
		ans=~0u>>1;

		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&x[i],&y[i]),p[i]=point(x[i],y[i]);

		Discrete();

		sort(p+1,p+n+1);

		BIT L(y[0]),R(y[0]);
		for(int i=1;i<=n;i++)
			if(!v[p[i].first])
			{
				L.clear();
				R.clear();
				v[p[i].first]=true;
				for(int j=1;j<=n;j++)
					if(p[j].first<=p[i].first)
						L.update(p[j].second);
					else
						R.update(p[j].second);
				for(int j=1;j<=y[0];j++)
					ans=min(ans,max(max(L.query(y[j]),L.query(y[y[0]])-L.query(y[j])),
									max(R.query(y[j]),R.query(y[y[0]])-R.query(y[j]))));
			}
		return ans;
	}
}cls;
int main()
{
	printf("%d\n",cls.solve());
}
