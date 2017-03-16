#include <stdio.h>
#include <math.h>

#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 1e5 + 10;
const int LOG = 17;

inline char getc()
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

int N, M, Q;

struct edge
{
	int to;
	edge *next;
	edge() {}
	edge(int to, edge *next) :to(to), next(next) {}
	void* operator new(size_t);
}*head[maxn], emem[maxn << 1];

void* edge :: operator new(size_t)
{
	static edge *p = emem;
	return p++;
}

void add(int x, int y)
{
	head[x] = new edge(y, head[x]);
	head[y] = new edge(x, head[y]);
}

struct query
{
	int x, y, pos;
}q[maxn];

int pos[maxn];
int belong[maxn];

int cntq = 0, cntm = 0;


bool operator < (const query &a, const query &b)
{
	if	(cntm)
	{
		if(belong[a.x] ^ belong[b.x])
			return belong[a.x]<belong[b.x];
		if(belong[a.y] ^ belong[b.y])
			return belong[a.y]<belong[b.y];
		return a.pos < b.pos;
	}
	else
	{
		if(belong[a.x] ^ belong[b.x])
			return belong[a.x]<belong[b.x];
		return ::pos[a.y] < ::pos[b.y];
	}
}

struct modify
{
	int x, v1, v2, pos;
}m[maxn];

int fa[LOG + 1][maxn];
int dep[maxn];

void dfsfa(int x, int d)
{
	dep[x] = d;
	for (int i = 1; i <= LOG; i++)
		fa[i][x] = fa[i - 1][fa[i - 1][x]];
	for (edge *p = head[x]; p; p = p->next)
		if (p->to ^ fa[0][x])
			fa[0][p->to] = x,
			dfsfa(p->to, d + 1);
}

int top;
int block;
int stack[maxn];
int cntb;

void dfs(int x)
{
	static int dfn;
	int last = top;
	pos[x] = ++dfn;
	for (edge *p = head[x]; p; p = p->next)
		if (p->to ^ fa[0][x])
		{
			dfs(p->to);
			if (top - last >= block)
			{
				++cntb;
				while (top ^ last)
					belong[stack[top--]] = cntb;
			}
		}
	stack[++top] = x;
}
 
inline int getfa(int x, int y)
{
	for (int i = 0; i <= LOG; i++)
		if (y & (1 << i))
			x = fa[i][x];
	return x;
}

inline int LCA(int x, int y)
{
	if (dep[x] < dep[y])
		swap(x, y);
	x = getfa(x, dep[x] - dep[y]);
	if (x == y)
		return x;
	for (int i = LOG; ~i; i--)
		if (fa[i][x] ^ fa[i][y])
			x = fa[i][x],
			y = fa[i][y];
	return fa[0][x];
}

bool vis[maxn];
int a[maxn];
int cnt[maxn];
int v[maxn];
int w[maxn];
LL now;

inline void XOR(int x)
{
    vis[x] ^= 1;  
    if (vis[x])  
    {  
        ++cnt[a[x]];  
        if (cnt[a[x]] >= 1)  
            now += v[a[x]] * 1ll * w[cnt[a[x]]];  
    }  
    else  
    {  
        if (cnt[a[x]] >= 1)  
            now -= v[a[x]] * 1ll * w[cnt[a[x]]];  
        --cnt[a[x]];  
    }  
}

void change(const modify &t, bool flag)
{
	if (flag)
	{
		a[t.x] = t.v1;  
		if(vis[t.x])  
		{  
			if(cnt[t.v2]>=1)  
				now -= v[t.v2] * 1ll * w[cnt[t.v2]];  
			cnt[t.v2]--;  
			cnt[t.v1]++;  
			if(cnt[t.v1]>=1)  
				now += v[t.v1] * 1ll * w[cnt[t.v1]];  
		}  
	}
	else
	{
		a[t.x] = t.v2;  
		if(vis[t.x])  
		{  
			if(cnt[t.v1]>=1)  
				now -= v[t.v1] * 1ll * w[cnt[t.v1]];  
			cnt[t.v1]--;  
			cnt[t.v2]++;  
			if(cnt[t.v2]>=1)  
				now += v[t.v2] * 1ll * w[cnt[t.v2]];  
		}  
	}
}

LL ans[maxn];

int main()
{
	read(N);
	read(M);
	read(Q);
	for (int i = 1; i <= M; i++)
		read(v[i]);
	for (int i = 1; i <= N; i++)
		read(w[i]);
	for (int i = 1, x, y; i < N; i++)
	{
		read(x);
		read(y);
		add(x, y);
	}
	for (int i = 1; i <= N; i++)
		read(a[i]);
	for (int i = 1, opt, x, y; i <= Q; i++)
	{
		read(opt);
		read(x);
		read(y);
		if (opt == 1)
		{
			++cntq;
			q[cntq].pos = cntq;
			q[cntq].x = x;
			q[cntq].y = y;
		}
		else
		{
			m[++cntm].x = x;
			m[cntm].v1 = a[x];
			m[cntm].v2 = a[x] = y;
			m[cntm].pos = cntq;
		}
	}
	Q = cntq;
	block = cntm ? pow(N, 2.0 / 3.0) + 1 : sqrt(N) + 1;
	dfsfa(1, 1);
	dfs(1);
	while (top)
		belong[stack[top--]] = cntb;
	cntq = cntm;
	for (int i = 1; i <= Q; i++)
		if (pos[q[i].x] > pos[q[i].y])
			swap(q[i].x, q[i].y);
	sort(q + 1, q + Q + 1);
	for (int i = 1, x, l = 1, r = 1, lca; i <= Q; i++)
	{
		lca = LCA(l, q[i].x);
		for (x = l; x ^ lca; x = fa[0][x])
			XOR(x);
		for (x = q[i].x ; x ^ lca; x = fa[0][x])
			XOR(x);
		lca = LCA(r, q[i].y);
		for (x = r; x ^ lca; x = fa[0][x])
			XOR(x);
		for (x = q[i].y; x ^ lca; x = fa[0][x])
			XOR(x);
		lca = LCA(l = q[i].x, r = q[i].y);
		XOR(lca);
		while (cntq > 0 && m[cntq].pos >= q[i].pos)
			change(m[cntq--], true);
		while (cntq < cntm && m[cntq + 1].pos < q[i].pos)
			change(m[++cntq], false);
		ans[q[i].pos] = now;
		XOR(lca);
	}
	for (int i = 1; i <= Q; i++)
		printf("%lld\n", ans[i]);
}