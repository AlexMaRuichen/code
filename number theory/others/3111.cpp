#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;
ll a,b;
bool pre[1000010];
int prime[80000];
int cnt;
int ans;
int main()
{
	scanf("%lld%lld",&a,&b);
	ll y=sqrt(b);
	for(ll i=2;i<=y+1;i++)
		for(ll j=(a/i/i*i*i>=a?a/i/i:(a/i/i)+1);j*i*i<=b;j++)
				pre[i*i*j-a]=true;
	for(ll i=a;i<=b;i++)
		if(!pre[i-a])
			ans++;
	printf("%d\n",ans);
}
