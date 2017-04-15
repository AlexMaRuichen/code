#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

const int maxn = 2000010;

struct node 
{
    int id;
    int dig;
} d[maxn];

bool cmp1(const node &a, const node &b) 
{
    return a.dig ^ b.dig ? a.dig < b.dig : a.id < b.id;
}

int wa[maxn], wb[maxn], wv[maxn], ws[maxn];

inline int cmp(int *r, int a, int b, int l) 
{
    return r[a] == r[b] && r[a + l] == r[b + l];
}

void da(int *r, int *sa, int n, int m) 
{
    int i, j, p, *x = wa, *y = wb, *t;
    for (i = 0; i < m; i++)
        ws[i] = 0;
    for (i = 0; i < n; i++)
        ws[x[i] = r[i]]++;
    for (i = 1; i < m; i++)
        ws[i] += ws[i - 1];
    for (i = n - 1; i >= 0; i--)
        sa[--ws[x[i]]] = i;
    for (j = 1, p = 1; p < n; j *= 2, m = p) 
	{
        for (p = 0, i = n - j; i < n; i++)
            y[p++] = i;
        for (i = 0; i < n; i++)
            if (sa[i] >= j)
                y[p++] = sa[i] - j;
        for (i = 0; i < n; i++)
            wv[i] = x[y[i]];
        for (i = 0; i < m; i++)
            ws[i] = 0;
        for (i = 0; i < n; i++)
            ws[wv[i]]++;
        for (i = 1; i < m; i++)
            ws[i] += ws[i - 1];
        for (i = n - 1; i >= 0; i--)
            sa[--ws[wv[i]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i], sa[i - 1], j) ? p - 1 : p++;
    }
}

int r[maxn], sa[maxn];

int main() 
{
    int n, i, j;
    scanf("%d", &n);
    for (i = n - 1; i >= 0; i--) 
	{
        scanf("%d", &d[i].dig);
        d[i].id = i;
    }
    sort(d, d + n, cmp1);
    int num = 1;
    for (i = 0; i < n; i++) 
	{
        if (i && d[i].dig == d[i - 1].dig) 
		{
            r[d[i].id] = r[d[i - 1].id];
            continue;
        }
        r[d[i].id] = i + 1;
    }
    r[n] = 0;
    da(r, sa, n + 1, n + 10);
    for (i = 1; i <= n && sa[i] <= 1; i++)
        ;
    int tmp = sa[i];
    for (j = tmp; j < n; j++)
        printf("%d\n", d[r[j] - 1].dig);
    for (j = 0; j < tmp; j++)
        r[tmp + j] = r[j];
    tmp *= 2;
    r[tmp] = 0;
    da(r, sa, tmp + 1, n + 10);
    for (i = 1; i < tmp && (!sa[i] || sa[i] >= tmp / 2); i++)
        ;
    int k = sa[i];
    for (j = k; j < tmp / 2; j++)
        printf("%d\n", d[r[j] - 1].dig);
    for (i = 0; i < k; i++)
        printf("%d\n", d[r[i] - 1].dig);
    return 0;
}
