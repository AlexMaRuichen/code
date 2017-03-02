#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 730;
const int inf = 1e7;

struct edge
{
	int to;
	edge *next;
	edge() {}
	edge(int to, edge *next) :to(to), next(next) {}
	void* operator new(size_t);
}*head[maxn], mem[maxn];

void* edge :: operator new(size_t)
{
	static edge *p = mem;
	return p++;
}

int deg[maxn];

void add(int x, int y)
{
	head[x] = new edge(y, head[x]);
	++deg[y];
}

int f[maxn][3];
int a[maxn];

void dp(int x)
{
	int inc = inf;
	f[x][0] = a[x];
	for (edge *p = head[x]; p; p = p->next)
	{
		dp(p->to);
		f[x][0] += min(min(f[p->to][0], f[p->to][1]), f[p->to][2]);
		f[x][2] += f[p->to][1];
		f[x][1] += min(f[p->to][0], f[p->to][1]);
		inc = min(inc, f[p->to][0] - f[p->to][1]);
	}
	f[x][1] += max(inc, 0);
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1, x, y, z; i <= n; i++)
	{
		scanf("%d%d%d", &x, &y, &z);
		a[x] = y;
		while (z--)
		{
			scanf("%d", &y);
			add(x, y);
		}
	}
	int root;
	for (int i = 1; i <= n; i++)
		if (!deg[i])
		{
			root = i;
			break;
		}
	dp(root);
	printf("%d\n", min(f[root][0], f[root][1]));
}