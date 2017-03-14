#include <bits/stdc++.h>
template <class T> inline void read(T *a) 
{
    char c;
    while (isspace(c = getchar())) ;
    bool flag = 0;
    if (c == '-')
        flag = 1, *a = 0;
    else
        *a = c - 48;
    while (isdigit(c = getchar()))
        *a = *a * 10 + c - 48;
    if (flag)
        *a = -*a;
}
using namespace std;
#define MAXN 505
vector<int> g[MAXN];
bool v[MAXN];
int tmp_match[MAXN], p[MAXN], match[MAXN], n;
void dodo(int k) 
{
    int m = g[k].size();
    if (m <= 1)
        return;
    for (int i = 1; i <= 5; ++i)
    	swap(g[k][rand() % m], g[k][rand() % m]);
}
bool dfs(int x) 
{
        v[x] = 1;
    dodo(x);
    for (size_t i = 0; i < g[x].size(); ++i) 
    {
        int y = g[x][i];
        if (v[y])
            continue;
        v[y] = 1;
        if (!tmp_match[y] || dfs(tmp_match[y])) 
		{
            tmp_match[y] = x;
            tmp_match[x] = y;
            return 1;
        }
    }
    return 0;
}
int m, a, b, M;
inline int random_match() 
{
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        p[i] = i;
    int xxxx = 2;
    for (int t1 = 0; t1 < xxxx; ++t1) 
    {
        random_shuffle(p + 1, p + 1 + n);
        memset(tmp_match + 1, 0, sizeof(int) * n);
        int tmp = 0;
        for (int i = 1; i <= n; ++i)
            dodo(i);
        for (int i = 1; i <= n; ++i)
            if (!tmp_match[p[i]])
                for (int t2 = 0; t2 < 40; ++t2) 
				{
                    memset(v + 1, 0, sizeof(bool) * n);
                    if (dfs(p[i])) 
		    		{
                        tmp++;
                        break;
                    }
                }
        if (tmp > ans)
		{
            ans = tmp;
            for (int i = 1; i <= n; ++i)
                match[i] = tmp_match[i];
        }
    }
    return ans;
}
int main() 
{

    scanf("%d%d", &n, &m);
    srand(time(0));
    M = m;
    while (m--) 
    {
        read(&a);
        read(&b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    printf("%d\n", random_match());
    for (int i = 1; i <= n; ++i)
        printf("%d ", match[i]);
    return 0;
}