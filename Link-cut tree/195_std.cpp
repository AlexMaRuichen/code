#include <bits/stdc++.h>
#define isrt(x) (c[fa[x]][0] != x && c[fa[x]][1] != x)
#define maintain(x) sum[x] = sum[c[x][0]] + sum[c[x][1]] + num[x]
#define ins(x) num[n + 1] = sum[++n] = x;
#define N 200005
using namespace std;

int n, m, tot, now, cnt, pt, fa[N], b[N], c[N][2], ans[N], lf[N], rg[N], num[N],
    sum[N];
int read() 
{
    int x = 0;
    char cr = getchar();
    while (cr < '0' || cr > '9')
        cr = getchar();
    while (cr >= '0' && cr <= '9') 
	{
        x = x * 10 + cr - '0';
        cr = getchar();
    }
    return x;
}
struct node 
{
    int pos, op, x, y;
} a[N << 2];
bool cmp(node u, node v) 
{
    return u.pos < v.pos || u.pos == v.pos && u.op < v.op;
}
void rot(int x) 
{
    int y = fa[x], z = fa[y], l = (c[y][1] == x), r = l ^ 1;
    if (!isrt(y))
        c[z][c[z][1] == y] = x;
    fa[x] = z;
    fa[y] = x;
    fa[c[x][r]] = y;
    c[y][l] = c[x][r];
    c[x][r] = y;
    maintain(y);
}
void splay(int x) 
{
    int y, z;
    for (; !isrt(x); rot(x)) 
	{
        y = fa[x];
        z = fa[y];
        if (!isrt(y))
            rot((c[z][0] == y ^ c[y][0] == x) ? x : y);
    }
    maintain(x);
}
int acss(int x) 
{
    int y = 0;
    for (; x; y = x, x = fa[x]) 
	{
        splay(x);
        c[x][1] = y;
        maintain(x);
    }
    return y;
}
void cut(int x) 
{
    acss(x);
    splay(x);
    c[x][0] = fa[c[x][0]] = 0;
    maintain(x);
}
void link(int x, int y) 
{
    splay(x);
    fa[x] = y;
}
int main() 
{
    pt = read();
    m = read();
    ins(1);
    b[cnt = 1] = lf[1] = 1;
    rg[1] = pt;
    ins(0);
    now = 2;
    link(2, 1);
    int i, k, op, x, y;
    for (i = 1; i <= m; i++) 
	{
        op = read();
        if (!op) 
		{
            lf[++cnt] = read();
            rg[cnt] = read();
            ins(1);
            b[cnt] = n;
            a[++tot] = (node){1, i - m, n, now};
        } 
		else if (op == 1) 
		{
            x = read();
            y = read();
            k = read();
            x = max(x, lf[k]);
            y = min(y, rg[k]);
            if (x <= y) 
			{
                ins(0);
                if (x > 1)
                    link(n, now);
                a[++tot] = (node){x, i - m, n, b[k]};
                a[++tot] = (node){y + 1, i - m, n, now};
                now = n;
            }
        } 
		else 
		{
            k = read();
            x = read();
            y = read();
            a[++tot] = (node){k, i, b[x], b[y]};
        }
    }
	sort(a + 1, a + tot + 1, cmp);
	for (int i = 1; i <= tot; i++)
		printf("%d %d %d %d\n", a[i].pos, a[i].pos, a[i].x, a[i].y);    
    memset(ans, -1, sizeof(ans));
    for (i = k = 1; i <= pt; i++)
        for (; k <= tot && a[k].pos == i; k++)
            if (a[k].op > 0) 
			{
                acss(a[k].x);
                splay(a[k].x);
                ans[a[k].op] = sum[a[k].x];
                x = acss(a[k].y);
                splay(a[k].y);
                ans[a[k].op] += sum[a[k].y];
				printf("%d\n", x);
                acss(x);
                splay(x);
                ans[a[k].op] -= sum[x] << 1;
            } 
			
			else 
			{
                cut(a[k].x);
                link(a[k].x, a[k].y);
            }
    for (i = 1; i <= m; i++)
        if (ans[i] != -1)
            printf("%d\n", ans[i]);
    return 0;
}