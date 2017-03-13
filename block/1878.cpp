#include <stdio.h>
#include <math.h>

#include <algorithm>

using namespace std;

const int maxn = 50010;
const int maxq = 200010;

int n, block, m;
int a[maxn];
int b[maxn];
int cnt[maxn];
int ans[maxq];

struct data
{
	int l, r, pos;
}q[maxq];

bool operator < (const data &a, const data &b)
{
	return a.l / block == b.l / block ? a.r < b.r : a.l / block < b.l / block;
}

int now;

void insert(int x)
{
	!cnt[x] ? ++now : 1;
	++cnt[x];
}

void del(int x)
{
	--cnt[x];
	!cnt[x] ? --now : 1;
}

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
	for (int i = 1; i <= m; i++)
	{
		while (l < q[i].l)
			del(a[l++]);
		while (l > q[i].l)
			insert(a[--l]);
		while (r < q[i].r)
			insert(a[++r]);
		while (r > q[i].r)
			del(a[r--]);
		ans[q[i].pos] = now;
	}
	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}