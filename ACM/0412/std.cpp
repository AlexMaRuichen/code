#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
const int maxn = 30001, INF = 1 << 30;
int mov[15] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
struct node 
{
    int size, head[maxn], next[maxn];
    int sta[maxn], sum[maxn];
    void clear() 
	{
        memset(head, -1, sizeof(head));
        size = 0;
    }
    void push(int st, const int v) 
	{
        int hash = st % maxn;
        for (int i = head[hash]; i >= 0; i = next[i]) 
		{
            if (sta[i] == st) 
			{
                sum[i] = min(sum[i], v);
                return;
            }
        }
        sta[size] = st, sum[size] = v;
        next[size] = head[hash], head[hash] = size++;
    }
} dp[2];
inline int getbit(int st, int k) 
{ 
	return 3 & (st >> mov[k]); 
}
inline int pybit(int st, int k) 
{ 
	return st << mov[k]; 
}
inline int clrbit(int st, int a, int b) 
{
    return st & (~(3 << mov[a])) & (~(3 << mov[b]));
}
int n, m, gp[20][20];
int DP() 
{
    int ans = INF;
    dp[0].clear();
    dp[0].push(0, 0);
    int now = 0, pre = 1;
    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= n; i++) 
	{
        pre = now, now ^= 1, dp[now].clear();
        for (int k = 0; k < dp[pre].size; k++)
            dp[now].push(dp[pre].sta[k] << 2, dp[pre].sum[k]);
        for (int j = 1; j <= m; j++) 
		{
            pre = now, now ^= 1, dp[now].clear();
            for (int k = 0; k < dp[pre].size; k++) 
			{
                int l = getbit(dp[pre].sta[k], j - 1);
                int up = getbit(dp[pre].sta[k], j);
                int st = clrbit(dp[pre].sta[k], j, j - 1);
                int v = dp[pre].sum[k];
                // printf("%d %d %d %d %d %d
                // %d\n",i,j,l,up,st,dp[pre].sta[k],v);
                if (!l && !up) 
				{
                    if (gp[i][j] == 0 || gp[i][j] == 1)
                        dp[now].push(st, v);
                    if (gp[i][j] == 0 && i < n && gp[i + 1][j] != 1 && j < m &&
                        gp[i][j + 1] != 1) 
					{
                        dp[now].push(st | pybit(1, j - 1) | pybit(1, j), v + 1);
                        dp[now].push(st | pybit(2, j - 1) | pybit(2, j), v + 1);
                    }
                    if (i < n && gp[i + 1][j] != 1 && gp[i][j] >= 2)
                        dp[now].push(st | pybit(gp[i][j] - 1, j - 1), v + 1);
                    if (j < m && gp[i][j + 1] != 1 && gp[i][j] >= 2)
                        dp[now].push(st | pybit(gp[i][j] - 1, j), v + 1);
                } 
				else if (!l || !up) 
				{
                    int e = l + up;
                    if (gp[i][j] == 0) 
					{
                        if (i < n && gp[i + 1][j] != 1)
                            dp[now].push(st | pybit(e, j - 1), v + 1);
                        if (j < m && gp[i][j + 1] != 1)
                            dp[now].push(st | pybit(e, j), v + 1);
                    }
                    if (gp[i][j] == 2 && e == 1) 
					{
                        if (st == 0 && cnt1 >= 1 && cnt2 >= 2) 
						{
                            ans = min(ans, v + 1);
                        }
                        dp[now].push(st, v + 1);
                    }
                    if (gp[i][j] == 3 && e == 2) 
					{
                        if (st == 0 && cnt2 >= 1 && cnt1 >= 2)
                            ans = min(ans, v + 1);
                        dp[now].push(st, v + 1);
                    }
                } 
				else if (l == 1 && up == 1) 
				{
                    if (gp[i][j] >= 2)
                        continue;
                    if (cnt1 >= 2) 
					{
                        if (cnt2 >= 2 && st == 0)
                            ans = min(ans, v + 1);
                    }
                    dp[now].push(st, v + 1);
                } 
				else if (l == 2 && up == 2) 
				{
                    if (gp[i][j] >= 2)
                        continue;
                    if (cnt2 >= 2) 
					{
                        if (cnt1 >= 2 && st == 0)
                            ans = min(ans, v + 1);
                    }
                    dp[now].push(st, v + 1);
                }
            }
            if (gp[i][j] == 2)
                cnt1++;
            else if (gp[i][j] == 3)
                cnt2++;
        }
    }
    if (ans == INF)
        ans = 2;
    return ans;
}
int main() 
{
    while (~scanf("%d%d", &n, &m)) 
	{
        if (n == m && m == 0)
            break;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", &gp[i][j]);
        cout << DP() - 2 << endl;
    }
    return 0;
}