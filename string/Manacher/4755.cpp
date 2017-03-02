#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

const int maxn = 1e5 + 10;
const unsigned int seed = 31;

char sa[maxn << 1];
char sb[maxn << 1];
char a[maxn];
char b[maxn];

void square(char *s, char *t)
{
	t[0] = '^';
	t[1] = '&';
	int len = strlen(s);
	for (int i = 1; i <= len; i++)
		t[i << 1] = s[i - 1],
		t[i << 1 | 1] = '&';
}

int p[maxn];

void manacher()
{
	int len = strlen(sa);
	int mx = 0, id = 0;
	for (int i = 1; i < len; i++)
	{
		if (mx > i)
			p[i] = min(p[(id << 1) - i], mx - i);
		else
			p[i] = 1;
		while (sa[i - p[i]] == sa[i + p[i]])
			++p[i];
		if (mx < p[i] + i)
			mx = p[i] + i, id = i;
		--p[i];
	}
	for (int i = 1; i < len; i++)
		printf("%d ", p[i]);
	puts("");
}

unsigned int hashb[maxn << 1];
unsigned int inva[maxn << 1];

int n;

bool check(int x, int len)
{
	if (x + len )
}

int main()
{
	scanf("%*d%s%s", a, b);
	square(a, sa);
	square(b, sb);
	printf("%s\n%s\n", sa, sb);
	manacher();
	n = strlen(sa);
	int ans = 0;
	hashb[0] = sb[0];
	for (int i = 1; i < n; i++)
		hashb[i] = hashb[i - 1] * seed + (unsigned int)sb[i];
	inva[n - 1] = sa[n - 1];
	for (int i = n - 2; ~i; i--)
		inva[i] = inva[i + 1] * seed + (unsigned int)sa[i];

	for (int i = 0; i < n; i++)
		printf("%u ", hashb[i]);
	puts("");
	for (int i = 0; i < n; i++)
		printf("%u ", inva[i]);
	puts("");

	for (int i = 0; i < n; i++)
	{
		int l = 0, r = n, mid;
		while(l < r)
		{
			mid = l + r >> 1;
			check(i, mid) ? l = mid + 1 : r = mid;
		}
		ans = max(ans, p[i] + mid);
	}
	printf("%d\n", ans + 1);
}
