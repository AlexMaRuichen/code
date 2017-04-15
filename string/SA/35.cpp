#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

const int charset = 26;
const int maxn = 100010;

int n;
char s[maxn];
int sa[maxn];
int Rank[maxn];
int height[maxn];

inline bool equal(int *y, int k, int i, int j)
{
	return y[i] == y[j] && (i + k < n ? y[i + k] : -1) == (j + k < n ? y[j + k] : -1);
}

void Suffix_Array()
{
	int *x = Rank;
	int *y = height;
	static int w[maxn];
	for (int i = 0; i < n; i++)
		++w[s[i] - 'a'];
	for (int i = 1; i < charset; i++)
		w[i] += w[i - 1];
	for (int i = n - 1; ~i; i--)
		sa[--w[s[i] - 'a']] = i;
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
			w[y[x[i]]]++;
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
	if (y != Rank)
		memcpy(x, y, sizeof(Rank));
	for (int i = 0, j = 0; i < n; i++)
	{
		if (j > 0)
			--j;
		if (Rank[i] + 1 == n)
			continue;
		int p = sa[Rank[i] + 1];
		while (i + j < n && p + j < n && s[i + j] == s[p + j])
			++j;
		height[Rank[i]] = j;
	}
}

int main()
{
	n = fread(s, 1, maxn, stdin);
	while (s[n - 1] < 'a')
		--n;
	Suffix_Array();
	for (int i = 0; i < n; i++)
		printf("%d ", sa[i] + 1);
	puts("");
	for (int i = 0; i < n - 1; i++)
		printf("%d ", height[i]);
	puts("");
}