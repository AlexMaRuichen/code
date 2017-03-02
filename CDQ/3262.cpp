#include <stdio.h>
#include <algorithm>
#define lowbit(x) (x)&(-x)
using namespace std;
const int maxn=100010;
struct blossom
{
	int s,c,m,cnt,ans;
	bool operator != (const blossom &a) const
	{
		return a.s^s||a.c^c||a.m^m;
	}
}a[maxn],p[maxn];
bool cmps(const blossom &a,const blossom &b)
{
	return a.s^b.s?a.s<b.s:a.c^b.c?a.c<b.c:a.m<b.m;
}
bool cmpc(const blossom &a,const blossom &b)
{
	return a.c^b.c?a.c<b.c:a.m<b.m;
}
int bit[200010];
int n,k;
void update(int x,int y)
{
	for(int i=x;i<=k;i+=lowbit(i))
		bit[i]+=y;
}
int query(int x)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans+=bit[i];
	return ans;
}
void CDQ(int l,int r)
{
	if(l==r)
		return ;
	int mid=l+r>>1;
	CDQ(l,mid);
	CDQ(mid+1,r);
	sort(p+l,p+mid+1,cmpc);
	sort(p+mid+1,p+r+1,cmpc);
	int i=l,j=mid+1;
	while(j<=r)
	{
		while(i<=mid&&p[i].c<=p[j].c)
			update(p[i].m,p[i].cnt),++i;
		p[j].ans+=query(p[j].m);
		++j;
	}
	for(j=l;j<i;j++)
		update(p[j].m,-p[j].cnt);
}
int ans[maxn];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&a[i].s,&a[i].c,&a[i].m),a[i].cnt=1;
	sort(a+1,a+n+1,cmps);
	int tot=0;
	for(int i=1;i<=n;i++)
		if(a[i]!=a[i-1])
			p[++tot]=a[i];
		else
			++p[tot].cnt;
	CDQ(1,tot);
	for(int i=1;i<=tot;i++)
		ans[p[i].ans+p[i].cnt-1]+=p[i].cnt;
	for(int i=0;i<n;i++)
		printf("%d\n",ans[i]);
}
