#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

const int maxn = 50010;

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}
template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

struct edge
{
	int to, len;
	edge *next;
	edge() {}
	edge(int to, int len, edge *next) :to(to), len(len), next(next) {}
	void* operator new(size_t);
}*head[maxn], mem[maxn << 1], *p;

void* edge :: operator new(size_t)
{
	return p++;
}

void add(int x, int y, int z)
{
	head[x] = new edge(y, z, head[x]);
	head[y] = new edge(x, z, head[y]);
}

int dis[maxn];
int up[maxn];
int dn[maxn];
int sd[maxn];

const int LOG = 16;
int mn[LOG + 1][maxn];
int mx[LOG + 1][maxn];
int  l[maxn];

void dfs(int x, int fa)
{
	for (edge *p = head[x]; p; p = p->next)
		if (p->to ^ fa)
		{
			dfs(p->to, x);
			if (dn[p->to] + p->len > dn[x])
				sd[x] = dn[x], dn[x] = dn[p->to] + p->len;
			else if (dn[p->to] + p->len > sd[x])
				sd[x] = dn[p->to] + p->len; 
		}
}

void rdfs(int x, int fa, int dep)
{
	up[x] = dep;
	for (edge *p = head[x]; p; p = p->next)
		if (p->to ^ fa)
		{
			if (dn[p->to] + p->len == dn[x])
				rdfs(p->to, x, max(sd[x], dep) + p->len);
			else
				rdfs(p->to, x, max(dn[x], dep) + p->len);
		}
}

inline int qmx(int s, int len)
{
	return max(mx[l[len]][s], mx[l[len]][s + len - (1 << l[len])]);
}

inline int qmn(int s, int len)
{
	return min(mn[l[len]][s], mn[l[len]][s + len - (1 << l[len])]);
}

int main()
{
	int n, m;
	for (int i = 2; i < maxn; i++)
		l[i] = l[i >> 1] + 1;
	while (scanf("%d%d", &n, &m) && n && m)
	{
		memset(head, 0, sizeof(head));
		memset(dis, 0 ,sizeof(dis));
		memset(up, 0, sizeof(up));
		memset(dn, 0, sizeof(dn));
		memset(sd, 0, sizeof(sd));
		memset(mx, 0, sizeof(mx));
		memset(mn, 0, sizeof(mn));
		p = mem;
		for (int i = 1, x, y, z; i < n; i++)
			scanf("%d%d%d", &x, &y, &z),
			add(x, y, z);
		dfs(1, 1);
		rdfs(1, 1, 0);
		for (int i = 1; i <= n; i++)
			mn[0][i] = mx[0][i] = max(up[i], dn[i]);
		for (int i = 1; i <= LOG; i++)
			for (int j = 1; j <= n - (1 << (i - 1)); j++)
			{
				mn[i][j] = min(mn[i - 1][j], mn[i - 1][j + (1 << (i - 1))]);
				mx[i][j] = max(mx[i - 1][j], mx[i - 1][j + (1 << (i - 1))]);
			}
		while (m--)
		{
			int q, l = 1, r = 1, ans = 0;
			scanf("%d", &q);
			while (r <= n)
			{
				while (l <= r && qmx(l, r - l + 1) - qmn(l, r - l + 1) > q)
					l++;
				relax(ans, r - l + 1);
				r++;
			}
			printf("%d\n", ans);
		}
	}
}