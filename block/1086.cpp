#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 1010;

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

void add(int x, int y)
{
	head[x] = new edge(y, head[x]);
	head[y] = new edge(x, head[y]); 
}

int belong[maxn];
int root[maxn];
int stack[maxn];
int top;
int cnt;

int n, b;

void dfs(int x, int fa)
{
	int last = top;
	for (edge *p = head[x]; p; p = p->next)
		if (p->to ^ fa)
		{
			dfs(p->to, x);
			if (top - last >= b)
			{
				root[++cnt] = x;
				while (top ^ last)
					belong[stack[top--]] = cnt;
			}
		}
	stack[++top] = x;
}

int main()
{
	scanf("%d%d", &n, &b);
	for (int i = 1, x, y; i < n; i++)
	{
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	dfs(1, 1);	
	while (top)
		belong[stack[top--]] = cnt;
	printf("%d\n", cnt);
	for (int i = 1; i <= n; i++)
		printf("%d%c", belong[i], i == n ? '\n' : ' ');
	for (int i = 1; i <= cnt; i++)
		printf("%d%c", root[i], i == n ? '\n' : ' ');
}