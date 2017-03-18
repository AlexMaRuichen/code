#include <stdio.h>
#include <string.h>
#include <deque>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int,int> point;
const int maxn=2010;
deque <point> dq;
ll f[maxn];
int n,l;
int h[maxn];
int w[maxn];
ll sum[maxn];
int main()
{
	memset(f,0x3f,sizeof(f));
	scanf("%d%d",&n,&l);
	register int i,j;
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&h[i],&w[i]);
		sum[i]=sum[i-1]+w[i];
	}
	f[0]=0;
	int hmax;
	for(i=1;i<=n;i++)
	{
		hmax=0;
		for(j=i;j&&sum[i]-sum[j-1]<=l;--j)
		{
			hmax=max(hmax,h[j]);
			f[i]=min(f[i],f[j-1]+hmax);
		}
	}
	printf("%lld\n",f[n]);
}
