#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <algorithm>

using namespace std;

const int maxn = 200010;
const int len = 100000;
const int charset = 256;

int n;
char s[maxn];
int Rank[maxn];
int height[maxn];
int sa[maxn];

bool equal(int *y, int k, int i, int j)
{
	return y[i] == y[j] && (i + k < n ? y[i + k] : -1) == (j + k < n ? y[j + k] : -1);
}

void Suffix_Array()
{
	int *x = Rank;
	int *y = height;
	static int w[maxn];
	for (int i = 0; i < n; i++)
		++w[s[i]];
	for (int i = 1; i < charset; i++)
		w[i] += w[i - 1];
	for (int i = n - 1; ~i; i--)
		sa[--w[s[i]]] = i;
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (!i || s[sa[i]] ^ s[sa[i - 1]])
			++cnt;
		y[sa[i]] = cnt - 1;
	}
	for (int k = 1; cnt < n; k <<= 1, swap(x, y))
	{
		int len = 0;
		for (int i = n - k; i < n; i++)
			x[len++] = i;
		for (int i = 0; i < n; i++)
			if (sa[i] >= k)
				x[len++] = sa[i] - k;
		memset(w, 0, sizeof(int) * cnt);
		for (int i = 0; i < n; i++)
			++w[y[x[i]]];
		for (int i = 1; i < cnt; i++)
			w[i] += w[i - 1];
		for (int i = n - 1; ~i; i--)
			sa[--w[y[x[i]]]] = x[i];
		cnt = 0;
		for (int i = 0; i < n; i++)
		{
			if (i == 0 || !equal(y, k, sa[i], sa[i - 1]))
				++cnt;
			x[sa[i]] = cnt - 1;
		}
	}
}

int main()
{
	n = fread(s, 1, len, stdin);
	while (!isprint(s[n - 1]))
		--n;
	memcpy(s + n, s, sizeof(char) * n);
	n <<= 1;
//	printf("%s %d\n", s, n);
	Suffix_Array();
/*	for (int i = 0; i < n; i++)
		printf("%d ", sa[i]);
	puts("");*/
	for (int i = 0; i < n; i++)
		if (sa[i] < (n >> 1))
			putchar(s[sa[i] + (n >> 1) - 1]);
	putchar('\n');
}