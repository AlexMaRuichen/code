#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
const int N = 1e5;
int mu[maxn];
bool v[maxn];
int prime[maxn];
map <int, LL> maps;

void sieve()
{
	mu[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!v[i])
			prime[++prime[0]] = i, mu[i] = -1;
		for(int j = 1; j <= prime[0] && i * prime[j] <= N; j++)
		{
			v[i * prime[j]] = true;
			if(i%prime[j]==0)
				break;
			mu[i * prime[j]] = -mu[i];
		}
	}
	for(int i = 1; i <= N; i++)
		mu[i] += mu[i-1];
}

LL get(LL x)
{
	static map <int, LL> :: iterator it;
	if(x <= N)
		return mu[x];
	if((it = maps.find(x)) != maps.end())
		return it->second;
	LL ans = 1;
	for(LL i = 2, last; i <= x; i = last + 1)
	{
		last = x / (x / i);
		ans -= (last - i + 1) * get(x / i);
	}
	return maps[x] = ans;
}

LL calc(int x)
{
	LL ans = 0;
	for (int i = 1, last; i <= x; i = last + 1)
	{
		last = min(x / (x / i), y / (y / i));
		(ans += (get(last) - get(i - 1)) * (x * 1ll * x + 3 * 1ll * x + 2)) %= mod;
	}
	return ans;
}

int main()
{
//	freopen("miu.in","r",stdin);
//	freopen("miu.out","w",stdout);
	sieve();
	int n;
	scanf("%d", &n);
	printf("%lld\n", calc(n));
}
