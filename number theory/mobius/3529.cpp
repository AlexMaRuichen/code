#include <stdio.h>

#include <algorithm>

#define lowbit(x) ((x) & (-(x)))

using namespace std;

const int maxn = 100010;
const int N = 1e5;

int cnt;
int mu[maxn];
bool v[maxn];
int prime[maxn];
pair <int, int> f[maxn];

struct query
{
	int n, m, a, id;
}q[maxn];

bool operator < (const query &a, const query &b)
{
	return a.a < b.a;
}

int ans[maxn];
int bit[maxn];

void modify(int x, int y)
{
	for (int i = x; i <= N; i += lowbit(i))
		bit[i] += y;
}

int query(int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
		ans += bit[i];
	return ans;
}

void sieve()
{
	mu[1] = 1;
	for (int i = 2; i <= N; i++)
	{
		if (!v[i])
			prime[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && i * prime[j] <= N; j++)
		{
			v[i * prime[j]] = true;
			if (i % prime[j] == 0)
				break;
			mu[i * prime[j]] = -mu[i];
		}
	}
	for (int i = 1; i <= N; i++)
		for (int j = i; j <= N; j += i)
			f[j].first += i;
	for (int i = 1; i <= N; i++)
		f[i].second = i;
/*	for (int i = 1; i <= 100; i++)
		printf("%d\n", f[i].first);*/
}

int calc(int x)
{
	int n = q[x].n, m = q[x].m, ans = 0;
	for (int i = 1, last; i <= n && i <= m; i = last + 1)
	{
		last = min(n / (n / i), m / (m / i));
		ans += (n / i) * (m / i) * (query(last) - query(i - 1));
	}
	return ans;
}

int main()
{
	int T;
	sieve();
	scanf("%d", &T);
	for (int i = 1; i <= T; i++)
	{
		scanf("%d%d%d", &q[i].n, &q[i].m, &q[i].a);
		q[i].id = i;
	}
	sort(q + 1, q + T + 1);
	sort(f + 1, f + N + 1);
	for(int i = 1, j = 1; i <= T; i++)
	{
		while (j <= N && f[j].first <= q[i].a)
		{
			for (int k = f[j].second; k <= N; k += f[j].second)
				modify(k, f[j].first * mu[k / f[j].second]);
			++j;
		}
		ans[q[i].id] = calc(i);
	}
	for (int i = 1; i <= T; i++)
		printf("%d\n", ans[i] & (~0u >> 1));
}