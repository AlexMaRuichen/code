#include <stdio.h>

#include <algorithm>

using namespace std;

typedef unsigned int uint;

const int maxn = 200010;

inline uint RAND()
{
	static uint seed = 998244353, a = 31;
	seed *= a;
	return seed;
}

struct Treap
{
	Treap *ls, *rs;
	int val;
	uint key;
	Treap() {}
	Treap(Treap *ls, Treap *rs, int val) :ls(ls), rs(rs), val(val), key(RAND()) {}
	void* operator new(size_t);
}*root, mem[maxn * 20];

int cnt;

void* Treap :: operator new(size_t)
{
	static Treap *p = mem;
	++cnt;
	return p++;
}

Treap* split_l(Treap *x, int y)
{
	return !x ? NULL : (x->val < y ? new Treap(x->ls, split_l(x->rs, y), x->val) : split_l(x->ls, y));
}

Treap * split_r(Treap *x, int y)
{
	return !x ? NULL : (x->val < y ? split_r(x->rs, y) :  new Treap(split_r(x->ls, y), x->rs, x->val));
}

Treap* merge(Treap *x, Treap *y)
{
	return (!x || !y) ? 
		   (x ? x : y) : 
		   (x->key < y->key ? new Treap(x->ls, merge(x->rs, y), x->val) : new Treap(merge(x, y->ls), y->rs, y->val)); 
}

Treap* insert(Treap *x, int y, uint w)
{
	return (!x || x->key > w) ?
		   (new Treap(split_l(x, y), split_r(x, y), y)) :
		   (y < x->val ? new Treap(insert(x->ls, y, w), x->rs, x->val) : new Treap(x->ls, insert(x->rs, y, w), x->val));
}

void print(Treap *x)
{
	if (!x)
		return;
	print(x->ls);
	printf("%d\n", x->val);
	print(x->rs);
}

int main()
{
	freopen("tt.in", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 1, x; i <= n; i++)
	{
		scanf("%d", &x);
		root = insert(root, x, RAND());
	}
	print(root);
}