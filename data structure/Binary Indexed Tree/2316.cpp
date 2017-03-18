#include <stdio.h>
#include <algorithm>
#include <string.h>
#define lowbit(x) ((x)&(-(x)))
const int maxn=100010;
using namespace std;
typedef long long ll;
struct cow
{
	ll v,mod;
	int id;
}c[maxn];
bool cmp(cow a,cow b)
{
	return a.v<b.v;
}
int bit[maxn];
ll n,l,C;
ll sum;
ll ans;
ll v[maxn];
ll mod[maxn];
int lab[maxn];
int id[maxn];
ll m;
void modify(int x)
{
	for(int i=x;i<=n;i+=lowbit(i))
		++bit[i];
}
int query(int x)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans+=bit[i];
	return ans;
}
int main()
{
	scanf("%lld%lld%lld",&n,&l,&C);	
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&v[i]);
		m=max(m,v[i]);
	}
	for(int i=1;i<=n;i++)
		mod[i]=(l*C*v[i])%(C*m);
	for(int i=1;i<=n;i++)
		c[i].v=v[i],c[i].mod=mod[i];
	sort(mod+1,mod+n+1);
	for(int i=1;i<=n;i++)
		id[i]=lower_bound(mod+1,mod+n+1,c[i].mod)-mod;
	for(int i=1;i<=n;i++)
		c[i].id=id[i];
	sort(c+1,c+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		long long floor=l*c[i].v/m;
		long long add=floor*(i-1)-sum-i+1+(long long)query(c[i].id);
		ans+=add;
		sum+=floor;
		modify(c[i].id);
	}
	printf("%lld\n",ans);
}
