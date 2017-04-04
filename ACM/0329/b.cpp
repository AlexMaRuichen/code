#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 5e4 + 10;

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

typedef long long LL;

struct edge
{
	int to;
	edge *next;
	edge() {}
	edge(int to, edge *next) :to(to), next(next) {}
	void* operator new(size_t);
}*head[maxn], mem[maxn << 1], *p;

void* edge :: operator new(size_t)
{
	return p++;
}

void add(int x, int y)
{
	head[x] = new edge(y, head[x]);
	head[y] = new edge(x, head[y]);
}

int size[maxn];
int f[maxn];
int n, I, R;

void dfs(int x, int fa)
{
	size[x] = 1;
	f[x] = 0;
	for (edge *p = head[x]; p; p = p->next)
		if (p->to ^ fa)
		{
			dfs(p->to, x);
			f[x] += size[p->to] + f[p->to];
			size[x] += size[p->to];
		}
}

int g[maxn];

void dp(int x, int fa)
{
	for (edge *p = head[x]; p; p = p->next)
		if (p->to ^ fa)
		{
			g[p->to] = g[x] - size[p->to] + (n - size[p->to]);
			dp(p->to, x);
		}
}

vector <int> v;

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		p = mem;
		memset(head, 0, sizeof(head));
		scanf("%d%d%d", &n, &I, &R);
		for (int i = 1, x, y; i < n; i++)
			scanf("%d%d", &x, &y),
			add(x, y);
		dfs(1, 1);
		g[1] = f[1];
		dp(1, 1);
		LL ans = ~0ull >> 1;
		for (int i = 1; i <= n; i++)
			if (ans > I * 1ll * I * R * g[i])
			{
				ans = I * 1ll * I * R * g[i];
				v.clear();
				v.push_back(i);
			}
			else if (ans == I * 1ll * I * R * g[i])
				v.push_back(i);
		printf("%lld\n", ans);
		for (int i = 0; i < v.size(); i++)
			printf("%d ", v[i]);
		puts("\n");
	}
}