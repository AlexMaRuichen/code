#include <stdio.h>
#include <algorithm>
#define lowbit(x) (x)&(-x)
using namespace std;
const int maxn=100010;
struct data
{
	int pos,val,ins,ans;
}d[maxn];
bool cmpi(const data &a,const data &b)
{
	return a.ins^b.ins?a.ins>b.ins:a.pos<b.pos;
}
bool cmpinv(const data &a,const data &b)
{
	return a.ins<b.ins;
}
bool cmpp(const data &a,const data &b)
{
	return a.pos<b.pos;
}
bool cmpv(const data &a,const data &b)
{
	return a.val<b.val;
}
int bit[maxn];
int n,m;
inline void insert(int x)
{
	for(int i=x;i<=n;i+=lowbit(i))
		++bit[i];
}
inline void del(int x)
{
	for(int i=x;i<=n;i+=lowbit(i))
		bit[i]=0;
}
inline int query(int x)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans+=bit[i];
	return ans;
}
void CDQ(int l,int r)
{
	if(l==r)
		return;
	int mid=l+r>>1;
	CDQ(l,mid);
	CDQ(mid+1,r);
	sort(d+l,d+mid+1,cmpp);
	sort(d+mid+1,d+r+1,cmpp);
	int i=l,j=mid+1;
	while(j<=r)
	{
		while(i<=mid&&d[i].pos<d[j].pos)
			insert(d[i].val),++i;
		d[j].ans+=query(n)-query(d[j].val);
		++j;
	}
	for(j=l;j<=mid;j++)
		del(d[j].val);
	i=mid,j=r;
	while(j>=mid+1)
	{
		while(i>=l&&d[i].pos>d[j].pos)
			insert(d[i].val),--i;
		d[j].ans+=query(d[j].val);
		--j;
	}
	for(j=l;j<=mid;j++)
		del(d[j].val);
}
int ans;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&d[i].val),d[i].pos=i,d[i].ins=m+1;
	sort(d+1,d+n+1,cmpv);
	for(int i=1;i<=m;i++)
	{
		static int x;
		scanf("%d",&x);
		d[x].ins=i;
	}
	sort(d+1,d+n+1,cmpi);
	CDQ(1,n);
	long long sum=0;
	sort(d+1,d+n+1,cmpinv);
	for(int i=1;i<=n;i++)
		sum+=d[i].ans;
	for(int i=1;i<=m;i++)
		printf("%lld\n",sum),sum-=d[i].ans;
}
