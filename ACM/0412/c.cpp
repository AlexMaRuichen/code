#include <stdio.h>

#include <algorithm>
#include <vector>

#define lowbit(x) ((x) & (-(x)))

using namespace std;

const int maxn = 500010;

int n, m;
int bit[maxn];

void insert(int x, int y)
{
	for (int i = x; i <= n; i += lowbit(i))
		bit[i] ^= 1 << y;
}

int query(int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
		ans ^= bit[i];
	return ans;
}

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

void add(int x, int y)
{
	head[x] = new edge(y, head[x]);
}

char s[maxn];
int dfn[maxn];
int size[maxn];
vector <int> v[maxn];

void dfs(int x, int dep)
{
	static int cnt;
	dfn[x] = ++cnt;
	size[x] = 1;
	v[dep].push_back(x);
	for (edge *p = head[x]; p; p = p->next)
	{
		dfs(p->to, dep + 1);
		size[x] += size[p->to];
	}
}

struct data
{
	int dep, x, id;
}d[maxn];

bool operator < (const data &a, const data &b)
{
	return a.dep < b.dep;
}

bool ans[maxn];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 2, x; i <= n; i++)
		scanf("%d", &x),
		add(x, i);
	dfs(1, 1);
	scanf("%s", s + 1);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &d[i].x, &d[i].dep), d[i].id = i;
	sort(d + 1, d + m + 1);
	for (int i = 1, x; i <= m; i++)
	{
		if (d[i].dep ^ d[i - 1].dep)
		{
			x = d[i - 1].dep;
			for (int j = 0; j < v[x].size(); j++)
				insert(dfn[v[x][j]], s[v[x][j]] - 'a');
			x = d[i].dep;
			for (int j = 0; j < v[x].size(); j++)
				insert(dfn[v[x][j]], s[v[x][j]] - 'a');		
		}
		x = query(dfn[d[i].x] + size[d[i].x] - 1) ^ query(dfn[d[i].x] - 1);
		ans[d[i].id] = __builtin_popcount(x) <= 1;
	}
	for (int i = 1; i <= m; i++)
		puts(ans[i] ? "Yes" : "No");
}