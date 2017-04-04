#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 250;
const int inf = 1e9;

int f[maxn][maxn];
int k, c, m, n;

int S, T;

queue <int> q;

struct edge
{
	int to, len;
	edge *next, *rev;
	edge() {}
	edge(int to, int len, edge *next) :to(to), len(len), next(next) {}
	void* operator new(size_t);
}*head[maxn], mem[maxn * maxn], *p;

void* edge :: operator new(size_t)
{
	return p++;
}

void add(int x, int y, int z)
{
	head[x] = new edge(y, z, head[x]);
	head[y] = new edge(x, 0, head[y]);
	head[x]->rev = head[y];
	head[y]->rev = head[x];
}

int dep[maxn];

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


bool check(int x)
{
	static int cnt[40];
	memset(cnt, 0, sizeof(cnt));
	memset(head, 0, sizeof(head));
	p = mem;
	for (int i = k + 1; i <= n; i++)
		for (int j = 1; j <= k; j++)
			if (f[i][j] <= x)
				add(i, j, 1);
	for (int i = k + 1; i <= n; i++)
		add(S, i, 1);
	for (int i = 1; i <= k; i++)
		add(i, T, m);
	return dinic() >= c;
}

int main()
{
	scanf("%d%d%d", &k, &c, &m);
	n = k + c;
	S = n + 1, T = n + 2;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &f[i][j]);
			if (!f[i][j])
				f[i][j] = 1e9;
		}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
/*	for (int i = 1; i <= n; i++, puts(""))
		for (int j = 1; j <= n; j++)
			printf("%d ", f[i][j]);*/
	int l = 0, r = 1e9, mid;
	while (l < r)
	{
		mid = l + r >> 1;
		check(mid) ? r = mid : l = mid + 1;
	}
	printf("%d\n", l);
}