#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 1e5 + 10;
const int mod = 998244353;

int n, m;

int mul(int x, int y)
{
	int ans = 1;
	while (y)
	{
		if (y & 1)
			ans = ans * 1ll * x % mod;
		x = x * 1ll * x % mod;
		y >>= 1;
	}
	return ans;
}

inline int merge(int x, int y)
{
	return (x * 1ll * (mod + 1 - y) + y * 1ll * (mod + 1 - x)) % mod;
}

struct seg
{
	int ls, rs;
	int val;
}mem[maxn * 500];

int tot;
int root[maxn << 2];

void insert(int &x, int v, int l, int r, int L, int R)
{
	if (!x)
		x = ++tot;
	if (l == L && r == R)
	{
		mem[x].val = merge(mem[x].val, v);
		return;
	}
	int mid = L + R >> 1;
	if (mid >= r)
		insert(mem[x].ls, v, l, r, L ,mid);
	else if (mid < l)
		insert(mem[x].rs, v, l, r, mid + 1, R);
	else
		insert(mem[x].ls, v, l, mid, L, mid),
		insert(mem[x].rs, v, mid + 1, r, mid + 1, R);
}

int query(int x, int p, int l, int r)
{
	if (!x)
		return 0;
	if (l == r)
		return mem[x].val;
	int mid = l + r >> 1;
	if (mid >= p)
		return merge(query(mem[x].ls, p, l, mid), mem[x].val);
	else
		return merge(query(mem[x].rs, p, mid + 1, r), mem[x].val);
}

void insert(int x, int v, int lL, int rR, int l, int r, int L, int R)
{
	if (l == L && r == R)
	{
		insert(root[x], v, lL, rR, 0, n);
		return ;
	}
	int mid = L + R >> 1;
	if (mid >= r)
		insert(x << 1, v, lL, rR, l, r, L, mid);
	else if (mid < l)
		insert(x << 1 | 1, v, lL, rR, l, r, mid + 1, R);
	else
		insert(x << 1, v, lL, rR, l, mid, L, mid),
		insert(x << 1 | 1, v, lL, rR, mid + 1, r, mid + 1, R);
}

int query(int x, int p, int v, int l, int r)
{
	int ans = query(root[x], v, 0, n);
	if (l == r)	
		return ans;
	int mid = l + r >> 1;
	if (mid >= p)
		return merge(query(x << 1, p, v, l, mid), ans);
	else	
		return merge(query(x << 1 | 1, p, v, mid + 1, r), ans);
}

int main()
{
	scanf("%d%d", &n, &m);
	++n;
	while (m--)
	{
		static int opt, l, r, inv, cur;  
		scanf("%d%d%d", &opt, &l, &r);
		inv = mul(r - l + 1, mod - 2);
        if(opt == 1)  
        {  
            insert(1, 2 * 1ll * inv % mod, l, r, l, r, 0, n);  
            insert(1, inv, l, r, 0, l - 1, 0, n);  
            insert(1, inv, r + 1, n, l, r, 0, n);  
            ++cur;  
        }  
        else  
        {  
            if(l == 1 && (cur & 1)) 
				printf("%d\n", query(1, 0, r, 0, n) );  
            else 
				printf("%d\n", (mod + 1 - query(1, l - 1, r, 0, n)) % mod );  
        }
	}
}
