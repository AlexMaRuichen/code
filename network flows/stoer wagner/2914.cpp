#include <stdio.h>
#include <string.h>

#include <algorithm>

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

using namespace std;

const int maxn = 510;
const int inf = 1e9;

int map[maxn][maxn];
int fa[maxn];
bool v[maxn];
int dis[maxn];

int stoer_wagner(int n)
{
	int ans = inf;
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	while (n > 1)
	{
		int pre = 1;
		memset(v, 0, sizeof(v));
		memset(dis, 0, sizeof(dis));
		for (int i = 2; i <= n; i++)
		{
			int k = 0;
			for (int j = 2; j <= n; j++)
				if (!v[fa[j]])
				{
					dis[fa[j]] += map[fa[pre]][fa[j]];
					if (!k || dis[fa[k]] < dis[fa[j]])
						k = j;
				}
			v[fa[k]] = true;
			if (i == n)
			{
				tense(ans, dis[fa[k]]);
				for (int j = 1; j <= n; j++)
					map[fa[pre]][fa[j]] += map[fa[j]][fa[k]],
					map[fa[j]][fa[pre]] += map[fa[j]][fa[k]];
				fa[k] = fa[n--];
			}
			pre = k;
		}
	}
	return ans;
}

int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m) == 2)    
	{
		memset(map, 0, sizeof(map));
		for (int i = 1, x, y, z; i <= m; i++)
			scanf("%d%d%d", &x, &y, &z),
			++x,
			++y,
			map[x][y] += z,
			map[y][x] += z;
		printf("%d\n", stoer_wagner(n));
	}
}