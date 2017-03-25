#include <stdio.h>

#include <algorithm>
#include <vector>

#define lowbit(x) x & -x
using namespace std;

const int maxn = 1e5 + 10;
const int LOG = 17;

int bit[maxn];

int n;

void modify(int x, int y)
{
	for (int i = x; i <= n; i += lowbit(i))
		bit[i] += y;
}

int query(int x)
{
	int p = 0;
	for (int i = LOG; ~i; i--)
		if (p + (1 << i) <= n && x > bit[p + (1 << i)])
			x -= bit[p += (1 << i)];
	return p + 1;
}

int a[maxn];
int ans[maxn];
int fir[maxn];
int suc[maxn];

vector <int> pos[maxn];

int main()
{
	scanf("%d", &n);
	++n;
	for (int i = 1; i < n; i++)
		scanf("%d", &a[i]);
	for (int i = n; i; i--)
		fir[i] = n;
	for (int i = n - 1; i; i--)
		suc[i] = fir[a[i]],
		fir[a[i]] = i;
	for (int i = 1; i < n; i++)
		pos[1].push_back(i),
		modify(fir[i], 1);
	for (int i = 1; i < n; i++)
	{
		for (int j = pos[i].size() - 1, x; ~j; j--)
		{
			++ans[x = pos[i][j]];
			pos[query(x + 1)].push_back(x);
		}
		modify(i, -1);
		modify(suc[i], 1);
	}
	for (int i = 1; i < n; i++)
		printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
}