#include <algorithm>
#include <ctype.h>
#include <numeric>
#include <stdio.h>
#include <string.h>
using namespace std;
const int maxn = 200010;
char s[maxn];
int sa[maxn];
void init(int n) 
{
    static int cnt[maxn];
    static int m[2][maxn];
    static int *id = m[0], *oid = m[1];
    for (int i = 1; i <= n; i++)
        ++cnt[s[i]];
    partial_sum(cnt + 1, cnt + 256, cnt + 1);
    for (int i = 1, t = 0; i <= 255; i++)
        if (cnt[i])
            id[i] = ++t;
    for (int i = 1; i <= n; i++)
        oid[i] = id[s[i]], sa[cnt[s[i]]--] = i;
    for (int k = 1, cur = 0; cur ^ n; k <<= 1, swap(id, oid)) 
	{
        memset(cnt, 0, sizeof(int) * (n + 1));
        for (int i = 1; i <= n; i++)
            ++cnt[oid[i]];
        partial_sum(cnt + 1, cnt + n + 1, cnt + 1);
        for (int i = n; i; i--)
            if (sa[i] > k)
                id[sa[i] - k] = cnt[oid[sa[i] - k]]--;
        for (int i = 1; i <= k; i++)
            id[n - i + 1] = cnt[oid[n - i + 1]]--;
        for (int i = 1; i <= n; i++)
            sa[id[i]] = i;
        cur = 0;
        for (int i = 1; i <= n; i++)
            id[sa[i]] = (sa[i] + k > n || sa[i - 1] + k > n ||
                         oid[sa[i]] ^ oid[sa[i - 1]] ||
                         oid[sa[i] + k] ^ oid[sa[i - 1] + k])
                            ? ++cur
                            : cur;
    }
}
int main() 
{
    fread(s + 1, 1, 100000, stdin);
    int n = 0;
    while (isprint(s[++n]))
        ;
    --n;
    for (int i = 1; i <= n; i++)
        s[i + n] = s[i];
    n <<= 1;
    init(n);
    for (int i = 1; i <= n; i++)
        if (sa[i] <= (n >> 1))
            putchar(s[sa[i] + (n >> 1) - 1]);
    puts("");
}
