#include <stdio.h>
#include <math.h>

#include <algorithm>

#define lowbit(x) ((x) & (-x))

using namespace std;

typedef long long LL;

const int maxn = 50010;

int n, m;
int block;
int a[maxn];
int b[maxn];
int bit[maxn];

void modify(int x, int y)
{
	for (int i = x; i <= n; i += lowbit(i))
		bit[i] += y;
}

int query(int x)
{
	int now = 0;
	for (int i = x; i; i -= lowbit(i))
		now += bit[i];
	return now;
}

struct data
{
	int l, r, pos;
}q[maxn];

bool operator < (const data &a, const data &b)
{
	return a.l / block == b.l / block ? a.r < b.r : a.l / block < b.l / block;
}

LL ans[maxn];

int main()
{
	scanf("%d", &n);
	block = sqrt(n) + 1;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &q[i].l, &q[i].r), q[i].pos = i;
	sort(q + 1, q + m + 1);
	int l = 1, r = 0;
	LL now = 0;
	for (int i = 1; i <= m; i++)
	{
		while (l < q[i].l)
			now -= query(a[l] - 1), modify(a[l++], -1);
		while (l > q[i].l)
			now += query(a[--l] - 1), modify(a[l], 1);
		while (r < q[i].r)
			now += query(n) - query(a[++r]), modify(a[r], 1);
		while (r > q[i].r)
			now -= query(n) - query(a[r]), modify(a[r--], -1); 
		ans[q[i].pos] = now;
	}
	for (int i = 1; i <= m; i++)
		printf("%lld\n", ans[i]);
}