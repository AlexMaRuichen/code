#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <stack>

using namespace std;

typedef long long LL;
const int maxn = 1e3 + 10;
const int mod = 1e8;

int n;

struct hpc
{
	LL x[500];
	int len;
	hpc(int a = 0)
	{
		memset(x, 0, sizeof(x));
		x[1] = a;
		len = 1;
	}
}ans(1);

void print(const hpc &x)
{
	printf("%lld", x.x[x.len]);
	for (int i = x.len - 1; i; i--)
		printf("%08lld", x.x[i]);
	puts("");
}

void operator *= (hpc &x, const hpc &y)
{
	hpc ans;
	ans.len = x.len + y.len;
	for (int i = 1; i <= x.len; i++)
	{
		LL num = 0, t;
		for (int j = 1; j <= y.len; j++)
		{
			t = x.x[i] * y.x[j] + ans.x[i + j - 1] + num;
			ans.x[i + j - 1] = t % mod;
			num = t / mod;
		}
		if (num)
			ans.x[i + y.len] = num;
	}
	x = ans;
	while(!x.x[x.len] && x.len > 1)
		--x.len;
}

int r, m;
stack <int> s;
int cnt[maxn];

void split(int x, int flag)
{
	for (int i = 2; i * i <= x; i++)
		while(x % i == 0)
			cnt[i] += flag, x /= i;
	if (x ^ 1)
		cnt[x] += flag;
}

void mul(int X, int y)
{
	hpc x(X);
	while(y)
	{
		if (y & 1)
			ans *= x;
		x *= x;
		y >>= 1;
	}
}

int main()
{
	scanf("%d", &n);
	r = n - 2;
	for (int i = 1, x; i <= n; i++)
	{
		scanf("%d", &x);
		if (x > 1)
			s.push(x - 1), r -= x - 1;
		else if(x == -1)
			++m;
	}
	for (int i = 2; i <= n - 2; i++)
		split(i, 1);
	while (!s.empty())
	{
		for (int i = s.top(); i > 1; i--)
			split(i, -1);
		s.pop();
	}
	for (int i = 2; i <= r; i++)
		split(i, -1);
	split(m, r);
	for (int i = 1; i <= n; i++)
		if (cnt[i])
			mul(i, cnt[i]);
	print(ans);
}