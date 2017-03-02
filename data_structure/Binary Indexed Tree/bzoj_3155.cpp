#include <stdio.h>
#include <algorithm>
#include <string.h>
#define lowbit(x) ((x)&(-x))
using namespace std;
/*****************************************************
SSt=( ∑t,i=1 ai∗i )=∑t,i=1 ai∗(n−i+1)− (n−t)∑t,i=1 ai
*****************************************************/
typedef long long ll;
const int maxn=100000;
ll bit[maxn+10];
ll Bit[maxn+10];
int n,m;
ll a[maxn+10];
ll sum;
char q[]="Query";
char M[]="Modify";
char opt[10];
int x,y;
void modify(bool _,int x,ll y)
{
	if(_)
		for(int i=x;i<=n;i+=lowbit(i))
			bit[i]+=y;
	else
		for(int i=x;i<=n;i+=lowbit(i))
			Bit[i]+=y;
}
ll query(bool _,ll x)
{
	ll ans=0;
	if(_)
		for(int i=x;i;i-=lowbit(i))
			ans+=bit[i];
	else
		for(int i=x;i;i-=lowbit(i))
			ans+=Bit[i];
	return ans;
}
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		modify(1,i,a[i]);
		modify(0,i,(n-i+1)*a[i]);
	}
	while(q--)
	{
		scanf("%s",opt);
		if(!strcmp(opt,q))
		{
			scanf("%d",&x);
			printf("%lld\n",query(0,x)-(n-x)*query(1,x));
		}
		else if(!strcmp(opt,M))
		{
			scanf("%d%d",&x,&y);
			modify(1,x,y-a[x]);
			modify(0,x,(n-x+1)*(y-a[x]));
			a[x]=y;
		}
	}
}
