#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 100010;
struct data
{
	int s[6];
	int id;
}d[maxn << 1];

int id[maxn << 1];
int x[10];

int mr(int *s)
{
	int i, j, k, t;
	for(i = 1, j = 2, k = 0; i <= 6 && j <= 6 && k <= 6; )
	{
		t = s[i + k > 6 ? i + k - 6 : i + k] - s[j + k > 6 ? j + k - 6 : j + k];
		if (!t)
			++k;
		else
		{
			t > 0 ? i += k + 1 : j += k + 1;
			i == j ? ++j , k = 0: k = 0;
		}
	}
	return min(i, j);
}

bool cmp(int x, int y)
{
	return d[x].s[0] ^ d[y].s[0] ?
		   d[x].s[0] < d[y].s[0] :
		   d[x].s[1] ^ d[y].s[1] ?
		   d[x].s[1] < d[y].s[1] :
		   d[x].s[2] ^ d[y].s[2] ?
		   d[x].s[2] < d[y].s[2] :
		   d[x].s[3] ^ d[y].s[3] ?
		   d[x].s[3] < d[y].s[3] :
		   d[x].s[4] ^ d[y].s[4] ?
		   d[x].s[4] < d[y].s[4] :
		   d[x].s[5] < d[y].s[5] ;
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1, start; i <= n; i++)
	{
		for (int j = 1; j <= 6; j++)
			scanf("%d", &x[j]);
		start = mr(x);
		for (int j = 0; j < 6; j++)
			d[i].s[j] = x[start + j > 6 ? start + j - 6 : start + j];
		reverse(x + 1, x + 6 + 1);
		start = mr(x);
		for (int j = 0; j < 6; j++)
			d[i + n].s[j] = x[start + j > 6 ? start + j - 6 : start + j];
		d[i].id = d[i + n].id = i;
	}
	for (int i = 1; i <= (n << 1); i++)
		id[i] = i;
	sort(id + 1, id + (n << 1) + 1, cmp);
	for (int i = 2; i <= (n << 1); i++)
	{
		if (d[id[i]].id == d[id[i - 1]].id)
			continue;
		for (int j = 0; j < 6; j++)
			if (d[id[i]].s[j] ^ d[id[i - 1]].s[j])
				goto lableA;
		return puts("Twin snowflakes found.");
		lableA:;
	}
	puts("No two snowflakes are alike.");
}