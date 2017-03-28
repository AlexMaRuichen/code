#include <stdio.h>

#include <algorithm>
#include <map>

using namespace std;

typedef long long LL;

const int maxn = 3e5 + 10;

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, 1 : 0;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return b > a ? a = b, 1 : 0;
}

struct data
{
	int val, pos;
	data() :val(0), pos(0) {}
	data(int val, int pos) :val(val), pos(pos) {} 

};

bool operator < (const data &x, const data &y)
{
	if (x.val == y.val) 
		return x.pos > y.pos;
	return x.val < y.val;
}

bool operator > (const data &x, const data &y)
{
	if (x.val == y.val) 
		return x.pos < y.pos;
	return x.val > y.val;
}

data fu[maxn];
data fd[maxn];

int n;
int up[maxn], down[maxn], both[maxn];
int posu[maxn], posd[maxn], posb[maxn];

map <LL, int> m;

void get(int *a, int *pos)
{
	m.clear();
	m[0] = n;
	LL sum = 0;
	pos[n] = n + 1;
	for (int i = n - 1; ~i; i--)
	{
		sum += a[i];
		pos[i] = pos[i + 1];
		if (m.count(sum)) 
			tense(pos[i], m[sum]);
		m[sum] = i;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) 
		scanf("%d", &up[i]);
	for (int i = 0; i < n; i++) 
		scanf("%d", &down[i]);
	for (int i = 0; i < n; i++) 
		both[i] = up[i] + down[i];
	get(up, posu);
	get(down, posd);
	get(both, posb);
	for (int i = 0; i <= n; i++)
	{
		relax(fd[posd[fu[i].pos]], data(fu[i].val + 1, i));
		relax(fu[posu[fd[i].pos]], data(fd[i].val + 1, i));
		relax(fu[posu[i]], data(fu[i].val + 1, fu[i].pos));
		relax(fd[posd[i]], data(fd[i].val + 1, fd[i].pos));

		relax(fu[i + 1], fu[i]);
		relax(fd[i + 1], fd[i]);

		data tmp = data(max(fu[i].val, fd[i].val) + 1, posb[i]);
		relax(fd[posb[i]], tmp);
	}
	printf("%d\n", max(fu[n].val, fd[n].val));
}
