#include <cstdio>
#include <cstring>
#include <algorithm>
#define M 250010

using namespace std;

char inp[33554432], *inpch = inp;

int Head[M], Next[M], Go[M], Pre[510], Nxt[510], F[510], S[510], Q[510], Vis[510], *Top = Q, Cnt = 0, Tim = 0, n, m, x, y;

inline void addedge(int x, int y)
{
	Go[++Cnt] = y;
	Next[Cnt] = Head[x];
	Head[x] = Cnt;
}

int find(int x)
{
	return x == F[x] ? x : F[x] = find(F[x]);
}

int lca(int x, int y)
{
	for(Tim++, x = find(x), y = find(y); ; x ^= y ^= x ^= y)
		if(x)
		{
			if(Vis[x] == Tim) return x;
			Vis[x] = Tim;
			x = find(Pre[Nxt[x]]);
		}
}

void blossom(int x, int y, int l)
{
	while(find(x) != l)
	{
		Pre[x] = y, y = Nxt[x];
		if(S[y] == 1) S[*Top = y] = 0, *Top++;
		if(F[x] == x) F[x] = l;
		if(F[y] == y) F[y] = l;
		x = Pre[y];
	}
}

int Match(int x)
{
	for(int i = 1; i <= n; i++) F[i] = i;
	memset(S, -1, sizeof S);
	S[*(Top = Q) = x] = 0, Top++;
	for(int *i = Q; i != Top; *i++)
		for(int T = Head[*i]; T; T = Next[T])
		{
			int g = Go[T];
			if(S[g] == -1)
			{
				Pre[g] = *i, S[g] = 1;
				if(!Nxt[g])
				{
					for(int u = g, v = *i, lst; v; u = lst, v = Pre[u])
						lst = Nxt[v], Nxt[v] = u, Nxt[u] = v;
					return 1;
				}
				S[*Top = Nxt[g]] = 0, *Top++;
			}
			else if(!S[g] && find(g) != find(*i))
			{
				int l = lca(g, *i);
				blossom(g, *i, l);
				blossom(*i, g, l);
			}
		}
	return 0;
}

inline void Read(int& x)
{
	x = 0;
	while(*inpch < '0') *inpch++;
	while(*inpch >= '0') x = x * 10 + *inpch++ - '0';
}

int main()
{
	fread(inp, 1, 33554432, stdin);
	Read(n), Read(m);
	for(int i = 1; i <= m; i++)
	{
		Read(x), Read(y);
		addedge(x, y);
		addedge(y, x);
	}
	int ans = 0;
	for(int i = n; i >= 1; i--)
		if(!Nxt[i]) ans += Match(i);
	printf("%d\n", ans);
	for(int i = 1; i <= n; i++) printf("%d ", Nxt[i]);
	putchar('\n');
	return 0;
}
