#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <map>
#include <string>

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

using namespace std;

const int maxn = 30;

struct node
{
	int v, cap;
	node() {}
	node(int v, int cap) :v(v), cap(cap) {}
};

bool operator < (const node &a, const node &b)
{
	return a.cap > b.cap;
}

int n, m, k;
map <string, int> name;
int g[maxn][maxn];
int dis[maxn];
int clo[maxn];
int pre[maxn];
int fst[maxn];
int mx[maxn];

node heap[maxn * maxn];

__attribute__((optimize(2))) int prim(int S, int id)
{
	int size = 0;
	heap[++size] = node(S, dis[S] = 0);
	int ans = 0;
	while (size)
	{
		int x = heap[1].v;
		pop_heap(heap + 1, heap + size-- + 1);
		if (!clo[x])
		{
			clo[x] = id;
			ans += dis[x];
			for (int i = 1; i < n; i++)
				if (!clo[i] && g[x][i] && tense(dis[i], g[x][i]))
				{
					pre[i] = x;
					heap[++size] = node(i, dis[i]);
					push_heap(heap + 1, heap + size + 1);
				}
		}
	}
	return ans;
}

__attribute__((optimize(2))) void update(int x, int fa, int dis)
{
	mx[x] = max(dis, g[x][fa]);
	for (int i = 1; i < n; i++)
		if (i ^ fa && g[x][i] && (pre[x] == i || pre[i] == x))
			update(i, x, mx[x]);
}

__attribute__((optimize(2))) int calc()
{
	int ans = 0, cnt = 1;
	for (int i = 0; i < n; i++)
		dis[i] = ~0u >> 1,
		clo[i] = pre[i] = fst[i] = 0;
	for (int i = 1; i < n; i++)
		if (!clo[i])
			ans += prim(i, cnt++);
	for (int i = 1, id; i < n; i++)
	{
		id = clo[i];
		if (g[0][i] && (!fst[id] || g[0][i] < g[0][fst[id]]))
			fst[id] = i;
	}
	for (int i = 1; i < cnt; i++)
	{
		ans += g[0][fst[i]];
		g[0][fst[i]] = g[fst[i]][0] = 0;
		update(fst[i], 0, 0);
	}
	k = k - cnt + 1;
	while (k--)
	{
		int x = 0;
		for (int i = 1; i < n; i++)
			if (g[0][i] && (x == 0 || mx[x] - g[0][x] < mx[i] - g[0][i]))
				x = i;
		if (mx[x] <= g[0][x])
			break;
		ans = ans - mx[x] + g[0][x];
		g[0][x] = g[x][0] = 0;
		int p = 0;
		for (int i = x; pre[i]; i = pre[i])
			if ((!p) || g[p][pre[p]] < g[i][pre[i]])
				p = i;
		pre[p] = 0;
		update(x, 0, 0);
	}
	return ans;
}

__attribute__((optimize(2))) int main() 
{
//	freopen("a.in", "r", stdin);
    char s1[20], s2[20];
    int cap;
    while (scanf("%d", &m) == 1) 
	{
		name.clear();
        name["Park"] = 0;
        n = 1;
        memset(g, 0, sizeof(g));
        while (m--) 
		{
            scanf("%s %s %d", s1, s2, &cap);
            if (!name.count(s1))
                name[s1] = n++;
            if (!name.count(s2))
                name[s2] = n++;
            int u = name[s1], v = name[s2];
            if (!g[u][v] || g[u][v] > cap)
                g[u][v] = g[v][u] = cap;
        }
        scanf("%d", &k);
        printf("Total miles driven: %d\n", calc());
    }
    return 0;
}