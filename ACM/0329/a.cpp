#include <stdio.h>

#include <algorithm>

using namespace std;

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

const int maxn = 2e5 + 10;

struct seg
{
	seg *ls, *rs;
	int val, lazy;
	void pushdown();
	void update();
	void* operator new(size_t);
}*root, mem[maxn <<2], *p;

void* seg :: operator new(size_t)
{
	p->ls = p->rs = NULL;
	p->val = p->lazy = 0;
	return p++;
}

int a[maxn];
int b[maxn];

void seg :: update()
{
	val = max(ls->val, rs->val);
}

void seg :: pushdown()
{
	if (lazy)
	{
		ls->val += lazy;
		rs->val += lazy;
		ls->lazy += lazy;
		rs->lazy += lazy;
		lazy = 0;
	}
}

void build(seg *&x, int l, int r)
{
	x = new seg();
	if (l == r)
	{
		x->val = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(x->ls, l, mid);
	build(x->rs, mid + 1, r);
	x->update();
}

void modify(seg *x, int v, int l, int r, int L, int R)
{
	if (l == L && r == R)
	{
		x->val += v;
		x->lazy += v;
		return ;
	}
	x->pushdown();
	int mid = L + R >> 1;
	if (mid >= r)
		modify(x->ls, v, l, r, L, mid);
	else if (mid < l)
		modify(x->rs, v, l, r, mid + 1, R);
	else
		modify(x->ls, v, l, mid, L, mid),
		modify(x->rs, v, mid + 1, r, mid + 1, R);
	x->update();
}

int query(seg *x, int l, int r, int L, int R)
{
	if (l == L && r == R)
		return x->val;
	x->pushdown();
	int mid = L + R >> 1;
	if (mid >= r)
		return query(x->ls, l, r, L, mid);
	else if (mid < l)
		return query(x->rs, l, r, mid + 1, R);
	else
		return max(query(x->ls, l, mid, L, mid), query(x->rs, mid + 1, r, mid + 1, R));
}

int main()
{
	int T, n, m, k;
	scanf("%d", &T);
	while (T--)
	{
		p = mem;
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 1; i <= n; i++)
			scanf("%d", &b[i]);
		int sum = 0;
		for (int i = 1; i <= k; i++)
			sum += b[i];
		a[1] = sum;
		for (int i = 2; i + k - 1 <= n; i++)
		{
			sum += b[i + k - 1] - b[i - 1];
			a[i] = sum;
		}
		n -= k - 1;
		build(root, 1, n);
		while (m--)
		{
			static int opt, x, y;
			scanf("%d%d%d", &opt, &x, &y);
			if (opt == 0)
			{
				modify(root, y - b[x], max(x - k + 1, 1), min(x, n), 1, n);
				b[x] = y;
			}
			else if (opt == 1)
			{
				modify(root, b[y] - b[x], max(x - k + 1, 1), min(x, n), 1, n);
				modify(root, b[x] - b[y], max(y - k + 1, 1), min(y, n), 1, n);
				swap(b[x], b[y]);
			}
			else 
				printf("%d\n", query(root, x, max(y - k + 1, 1), 1, n));
		}
	}
}