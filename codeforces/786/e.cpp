#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 2e4 + 10;
const int inf = 1e9;

struct EDGE
{
	int to;
	EDGE *next;
	EDGE() {}
	EDGE(int to, EDGE *next) :to(to), next(next) {}
	void* operator new(size_t);
}*HEAD[maxn], Emem[maxn << 1];

void* EDGE :: operator new(size_t)
{
	static EDGE *p = Emem;
	return p++;
}

void add(int x, int y)
{
	HEAD[x] = new EDGE(y, HEAD[x]);
	HEAD[y] = new EDGE(x, HEAD[y]);
}

int fa[maxn];
int dep[maxn * 5];
int top[maxn];
int son[maxn];
int size[maxn];
int pos[maxn];

void dfs_son(int x, int f)
{
	dep[x] = dep[f] + 1;
	fa[x] = f;
	size[x] = 1;
	for (EDGE *p = HEAD[x]; p; p = p->next)
		if (p->to ^ f)
		{
			dfs_son(p->to, x);
			size[x] += size[p->to];
			son[x] = size[p->to] > size[son[x]] ? p->to : son[x];
		}
}

void dfs_top(int x, int t)
{
	static int cnt;
	pos[x] = ++cnt;
	top[x] = t;
	if (son[x])
		dfs_top(son[x], t);
	for (EDGE *p = HEAD[x]; p; p = p->next)
		if (p->to ^ fa[x] && p->to ^ son[x])
			dfs_top(p->to, p->to);
}


struct edge
{
	int to, len;
	edge *next, *rev;
	edge() {}
	edge(int to, int len, edge *next) :to(to), len(len), next(next) {}
	void* operator new(size_t);
}*head[maxn], emem[maxn << 1];

void* edge :: operator new(size_t)
{
	static edge *p = emem;
	return p++;
}

void add(int x, int y, int z)
{
	head[x] = new edge(y, z, head[x]);
	head[y] = new edge(x, 0, head[y]);
	head[x]->rev = head[y];
	head[y]->rev = head[x];
}

struct seg
{
	seg *ls, *rs;
	int lab;
	void* operator new(size_t);
}*root, smem[maxn << 2];

void*  seg :: operator new(size_t)
{
	static seg *p = smem;
	return p++;
}

int segcnt;
int n, m;
int S, T;
void build(seg *&x, int l, int r)
{
	x = new seg();
	x->lab = ++segcnt;
	if (l == r)
	{
		add(x->lab, m + l, inf);
		add(m + l, T, 1);
		return;
	}
	int mid = l + r >> 1;
	build(x->ls, l, mid);
	build(x->rs, mid + 1, r);
	add(x->lab, x->ls->lab, inf);
	add(x->lab, x->rs->lab, inf);
}

void query(seg *x, int lab, int l, int r, int L, int R)
{
	if (l == L && r == R)
	{
		add(lab, x->lab, inf);
		return;
	}
	int mid = L + R >> 1;
	if (mid >= r)
		query(x->ls, lab, l, r, L, mid);
	else if(mid < l)
		query(x->rs, lab, l, r, mid + 1, R);
	else
		query(x->ls, lab, l, mid, L, mid),
		query(x->rs, lab, mid + 1, r, mid + 1, R);
}

void work(int lab, int x, int y)
{
	while (top[x] ^ top[y])
	{
		if (dep[top[x]] < dep[top[y]])
			swap(x, y);
		query(root, lab, pos[top[x]], pos[x], 1, n);
		x = fa[top[x]];
	}
	if (dep[x] > dep[y])
		swap(x, y);
	if (x ^ y)
		query(root, lab, pos[x] + 1, pos[y], 1, n);
}

queue <int> q;

bool bfs()
{
	memset(dep, -1, sizeof(dep));
	dep[S]=1;
	q.push(S);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(edge *p=head[x];p;p=p->next)
			if(p->len&&dep[p->to]<0)
				dep[p->to]=dep[x]+1,q.push(p->to);
	}
	return dep[T]^-1;
}
int dfs(int x,int f)
{
	if(x==T)
		return f;
	int w,used=0;
	for(edge *p=head[x];p;p=p->next)
		if(p->len&&dep[p->to]==dep[x]+1)
		{
			w=dfs(p->to,min(p->len,f-used));
			p->len-=w;
			p->rev->len+=w;
			used+=w;
			if(used==f)
				return f;
		}
	if(used^f)
		dep[x]=-1;
	return used;
}

int dinic()
{
	int ans=0;
	while(bfs())
		ans+=dfs(S,inf);
	return ans;
}

int ans1[maxn];
int ans2[maxn];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i < n; i++)
		scanf("%d%d", &x, &y),
		add(x, y);
	dfs_son(1, 1);
	dfs_top(1, 1);
	segcnt = n + m;
	S = ++segcnt;
	T = ++segcnt;
	build(root, 1, n);
	for (int i = 1, x, y; i <= m; i++)
	{
		add(S, i ,1);
		scanf("%d%d", &x, &y);
		work(i, x, y);
	}
	printf("%d\n", dinic());
	for (edge *p = head[S]; p; p = p->next)
		if (!p->len && p->to >= 1 && p->to <= m)
			ans1[++ans1[0]] = p->to;
	for (edge *p = head[T]; p; p = p->next)
		if (!p->rev->len && p->to > m && p->to <= n + m)
			ans2[++ans2[0]] = p->to;
	printf("%d ", ans1[0]);
	for (int i = 1; i <= ans1[0]; i++) 
		printf("%d ", ans1[i]);
	puts("");
	printf("%d ", ans2[0]);
	for (int i = 1; i <= ans2[0]; i++) 
		printf("%d ", ans2[i] - m);
	puts("");
}