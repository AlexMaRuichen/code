#include <stdio.h>
#include <math.h>

#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 6e4 + 10;

#ifdef ONLINE_JUDGE

const double M_PI = 3.141592653589793238462;

#endif

int n;
vector <int> g[maxn];

struct cp
{
	double x, y;
	cp() {}
	cp(double x, double y) :x(x), y(y) {}
};

cp operator + (const cp &a, const cp &b)
{
	return cp(a.x + b.x, a.y + b.y);
}

cp operator - (const cp &a, const cp &b)
{
	return cp(a.x - b.x, a.y - b.y);
}

cp operator * (const cp &a, const cp &b)
{
	return cp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

void DFT(cp *a, int len, int type)
{
	for (int i = 0, t = 0; i < len; i++)
	{
		if (t < i)
			swap(a[t], a[i]);
		for (int j = len >> 1; (t ^= j) < j; j >>= 1);
	}
	for (int i = 2; i <= len; i <<= 1)
	{
		cp wn(cos(2 * M_PI * type / i), sin(2 * M_PI * type / i));
		for (int j = 0; j < len; j += i)
		{
			cp w(1, 0), t;
			for (int k = 0; k < (i >> 1); k++, w = w * wn)
			{
				t = a[j + k + (i >> 1)] * w;
				a[j + k + (i >> 1)] = a[j + k] - t;
				a[j + k] = a[j + k] + t;
			}
		}
	}
	if (type < 0)
		for (int i = 0; i < len; i++)
			a[i].x /= len;
}

void FFT(cp *a, cp *b, cp *c, int len)
{
	DFT(a, len, 1);
	DFT(b, len, 1);
	for (int i = 0; i < len; i++)
		c[i] = a[i] * b[i];
	DFT(c, len, -1);
}

struct seg
{
	seg *ls, *rs;
	int mx;
	seg() 
	{
		ls = rs = NULL;
		mx = 0;
	}
	void* operator new(size_t);
}*root, mem[maxn << 2], *ptr = mem;

void* seg :: operator new(size_t)
{
	return ptr++;
}

int a[maxn];

void build(seg *&x, int l, int r)
{
	x = new seg();
	if (l == r)
	{
		x->mx = a[l];
		return ;
	}
	int mid = l + r >> 1;
	build(x->ls, l, mid);
	build(x->rs, mid + 1, r);
	x->mx = max(x->ls->mx, x->rs->mx);
}

int query(seg *x, int l, int r, int L, int R)
{
	if (l == L && r == R)
		return x->mx;
	int mid = L + R >> 1;
	if (mid >= r)
		return query(x->ls, l, r, L, mid);
	else if (mid < l)
		return query(x->rs, l, r, mid + 1, R);
	else
		return max(query(x->ls, l, mid, L, mid), query(x->rs, mid + 1, r, mid + 1, R));
}

int ans[maxn];

cp A[1 << 17];
cp B[1 << 17];
cp C[1 << 17];

void solve(int l, int r)
{
	if (l > r)
		return;
	if (l == r)
	{
		++ans[1];
		return;
	}
	int mx = query(root, l, r, 1, n);
	vector <int> p;
	int lft = lower_bound(g[mx].begin(), g[mx].end(), l) - g[mx].begin();
	int rft = upper_bound(g[mx].begin(), g[mx].end(), r) - g[mx].begin() - 1;
	p.push_back(l - 1);
	for (int i = lft; i <= rft; i++)
		p.push_back(g[mx][i]);
	p.push_back(r + 1);
	int len1 = p.size() - 1, len = 1;
	for (; len < (len1 << 1); len <<= 1);
	for (int i = 0; i < len1; i++)
		A[i] = cp(p[i + 1] - p[i], 0);
	for (int i = 0; i < len1; i++)
		B[i] = cp(p[len1 - i] - p[len1 - i - 1], 0);
	for (int i = len1; i < len; i++)
		A[i] = B[i] = cp(0, 0);
	FFT(A, B, C, len);
	for (int i = 0; i < len1 - 1; i++)
		ans[len1 - i - 1] += (int)(C[i].x + 0.5);
	for (int i = 0; i < p.size() - 1; i++)
		solve(p[i] + 1, p[i + 1] - 1);
}

int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
	{
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            g[i].clear(), ans[i]=0;
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]), g[a[i]].push_back(i);
		ptr = mem;
		build(root, 1, n);
        solve(1, n);
        long long f=0;
        for(int i = 1; i <= n; i++)
            f += (i ^ ans[i]);
        printf("%lld\n", f);
    }
}
