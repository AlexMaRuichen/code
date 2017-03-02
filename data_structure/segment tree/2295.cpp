#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1010;
long long x[maxn*2];
long long y[maxn*2];
int cnt[maxn*2];
long long ans;
struct seg
{
	int x,l,r;
	bool s;
}s[maxn*2];
bool cmp(seg a,seg b)
{
	return a.x<b.x;
}
int n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		static int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		s[i].x=a;
		s[i+n].x=c;
		s[i].l=s[i+n].l=d;
		s[i].r=s[i+n].r=b;
		x[i]=a;
		x[i+n]=c;
		y[i]=b;
		y[i+n]=d;
		s[i].s=true;
	}
	sort(x+1,x+(n<<1)+1);
	sort(y+1,y+(n<<1)+1);
	for(int i=1;i<=n;i++)
	{
		s[i].x=lower_bound(x+1,x+(n<<1)+1,s[i].x)-x;
		s[i].l=lower_bound(y+1,y+(n<<1)+1,s[i].l)-y;
		s[i].r=lower_bound(y+1,y+(n<<1)+1,s[i].r)-y;
		s[i+n].x=lower_bound(x+1,x+(n<<1)+1,s[i+n].x)-x;
		s[i+n].l=lower_bound(y+1,y+(n<<1)+1,s[i+n].l)-y;
		s[i+n].r=lower_bound(y+1,y+(n<<1)+1,s[i+n].r)-y;
	}
	sort(s+1,s+(n<<1)+1,cmp);
	int l=1,r=1;
	long long sum;
	while(r<=(n<<1))
	{
		sum=0;
		for(int i=1;i<=(n<<1);i++)
			if(cnt[i])
				sum+=y[i]-y[i-1];
		ans+=sum*(x[s[l].x]-x[s[l-1].x]);
		while(s[r].x==s[l].x)
		{
			if(s[r].s)
				for(int i=s[r].l+1;i<=s[r].r;i++)
					++cnt[i];
			else
				for(int i=s[r].l+1;i<=s[r].r;i++)
					--cnt[i];
			++r;
		}
		l=r;
	}
	printf("%lld\n",ans);
}
