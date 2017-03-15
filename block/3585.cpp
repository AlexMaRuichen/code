#include <stdio.h>
#include <math.h>

#include <algorithm>

using namespace std;

const int maxn = 200010;

int n, m;
int block;
int a[maxn];
int cnt[maxn];
int size[maxn];
int l[maxn];
int r[maxn];
int ans[maxn];
int belong[maxn];

struct query
{
	int l, r, pos;
}q[maxn];

bool operator < (const query &a, const query &b)
{
	return belong[a.l] == belong[b.l] ? a.r < b.r : a.l < b.l;
}


void ins(int x)
{
	x <= n && !cnt[x]++ ? ++size[belong[x]] : 1;
}

void del(int x)
{
	x <= n && !--cnt[x] ? --size[belong[x]] : 1;
}

int get()
{
	if (!cnt[0])
		return 0;
	static int i, tmp;
	for (i = 1; l[i]; i++)
		if (size[i] ^ r[i] - l[i] + 1)
			break;
	tmp = i;
	for (i = l[tmp]; i <= r[tmp]; i++)
		if (!cnt[i])
			return i;
	return n;
}

int main()
{
	scanf("%d%d", &n, &m);
	block = sqrt(n) + 1;
	for (int i = 1; i <= n; i++)
		belong[i] = (i - 1) / block + 1;
	for (int i = 1; (i - 1) * block <= n; i++)
		l[i] = (i - 1) * block + 1, r[i] = min(i * block, n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &q[i].l, &q[i].r), q[i].pos = i;
	sort(q + 1, q + m + 1);
	int l = 1, r = 0;
	for (int i = 1; i <= m; i++)
	{
		while (l < q[i].l)
			del(a[l++]);
		while (l > q[i].l)
			ins(a[--l]);
		while (r < q[i].r)
			ins(a[++r]);
		while (r > q[i].r)
			del(a[r--]);
		ans[q[i].pos] = get();
	}
	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}