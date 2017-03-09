#include <stdio.h>
#include <math.h>
#include <string.h>

#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 110;
const int maxm = 5000;
const int inf = 1e9;

struct point
{
	double x, y;
	point() {}
	point(double x, double y) :x(x), y(y) {}
}p[maxn], o[maxn];

point operator + (const point &a, const point &b)
{
	return point(a.x + b.x, a.y + b.y);
}

point operator - (const point &a, const point &b)
{
	return point(a.x - b.x, a.y - b.y);
}

double operator * (const point &a, const point &b)
{
	return a.x * b.y - a.y * b.x;
}

double operator ^ (const point &a, const point &b)
{
	return a.x * b.x + a.y * b.y;
}

vector <int> to[maxn];

int tot;
struct line
{
	int x, y, cost, bel, rev;
	double alpha;
	line() {}
	line(int x, int y, int cost) :x(x), y(y), cost(cost)
	{
		bel = 0;
		alpha = atan2(p[y].y - p[x].y, p[y].x - p[x].x);
	}
}l[maxm];

bool cmp(const int &x, const int &y)
{
	return l[x].alpha < l[y].alpha;
}

vector <int> polygon[maxm];

int P, n, m;

void DFS(int edgeid, int polyid)
{
	l[edgeid].bel = polyid;
	polygon[polyid].push_back(edgeid);
	int x = l[edgeid].y;
//	printf("%d %d\n", polyid, x);
	int pos = lower_bound(to[x].begin(), to[x].end(), l[edgeid].rev, cmp) - to[x].begin() + 1;
	if (pos == to[x].size())
		pos = 0;
	if (l[to[x][pos]].bel)
		return;
	DFS(to[x][pos], polyid);
}

void link(int x, int y, int z)
{
	l[++tot] = line(x, y, z);
	l[++tot] = line(y, x, z);

	l[tot].rev = tot - 1;
	l[tot - 1].rev = tot;

	to[x].push_back(tot - 1);
	to[y].push_back(tot);
}

double area(int x)
{
	int size = polygon[x].size();
	double ans = 0;
	int pid = l[polygon[x][0]].x;
	for (int i = 0; i < size; i++)
		ans += (p[l[polygon[x][i]].x] - p[pid]) * (p[l[polygon[x][i]].y] - p[pid]);
	return ans;
}

struct edge
{
	int to, len;
	edge *next, *rev;
	edge() {}
	edge(int to, int len, edge *next) :to(to), len(len), next(next) {}
	void* operator new(size_t);
}*head[maxm], *bak[maxm], mem[100010], *g = mem, *bakptr;

void* edge :: operator new(size_t)
{
	return g++;
}

void add(int x, int y ,int z)
{
	head[x] = new edge(y, z, head[x]);
	head[y] = new edge(x, 0, head[y]);
	head[x]->rev = head[y];
	head[y]->rev = head[x];
}

queue <int> q;
int dep[maxm];
int S, T;

bool bfs()
{
	memset(dep, -1, sizeof(dep));
	dep[S] = 1;
	q.push(S);
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		for (edge *ptr = head[x]; ptr; ptr = ptr->next)
			if (ptr->len && dep[ptr->to] < 0)
				dep[ptr->to] = dep[x] + 1, q.push(ptr->to);
	}
	return dep[T] ^ -1;
}

int dfs(int x, int f)
{
	if (x == T)
		return f;
	int w, used = 0;
	for (edge *ptr = head[x]; ptr; ptr = ptr->next)
		if (ptr->len && dep[ptr->to] == dep[x] + 1)
		{
			w = dfs(ptr->to, min(f - used, ptr->len));
			ptr->len -= w;
			ptr->rev->len += w;
			used += w;
			if (used == f)
				return f;
		}
	dep[x] = -1;
	return used;
}

int dinic()
{
	int ans = 0;
	while (bfs())
		ans += dfs(S, inf);
	return ans;
}

int inside[maxm];

bool attach(int polyid, int oid)
{
	for (int i = 0; i < polygon[polyid].size(); i++)
		if((o[oid] - p[l[polygon[polyid][i]].x]) * (p[l[polygon[polyid][i]].y] - p[l[polygon[polyid][i]].x]) < 0)
			return false;
	return true;
}

int ans[maxm];

int main()
{
	scanf("%d%d%d", &P, &n, &m);
	for (int i = 1; i <= P; i++)
		scanf("%lf%lf", &o[i].x, &o[i].y);
	for (int i = 1; i <= n; i++)
		scanf("%lf%lf", &p[i].x, &p[i].y);
	for (int i = 1, x, y, z; i <= m; i++)
	{
		scanf("%d%d%d", &x, &y, &z);
		link(x, y, z);
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		sort(to[i].begin(), to[i].end(), cmp);
	for (int i = 1; i <= n; i++)
		for (int j = to[i].size() - 1; ~j; j--)
			if (!l[to[i][j]].bel)
				DFS(to[i][j], ++cnt);
/*	for (int i = 1; i <= cnt; i++, puts(""))
		for (int j = 0; j < polygon[i].size(); j++)
			printf("%d ", polygon[i][j]);
	for (int i = 1; i <= cnt; i++)
		printf("%lf\n", area(i));*/

	S = cnt + 1, T = cnt + 2;
	for (int i = 1; i <= cnt; i++)
		if (area(i) > 0)
			add(i, T, inf);
		else
			for (int j = 1; j <= P; j++)
				if (attach(i, j))
					inside[j] = i;
	for (int i = 1; i <= cnt; i++)
		for (int j = polygon[i].size() - 1; ~j; j--)
			add(i, l[l[polygon[i][j]].rev].bel, l[polygon[i][j]].cost);
	memcpy(bak, head, sizeof(head));
	memset(ans, 0x3f, sizeof(ans));
	bakptr = g;
	int mask = 1 << P;
	for (int i = 1; i < mask; i++)
	{
		int countbits = 0;
		for (int j = 0; j < P; j++)
			if (i & (1 << j))
				++countbits, add(S, inside[j + 1], inf);
		ans[countbits] = min(ans[countbits], dinic());
		for (edge *tmp = mem; tmp != g; tmp += 2)
			tmp->len += tmp->rev->len, tmp->rev->len = 0;
		memcpy(head, bak, sizeof(head));
		g = bakptr;
	}
	for (int i = 1; i <= P; i++)
		printf("%d\n", ans[i]);
}