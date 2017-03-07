#include <stdio.h>

#include <algorithm>
#include <bitset>

#define push(x) q[++r] = x
#define front(x) q[l++]
#define size() r - l + 1
#define relax(x) x >= mod ? x -= mod : 1

using namespace std;

typedef long long LL;

const int maxn = 3010;
const int mod = 998244353;

int n;
int deg[maxn];
bitset <maxn> map[maxn];
bitset <maxn> f[maxn];
int q[maxn];
int pow[maxn];
int l = 1, r;

int main()
{
	scanf("%d", &n);
	pow[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		static char s[maxn];
		scanf("%s", s + 1);
		for (int j = 1; j <= n; j++)
			map[i][j] = s[j] == '0';
		map[i][i] = false;
		pow[i] = pow[i - 1] << 1;
		relax(pow[i]);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (map[i][j])
				++deg[i];
	for (int i = 1; i <= n; i++)
		if (!deg[i])
			push(i);
	while (size())
	{
		int x = front();
		for (int i = 1; i <= n; i++)
			if (map[i][x] && !(--deg[i]))
				push(i);
	}
	for (int i = r; i; i--)
	{
		int x = q[i];
		f[x][x] = true;
		for (int j = i + 1; j <= r; j++)
			if (map[q[j]][x])
				f[x] |= f[q[j]];
	}
	int ans1 = 0, ans2 = 0;
	for (int i = 1, cnt; i <= r; i++)
	{
		cnt = f[q[i]].count();
		ans1 = (ans1 + (pow[cnt] - 1) * 1ll * pow[r - cnt]) % mod;
		ans2 += pow[r - cnt];
		relax(ans2);
	}
	printf("%d %d\n", ans1, ans2);
}