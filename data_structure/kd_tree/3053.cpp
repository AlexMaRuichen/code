#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 5e4 + 10;

int k, s;

struct point
{
	int x[5];
}p[maxn];

bool cmp(const point &a, const point &b)
{
	return a.x[s] < b.x[s];
}

struct kdt
{
	kdt *ls, *rs;
	point p;
	int mn[5], mx[5];
	kdt(){}
	kdt(const point &p);
	int mndis(const point &p);
	void update();
	void* operator new(size_t);
}*root, mem[maxn], *p;

int kdt :: mndis(const point &p)
{
	int ans = 0;
	for (int i = 0; i < k; i++)
	{
		if (mn[i] > p.x[i])
			ans += (p.x[i] - mn[i]) * (p.x[i] - mn[i]);
		if (mx[i] < p.x[i])
			ans += (p.x[i] - mx[i]) * (p.x[i] - mx[i]);
	}
	return ans;
}

kdt :: kdt(const point &p)
{
	this->p = p;
	for (int i = 0; i < k; i++)
		mn[i] = mx[i] = p.x[i];
}

void* kdt :: operator new(size_t)
{
		return p++;
}

void kdt :: update()
{
	if (ls)
		for (int i = 0; i < k; i++)
			mn[i] = min(mn[i], ls->mn[i]),
			mx[i] = max(mx[i], ls->mx[i]);
	if (rs)
		for (int i = 0; i < k; i++)
			mn[i] = min(mn[i], rs->mn[i]),
			mx[i] = max(mx[i], rs->mx[i]);
}

void build(kdt *&x, int l, int r, int dem)
{
	if (l > r)
		return;
	s = dem;
	int mid = l + r >> 1;
	nth_element(p + l, p + mid, p + r + 1, cmp);
	x = new kdt(p[mid]);
	build(x->ls, l, mid - 1, (dem + 1) % k);
	build(x->rs, mid + 1, r, (dem + 1) % k);
	x->update();
}


int main()
{

}