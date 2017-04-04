#include <stdio.h>

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

const int maxn = 20;
const int inf = 1e9;

char s[maxn][maxn + 10];

int sta[1 << maxn], f[2][1 << maxn];

int solve(int n, int m) 
{
    int mask = (1 << (m << 1)) - 1, tot = 0;
    for (int i = 0; i <= mask; i++) 
	{
        bool flag = true;
        for (int j = 1; j < m; j++)
            if ((i >> (j << 1) & 3) == 3) 
			{
                flag = false;
                break;
            }
        if (flag)
            sta[tot++] = i;
    }
    for (int i = 0; i < tot; i++) 
	{
        int csta = sta[i];
        bool flag = true;
        for (int j = 0; j < m; j++) 
		{
            if (csta & 1) 
			{
                flag = false;
                break;
            }
            csta >>= 2;
        }
        f[0][sta[i]] = flag ? 0 : inf;
    }
    // f[0][0] = 0;
    int c = 0;
    for (int i = 0; i < n; i++) 
	{
        for (int j = 0; j < m; j++) 
		{
            for (int k = 0; k < tot; k++)
                f[c ^ 1][sta[k]] = inf;
            for (int k = 0; k < tot; k++)
                if (f[c][sta[k]] ^ inf) 
				{
                    int csta = sta[k];
                    int left = csta & 3;
                    int up = (csta >> (m - 1 << 1)) & 3;
                    int tmp = (csta ^ (up << (m - 1 << 1)) ^ left) << 2;
                    if (j == 0) 
					{
                        tmp = (csta ^ (up << (m - 1 << 1))) << 2;
                        if (up & 2) 
						{
                            int cur = 1;
                            int to = tmp ^ cur;
                            tense(f[c ^ 1][to], f[c][csta] + 1);
                            to ^= 2;
                            tense(f[c ^ 1][to], f[c][csta] + 1);
                        } else 
						{
                            int cur = ((up & 1) ^ (s[i][j] - '0')) << 1;
                            int to = tmp ^ cur;
                            tense(f[c ^ 1][to], f[c][csta]);
                            to ^= 2;
                            tense(f[c ^ 1][to], f[c][csta] + 2);
                        }
                    } else if (up & 2) 
					{
                        int cur = 1;
                        left ^= 2;
                        if (left & 2) 
						{
                            if (left & 1)
                                left ^= 1;
                        }
                        int to = tmp ^ (left << 2) ^ cur;
                        tense(f[c ^ 1][to], f[c][csta] + 1);
                        to ^= 2;
                        tense(f[c ^ 1][to], f[c][csta] + 1);
                    } else 
					{
                        int cur = ((left & 1) ^ (s[i][j] - '0') ^ (up & 1))
                                  << 1;
                        if (left & 2) 
						{
                            if (left & 1)
                                left ^= 1;
                        }
                        int to = tmp ^ (left << 2) ^ cur;
                        tense(f[c ^ 1][to], f[c][csta]);
                        to ^= 2;
                        tense(f[c ^ 1][to], f[c][csta] + 2);
                    }
                }
            c ^= 1;
            if (j == m - 1) 
			{
                for (int k = 0; k < tot; k++)
                    if (f[c][sta[k]] ^ inf) 
					{
                        int csta = sta[k];
                        if ((csta & 3) == 3) 
						{
                            tense(f[c][csta ^ 1], f[c][csta]);
                            f[c][csta] = inf;
                        }
                    }
            }
        }
    }
    int ans = inf;
    for (int i = 0; i < tot; i++)
        if (f[c][sta[i]] ^ inf) 
		{
            int csta = sta[i];
            bool flag = true;
            for (int j = 0; j < m; j++) 
			{
                if ((csta & 3) >= 2) 
				{
                    flag = false;
                    break;
                }
                csta >>= 2;
            }
            if (flag)
                tense(ans, f[c][sta[i]]);
        }
    return ans;
}

int main() 
{
    int n, m, test = 0;
    while (scanf("%d%d", &n, &m) == 2 && n && m) 
	{
        for (int i = 0; i < n; i++)
            scanf("%s", s[i]);
        printf("Case #%d: %d\n", ++test, solve(n, m));
    }
}