#include <stdio.h>

#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 2e5 + 10;

struct edge
{
	int to;
	edge *next;
	edge() {}
	edge(int to, edge *next) :to(to), next(next) {}
	void* operator new(size_t);
}*head[maxn], mem[maxn << 1];

void* edge :: operator new(size_t)
{
	static edge *p = mem;
	return p++;
}

void add(int x, int y)
{
	head[x] = new edge(y, head[x]);
	head[y] = new edge(x, head[y]);
}

int n, k;
int size[maxn];
LL f[maxn][6], ans, cnt[6];

void dfs(int x,int fa)
{
	size[x] = 1; 
	f[x][0] = 1;
	for (edge *p = head[x]; p; p = p->next)
		if(p->to ^ fa)
		{
			dfs(p->to, x);
			size[x] += size[p->to];
			for (int i = 0; i < k; i++)
				for (int j = 0; j < k; j++)
					cnt[(i + j + 1) % k] += f[x][i] * 1ll * f[p->to][j];
			for (int i = 0; i < k; i++) 
				f[x][(i + 1) % k] += f[p->to][i];
		}
	ans += (size[x] * 1ll * (n - size[x]));
}
int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1, x, y; i < n; i++)
	{
		scanf("%d %d",&x, &y);
		add(x, y);
	}
	dfs(1, 1);
	for (int i = 1; i < k; i++)
		ans += (cnt[i] * 1ll * (k - i));
	printf("%lld\n", ans / k);
}