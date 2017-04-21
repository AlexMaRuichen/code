#include <stdio.h>

#include <algorithm>
#define lowbit(x) x & -x

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

using namespace std;

const int maxn = 20010;
const int N = 2e4;

int n, ans;
int bit[maxn];

void modify(int x, int y)
{
	for (int i = x; i <= N; i += lowbit(i))
		relax(bit[i], y);
}

int query(int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
		relax(ans, bit[i]);
	return ans;
}

void del(int x)
{
	for (int i = x; i <= N; i += lowbit(i))
		bit[i] = 0;
}

struct point
{
	int x, y, id, ans;
}p[maxn];

bool operator < (const point &a, const point &b)
{
	return a.x ^ b.x ? a.x < b.x : a.y < b.y;
}

bool cmp(const point &a, const point &b)
{
	return a.id < b.id;
}

void CDQ(int l, int r)
{
	if (l == r)
		return ;
	int mid = l + r >> 1;
	CDQ(l, mid);
	sort(p + l, p + mid + 1);
	sort(p + mid + 1, p + r + 1);
	int i = l, j = mid + 1;
	while (j <= r)
	{
		while (i <= mid && p[i].x < p[j].x)
			modify(p[i].y, p[i].ans), ++i;
		relax(p[j].ans, query(p[j].y) + 1);
		++j;
	}
	for (int i = l; i <= mid; i++)
		del(p[i].y);
	sort(p + l, p + r + 1, cmp);
	CDQ(mid + 1, r);
}

int main()
{
	scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d%d", &p[i].x, &p[i].y), p[i].ans = 1, p[i].id = i;
    CDQ(1, n);
	for (int i = 1; i <= n; i++)
		relax(ans, p[i].ans);
    printf("%d\n", ans);
}