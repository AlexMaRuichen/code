#include <stdio.h>
#include <algorithm>
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int maxn=1e5+10;
int n;
long long bit[maxn];
long long ans;
int a[maxn];
void modify(int x)
{
	while(x<=1e5)
	{
		bit[x]++;
		x+=lowbit(x);
	}
}
long long query(int x)
{
	long long tmp=0;
	while(x)
	{
		tmp+=bit[x];
		x-=lowbit(x);
	}
	return tmp;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		modify(a[i]);
		ans+=i-query(a[i]);	
	}
	printf("%lld\n",ans);
}
