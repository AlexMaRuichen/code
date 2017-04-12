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

const int maxn = 30010;
const int inf = 1 << 30;

int mov[15] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

struct node
{
	int tot, head[maxn], next[maxn];
	int sta[maxn], sum[maxn];
	void clear()
	{
		memset(head, -1, sizeof(head));
		tot = 0;
	}
	void push(int st, int v)
	{
		int hash = st % maxn;
		for (int i = head[hash]; ~i; i = next[i])
			if (sta[i] == st)
			{
				tense(sum[i], v);
				return;
			}
		sta[tot] = st;
		sum[tot] = v;
		next[tot] = head[hash];
		head[hash] = tot++;
	}
}f[2];

inline int get(int st, int k)
{
	return 3 & (st >> mov[k]);
}

inline int py(int st, int k)
{
	return st << mov[k];
}

inline int clr(int st, int a, int b)
{
	return st & (~(3 << mov[a])) & (~(3 << mov[b]));
}

int n, m;
int map[20][20];

int dp()
{
	int ans =  inf;
	f[1].clear();
	f[1].push(0, 0);
	int c = 0, p = 1;
	int cnt1 = 0, cnt2 = 0;
	for (int i = 1; i <= n; i++)
	{
		f[c].clear();
		for (int k = 0; k < f[p].tot; k++)
			f[c].push(f[p].sta[k] << 2, f[p].sum[k]);
		swap(p, c);
		for (int j = 1; j <= m; j++, swap(p, c))
		{
			f[c].clear();
			for (int k = 0; k < f[p].tot; k++)
			{
				int l = get(f[p].sta[k], j - 1);
				int u = get(f[p].sta[k], j);
				int st = clr(f[p].sta[k], j, j - 1);
				int v = f[p].sum[k];
				if (!l && !u)
				{
					if (!map[i][j] || map[i][j] == 1)
						f[c].push(st, v);
					if (!map[i][j] && i < n && map[i + 1][j] != 1 && j < m && map[i][j + 1] != 1)
					{
						f[c].push(st | py(1, j - 1) | py(1, j), v + 1);
						f[c].push(st | py(2, j - 1) | py(2, j), v + 1);
					}
					if (i < n && map[i + 1][j] != 1 && map[i][j] >= 2)
						f[c].push(st | py(map[i][j] - 1, j - 1), v + 1);
					if (j < m && map[i][j + 1] != 1 && map[i][j] >= 2)
						f[c].push(st | py(map[i][j] - 1, j), v + 1);
				}
				else if (!l || !u)
				{
                    int e = l + u;
                    if (map[i][j] == 0) 
					{
                        if (i < n && map[i + 1][j] != 1)
                            f[c].push(st | py(e, j - 1), v + 1);
                        if (j < m && map[i][j + 1] != 1)
                            f[c].push(st | py(e, j), v + 1);
                    }
                    if (map[i][j] == 2 && e == 1) 
					{
                        if (st == 0 && cnt1 >= 1 && cnt2 >= 2) 
                            tense(ans, v + 1);
                        f[c].push(st, v + 1);
                    }
                    if (map[i][j] == 3 && e == 2) 
					{
                        if (st == 0 && cnt2 >= 1 && cnt1 >= 2)
                            tense(ans, v + 1);
                        f[c].push(st, v + 1);
                    }
				}
				else if (l == 1 && u == 1) 
				{
                    if (map[i][j] >= 2)
                        continue;
                    if (cnt1 >= 2) 
					{
                        if (cnt2 >= 2 && st == 0)
                            tense(ans, v + 1);
                    }
                    f[c].push(st, v + 1);
                } 
				else if (l == 2 && u == 2) 
				{
                    if (map[i][j] >= 2)
                        continue;
                    if (cnt2 >= 2) 
					{
                        if (cnt1 >= 2 && st == 0)
                            tense(ans, v + 1);
                    }
                    f[c].push(st, v + 1);
                }
				if (map[i][j] == 2)
					cnt1++;
				else if (map[i][j] == 3)
					cnt2++;
			}
		}
	}
	if (ans == inf)
		ans = 2;
	return ans;
}

int main()
{
	while (scanf("%d%d", &n, &m) && n && m)
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &map[i][j]);
		printf("%d\n", dp() - 2);
	}
}