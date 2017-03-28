#include <stdio.h>

#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 150010;

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

int deg[maxn];

void add(int x, int y)
{
	++deg[x];
	++deg[y];
	head[x] = new edge(y, head[x]);
	head[y] = new edge(x, head[y]);
}

int n, m;

int stack[maxn];
int top, cnt;

bool v[maxn];

queue <int> q;

bool bfs(int S)
{
	cnt = 0;
	stack[top = 1] = S;
	q.push(S);
	v[S] = true;
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		++cnt;
		for (edge *p = head[x]; p; p = p->next)
			if (!v[p->to])
				stack[++top] = p->to,
				v[p->to] = true,
				q.push(p->to);
	}
	for (int i = 1; i <= top; i++)
		if (deg[stack[i]] ^ (cnt - 1))
			return false;
	return true;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= m; i++)
	{
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	for (int i = 1; i <= n; i++)
		if (!v[i] && !bfs(i))
			return puts("NO"), 0;
	puts("YES");
}