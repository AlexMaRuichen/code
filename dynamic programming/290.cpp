#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

const int maxn = 1e5 + 10;
const int maxm = 2e6 + 10;
const int mod = 998244353;

char getc()
{
	static const int len = 1 << 15;
	static char buf[len], *s, *t;
	if (s == t)
	{
		t = (s = buf) + fread(buf, 1, len, stdin);
		if (s == t)
			return EOF;
	}
	return *s++;
}

void read(register int &x)
{
	static char ch;
	x = 0;
	while (ch < '0')
		ch = getc();
	while (ch >= '0')
		x = (x << 1) + (x << 3) + ch - '0', ch = getc();
}

struct edge
{
	int to;
	edge *next;
	edge() {}
	edge(int to, edge *next) :to(to), next(next) {}
	void* operator new(size_t);
}*head[maxn], mem[maxm], *p;

void* edge :: operator new(size_t)
{
	return p++;
}

int deg[maxm];

void add(int x, int y)
{
	++deg[x];
	++deg[y];
	head[x] = new edge(y, head[x]);
	head[y] = new edge(x, head[y]);
}

int f[maxm] = {1, 1};
int dfn[maxn];
int fa[maxn];
bool v[maxn];
int cnt;

bool dfs(int x) 
{
	dfn[x] = ++cnt;
	for (edge *p = head[x]; p; p = p->next)
		if (!dfn[p->to]) 
		{
			fa[p->to] = x;
			if (dfs(p->to)) 
				return true; 
		}
		else if (dfn[p->to] > dfn[x])
		{
			deg[x] -= 2;
			for (int t = p->to; t ^ x; v[t] = true, deg[t] -= 2, t = fa[t])
				if (v[t]) 
					return true;
		}
	return false;
}

int main()
{
	int T;
	read(T);
	for (int i = 2; i <= 500000; i++) 
		f[i] = ((i - 1) * 1ll * f[i - 2] + f[i - 1]) % mod;
	while (T--) 
	{
		int n, m;
		read(n);
		read(m);
		p = mem;
		cnt = 0;
		for (int i = 1; i <= n; i++)
			dfn[i] = v[i] = deg[i] = 0, head[i] = NULL;
		for (int i = 1, x, y; i <= m; i++)
		{
			read(x);
			read(y);
			add(x, y);
		}
		if (dfs(1)) 
			puts("0");
		else 
		{
			int ans = 1;
			for (int i = 1; i <= n; i++) 
				ans = ans * 1ll * f[deg[i]] % mod;
			printf("%d\n",ans);
		}
	}
}