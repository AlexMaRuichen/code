#include <stdio.h>
#include <string.h>


#include <algorithm>
#include <stack>

#define inv(x) x & 1 ? x ^ 1 : x | 1

using namespace std;

const int maxn = 210;
const int maxm = 2010;
int n, m;
char ch;
bool flag;

int to[maxm];
int next[maxm];
int head[maxn];
int tot;
int belong[maxn];
int scc;
int cnt;
int dfn[maxn];
int low[maxn];
bool v[maxn];
bool ins[maxn];
stack<int> s;
inline void dfs(int x) 
{
    v[x] = ins[x] = true;
    dfn[x] = low[x] = ++cnt;
    s.push(x);
    for (int i = head[x]; i; i = next[i])
        if (!v[to[i]])
            dfs(to[i]), low[x] = min(low[to[i]], low[x]);
        else if (ins[to[i]])
            low[x] = min(dfn[to[i]], low[x]);
    if (low[x] == dfn[x]) 
	{
        int now = 0;
        ++scc;
        while (now ^ x) 
		{
            now = s.top();
            s.pop();
            ins[now] = false;
            belong[now] = scc;
        }
    }
}
int main() 
{
    int T, i;
    scanf("%d", &T);
    while (T--) 
	{
        scanf("%d%d", &n, &m);
        memset(head, 0, sizeof(int) * ((n << 1) + 5));
        memset(v, 0, sizeof(bool) * ((n << 1) + 5));
        tot = 0;
        scc = 0;
        cnt = 0;
        for (i = 1; i <= m; i++) 
		{
            static int x, y;
            x = 0;
            ch = getchar();
            while (ch != 'm' && ch != 'h')
                ch = getchar();
            flag = ch == 'm';
            ch = getchar();
            while (ch >= '0' && ch <= '9')
                x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
            x = flag ? x << 1 : x << 1 | 1;

            y = 0;
            ch = getchar();
            while (ch != 'm' && ch != 'h')
                ch = getchar();
            flag = ch == 'm';
            ch = getchar();
            while (ch >= '0' && ch <= '9')
                y = (y << 1) + (y << 3) + ch - '0', ch = getchar();
            y = flag ? y << 1 : y << 1 | 1;

            to[++tot] = inv(y);
            next[tot] = head[x];
            head[x] = tot;

            to[++tot] = inv(x);
            next[tot] = head[y];
            head[y] = tot;
        }
        for (i = 2; i <= (n << 1 | 1); i++)
            if (!v[i])
                dfs(i);
        for (i = 1; i <= n; i++)
            if (belong[i << 1] == belong[i << 1 | 1]) 
			{
                puts("BAD");
                goto lableA;
            }
        puts("GOOD");
    lableA:;
    }
}