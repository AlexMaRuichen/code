#include <stdio.h>

#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 100010;

struct SAM
{
    SAM *ch[10], *fa;
    int len;
	bool v;
    SAM() {}
    void *operator new(size_t);
} *root = new SAM(), *node[maxn], smem[maxn * 20];

void* SAM :: operator new(size_t)
{
	static SAM *p = smem;
	return p++;
}

SAM* insert(SAM *p, int x)
{
    if (p->ch[x] && p->ch[x]->len == p->len + 1)
		return p->ch[x];
    SAM *np = new SAM();
    np->len = p->len + 1;
    while (p && !p->ch[x])
		p->ch[x] = np, p = p->fa;
    if (!p)
		np->fa = root;
    else
    {
		SAM *q = p->ch[x];
		if (q->len == p->len + 1)
			np->fa = q;
		else
		{
			SAM *nq = new SAM();
			*nq = *q;
			nq->len = p->len + 1;
			nq->fa = q->fa;
			q->fa = np->fa = nq;
			while (p && p->ch[x] == q)
				p->ch[x] = nq, p = p->fa;
		}
    }
	return np;
}

int a[maxn];

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

int deg[maxn];

void add(int x, int y)
{
	head[x] = new edge(y, head[x]);
	head[y] = new edge(x, head[y]);
	++deg[x];
	++deg[y];
}

void dfs(int x, int fa)
{
	node[x] = insert(node[fa], a[x]);
	for (edge *p = head[x]; p; p = p->next)
		if (p->to ^ fa)
			dfs(p->to, x);
}

long long ans;
queue <SAM*> q;

int n, c;

void bfs()
{
	while (!q.empty())
		q.pop();
	q.push(root);
	while (!q.empty())
	{
		SAM *x = q.front();
		q.pop();
		if (x != root)
			ans += x->len - x->fa->len;
		for (int i = 0; i < c; i++)
			if (x->ch[i] && !x->ch[i]->v)
				x->ch[i]->v = true, q.push(x->ch[i]);
	}
}

int main()
{
	scanf("%d%d", &n, &c);
	for (int i = 1; i <= n; i++)  
		scanf("%d", &a[i]);  
	for (int i = 1, x, y; i < n; i++)  
	{  
		scanf("%d%d", &x, &y);
		add(x, y);
	}  
	node[0] = root;  
	for (int i = 1; i <= n; i++)  
		if (deg[i] == 1)  
			dfs(i, 0);  
	bfs();  
	printf("%lld\n", ans);
}