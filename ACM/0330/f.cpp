#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <stack>

using namespace std;

const int maxn = 1010;
const int maxm = 1000 * 1000 * 2 + 10;

int n,m;

int to[maxm];
int nex[maxm];
int head[maxn];
int tot = 1;

void add(int x, int y)
{
	to[++tot] = y;
	nex[tot] = head[x];
	head[x] = tot;

	to[++tot] = x;
	nex[tot] = head[y];
	head[y] = tot;
}

int cnt;
int dfn[maxn];
int low[maxn];
int sta[maxm];

void dfs(int x, int fa)
{
	dfn[x] = low[x] = ++cnt;

	for(int i = head[x]; i; i = nex[i])
	{
		if (sta[i] ^ -1 || to[i] == fa)
			continue;
		sta[i] = 1;
		sta[i ^ 1] = 0;
		if (!dfn[to[i]])
		{
			sta[i] = 1;
			dfs(to[i], x);
			low[x] = min(low[x], low[to[i]]);
			if(low[to[i]] > dfn[x])
				sta[i ^ 1] = 1;
		}
		else if (dfn[to[i]] < dfn[x])
			low[x] = min(low[x], dfn[to[i]]);
	}
}

int main()
{
	int tc = 0;
	while (scanf("%d%d", &n, &m) && n && m)
	{
		tot = 1;
		cnt = 0;
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(sta, -1, sizeof(sta));
		memset(head, 0, sizeof(head));
		for (int i = 1, x, y; i <= m; i++)
		{
			scanf("%d%d", &x, &y);
			add(x, y);
		}
		dfs(1, 1);
		printf("%d\n\n", ++tc);
		for (int i = 2; i <= tot; i++)
			if (sta[i])
				printf("%d %d\n", to[i ^ 1], to[i]);
		puts("#");
	}
}
