#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <numeric>

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

using namespace std;

const int maxn = 400010;

struct data
{
	int dig, id;
}d[maxn];

bool operator < (const data &a, const data &b)
{
	return a.dig ^ b.dig ? a.dig < b.dig : a.id < b.id;
}

int a[maxn];
int s[maxn];
int sa[maxn];
int cnt[maxn];
int m[2][maxn];
int *id, *oid;

void Suffix_Array(int n, int charset)
{
	id = m[0];
	oid = m[1];
	memset(sa, 0, sizeof(sa));
	memset(cnt, 0, sizeof(cnt));
	memset(m, 0, sizeof(m));
	for (int i = 1; i <= n; i++)
		++cnt[s[i]];
	partial_sum(cnt + 1, cnt + charset + 1, cnt + 1);
	for (int i = 1, t = 0; i <= charset; i++)
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
		for (int i = 1; i <= n; i++)
			id[n - i + 1] = cnt[oid[n - i + 1]]--;
		for (int i = 1; i <= n; i++)
			sa[id[i]] = i;
		cur = 0;
		for (int i = 1; i <= n; i++)
			id[sa[i]] = (sa[i] + k > n || sa[i - 1] + k > n ||
						 oid[sa[i]] ^ oid[sa[i - 1]] ||
						 oid[sa[i] + k] ^ oid[sa[i - 1] + k]) ?
						 ++cur : 
						 cur;
	}
}

int main()
{
	int n, nn;
	scanf("%d", &n);
	nn = n;
	for (int i = 1; i <= n; i++)
		scanf("%d", &d[i].dig), d[i].id = i;
	sort(d + 1, d + n + 1);
	for (int i = 1; i <= n; i++)
        s[d[i].id] = (i ^ 1 && d[i].dig == d[i - 1].dig) ? s[d[i - 1].id] : i;
	reverse(s + 1, s + n + 1);
	Suffix_Array(n, nn);
	int id = 1;
	for (int i = 1; i <= n; i++)
		printf("%d ", d[s[i]].dig);
	puts("");
	while (sa[id] <= 2 && id <= n)
		++id;
	for (int i = sa[id]; i <= n; i++)
		printf("%d\n", d[s[i]].dig);
	puts("");
	n = sa[id] - 1;
	for (int i = 1; i <= n; i++)
		s[i + n] = s[i];
	for (int i = 1; i <= (n << 1); i++)
		printf("%d ", d[s[i]].dig);
	puts("");
	s[n << 1 | 1] = 0;
	Suffix_Array(n << 1, nn);
	id = 1;
	while (sa[id] <= 1 || sa[id] > n)
		++id;
	for (int i = sa[id]; i <= n; i++)
		printf("%d\n", d[s[i]].dig);
	puts("");
	for (int i = 1; i < sa[id]; i++)
		printf("%d\n", d[s[i]].dig);
	puts("");
}
