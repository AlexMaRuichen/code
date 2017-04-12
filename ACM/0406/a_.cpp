#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

const int N = 30;

struct node 
{
    int v, cap;
    node() 
	{}
    node(int _v, int _cap) : v(_v), cap(_cap) 
	{}
    bool operator<(const node &a) const 
	{ 
		return a.cap < cap; 
	}
};

map<string, int> mp;
int g[N][N], dis[N], clo[N], pre[N], fst[N], max_side[N];
int n, m, k;

int Prim(int src, int id) 
{
    priority_queue<node> q;
    while (!q.empty())
        q.pop();
    dis[src] = 0;
    q.push(node(src, 0));
    int ans = 0;
    while (!q.empty()) 
	{
        node cur = q.top();
        q.pop();
        int u = cur.v;
        if (!clo[u]) 
		{
            clo[u] = id;
            ans += dis[u];
            for (int i = 1; i < n; i++)
                if (!clo[i] && g[u][i] != 0 && dis[i] > g[u][i]) 
				{ //满足松弛条件
                    pre[i] = u;
                    dis[i] = g[u][i];
                    q.push(node(i, dis[i]));
                }
        }
    }
    return ans;
}

void update(int cur, int last, int maxside) 
{ //也是一个dfs过程,直到搜回到起点,同时完成了max_side[]更新
    max_side[cur] = maxside > g[cur][last] ? maxside : g[cur][last];
    for (int i = 1; i < n; i++)
        if (i != last && g[cur][i] != 0 && (pre[cur] == i || pre[i] == cur))
            update(i, cur, max_side[cur]);
}

void Solve() 
{
    int i, res, cnt;
    for (i = 0; i < n; i++) 
	{
        dis[i] = INT_MAX;
        clo[i] = pre[i] = fst[i] = 0;
    }
    res = 0, cnt = 1; //除去根节点后,图中的连通子图个数,即最小生成树个数
    for (i = 1; i < n; i++)
        if (!clo[i])
            res += Prim(i, cnt++);
    for (i = 1; i < n; i++) 
	{ //找到每个生成树和 Park 最近的点使之和 Park 相连
        int id = clo[i];
        if (g[0][i] != 0 && (!fst[id] || g[0][i] < g[0][fst[id]]))
            fst[id] = i;
    }
    for (i = 1; i < cnt; i++) 
	{ //把m个生成树上和根节点相连的边加入res,得到关于Park的最小m度生成树
        res += g[0][fst[i]];
        g[0][fst[i]] = g[fst[i]][0] = 0; //之所以用邻接阵就是因为删除边很方便
        update(fst[i], 0, 0);
    }

/*
添删操作:将根节点和生成树中一个点相连,会产生一个环,将这个环上(除刚添的那条边外)权值最大的边删去.
由于每次操作都会给总权值带来影响d=max_side[tmp]-mat[0][tmp],
我们需要得到最小生成树,所以我们就要求 d 尽量大
*/

    k = k - cnt + 1; //接下来重复操作,直到度数满足条件
    while (k--) 
	{
        int tmp = 0;
        for (i = 1; i < n; i++) //找 d
                                //值最大的点(就是说完成添删操作后可以使总边权减小的值最大)
            if (g[0][i] != 0 && (tmp == 0 || max_side[tmp] - g[0][tmp] < max_side[i] - g[0][i]))
                tmp = i;
        if (max_side[tmp] <= g[0][tmp]) //总权值无法再减小
            break;
        res = res - max_side[tmp] + g[0][tmp];
        g[0][tmp] = g[tmp][0] = 0;
        int p = 0;
        for (i = tmp; pre[i] != 0; i = pre[i])
            if (p == 0 || g[p][pre[p]] < g[i][pre[i]])
                p = i;
        pre[p] = 0;
        update(tmp, 0, 0);
    }
    printf("Total miles driven: %d\n", res);
}

int main() 
{

    // freopen("input.txt","r",stdin);

    char s1[20], s2[20];
    int cap;
    while (~scanf("%d", &m)) 
	{
        mp["Park"] = 0;
        n = 1;
        memset(g, 0, sizeof(g));
        while (m--) 
		{
            scanf("%s %s %d", s1, s2, &cap);
            if (!mp.count(s1))
                mp[s1] = n++;
            if (!mp.count(s2))
                mp[s2] = n++;
            int u = mp[s1], v = mp[s2];
            if (!g[u][v] || g[u][v] > cap)
                g[u][v] = g[v][u] = cap;
        }
        scanf("%d", &k);
        Solve();
    }
    return 0;
}