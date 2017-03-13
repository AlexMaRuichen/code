#include <stdio.h>
#include <math.h>

#include <algorithm>

using namespace std;

const int maxn = 5e4 + 10;

struct query
{
	int l, r, pos;
}q[maxn];

int n, m, block;

bool operator < (const query &a, const query &b)
{
	return a.l / block == b.l / block ? a.r < b.r : a.l / block < b.l / block;
}

int a[maxn];
int cnt[maxn];

typedef unsigned int uint;
typedef pair <uint, uint> point;

uint GCD(uint x, uint y)
{
	return y ? GCD(y, x % y) : x;
}

point ans[maxn];

int main()
{
	scanf("%d%d", &n, &m);
	block = sqrt(n) + 1;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &q[i].l, &q[i].r), q[i].pos = i;
	sort(q + 1, q + m + 1);
	int l = 1, r = 0;
	uint now = 0;
	for (int i = 1; i <= m; i++)
	{
		while (r < q[i].r)  
            now += cnt[a[++r]]++;  
        while (r > q[i].r)  
            now -= --cnt[a[r--]];  
		while (l < q[i].l)
			now -= --cnt[a[l++]];
		while (l > q[i].l)
			now += cnt[a[--l]]++;
		uint tmp = uint(r - l + 1) * (r - l) >> 1;
		uint gcd = GCD(tmp, now);
		ans[q[i].pos] = point(now / gcd, tmp / gcd);
	}
	for (int i = 1; i <= m; i++)
		printf("%u/%u\n", ans[i].first, ans[i].second);
}