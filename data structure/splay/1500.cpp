#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
const int inf = ~0u >> 2;
const int maxn = 5e5 + 10;
const int end = 5e5;
int n, m;

template <typename T> inline T& relax(T &a, const T &b)
{
	return (a < b ? a = b : 1), a;
}

inline char getc()
{
	static const int len = 1 << 15;
	static char buf[len], *s, *t;
	if (s == t)
	
	{
		t = (s = buf) + fread(buf, 1, len, stdin);
		if (s == t)
			return EOF;
	}
	return *s++;
}

inline void read(register int &x)
{
	bool flag = false;
	char ch = getc();
	x=0;
	while(ch < '0' || ch > '9')
	
	{
		if(ch == '-')
			flag = true;
		ch = getc();
	}
	while(ch >= '0' && ch <= '9')
		x = (x << 1) + (x << 3) + ch - '0', ch = getc();
	x = flag ? -x : x;
}

inline void read(char *s)
{
	char ch = getc();
	while (ch < 'A' || ch > 'Z')
		ch = getc();
	while ((ch >= 'A' && ch <= 'Z') || ch == '-')
		*s++ = ch, ch = getc();
	*s = 0;
}

struct Splay 
{
    Splay *ls, *rs, *fa;
    int size, val;
    bool rev;
    int change;
    int lmx, rmx, sum, mx;
    Splay();
    Splay(int x);
    void update();
    void push_down();
    void reverse();
    void same(int x);
    void *operator new(size_t);
    void del();
};

struct queue 
{
    Splay *a[maxn];
    int l, r;
    queue() 
	{ 
		l = 1, r = 0; 
	}
    bool empty() 
	{ 
		return l > r; 
	}
    Splay *front() 
	{ 
		return a[(l++ - 1) % end + 1]; 
	}
    void push(Splay *x) 
	{ 
		a[(++r - 1) % end + 1] = x; 
	}
} q;

Splay *null = new Splay, *root = null, Tdata[maxn];

Splay::Splay() 
{
    fa = ls = rs = this;
    size = 0;
    val = lmx = rmx = mx = -inf;
    sum = 0;
}

void *Splay::operator new(size_t) 
{
    static Splay *p = Tdata;
    if (!q.empty())
        return q.front();
    else
        return p++;
}

void Splay::del() 
{
    if (this == null)
        return;
    ls->del();
    rs->del();
    q.push(this);
}

Splay::Splay(int x) 
{
    fa = ls = rs = null;
    val = lmx = rmx = mx = sum = x;
    size = 1;
    rev = false;
    change = inf;
}

void Splay::update() 
{
    size = ls->size + rs->size + 1;
    mx = lmx = rmx = sum = val;
	relax(relax(mx, ls->mx), ls->rmx + lmx);
    lmx = max(ls->lmx, ls->sum + lmx);
	relax(rmx, sum + ls->rmx);
    sum += ls->sum;
	relax(relax(mx, rs->mx), rmx + rs->lmx);
	relax(lmx, sum + rs->lmx);
    rmx = max(rs->rmx, rs->sum + rmx);
    sum += rs->sum;
}

void Splay::push_down() 
{
    if (change ^ inf) 
	{
        ls->same(change);
        rs->same(change);
        change = inf;
    }
    if (rev) 
	{
        ls->reverse();
        rs->reverse();
        rev = 0;
    }
}

void Splay::reverse() 
{
    swap(ls, rs);
    swap(lmx, rmx);
    rev ^= 1;
}

void Splay::same(int x) 
{
    sum = size * x;
    val = change = x;
    if (x > 0)
        lmx = rmx = mx = size * x;
    else
        lmx = rmx = mx = x;
}

void zig(Splay *x) 
{
    Splay *y = x->fa;
    y->push_down();
    x->push_down();
    y->ls = x->rs;
    x->rs->fa = y;
    x->rs = y;
    x->fa = y->fa;
    if (y == y->fa->ls)
        y->fa->ls = x;
    else if (y == y->fa->rs)
        y->fa->rs = x;
    y->fa = x;
    y->update();
    if (root == y)
        root = x;
}

void zag(Splay *x) 
{
    Splay *y = x->fa;
    y->push_down();
    x->push_down();
    y->rs = x->ls;
    x->ls->fa = y;
    x->ls = y;
    x->fa = y->fa;
    if (y == y->fa->ls)
        y->fa->ls = x;
    else if (y == y->fa->rs)
        y->fa->rs = x;
    y->fa = x;
    y->update();
    if (root == y)
        root = x;
}

void splay(Splay *x, Splay *t) 
{
    Splay *y, *z;
    x->push_down();
    while (true) 
	{
        y = x->fa;
        z = y->fa;
        if (y == t)
            break;
        else if (z == t) 
		{
            if (x == y->ls)
                zig(x);
            else
                zag(x);
            break;
        } else if (x == y->ls) 
		{
            if (y == z->ls)
                zig(y);
            zig(x);
        } else 
		{
            if (y == z->rs)
                zag(y);
            zag(x);
        }
    }
    x->update();
}

void find(Splay *x, int y, Splay *z) 
{
    while (true) 
	{
        x->push_down();
        if (y <= x->ls->size)
            x = x->ls;
        else 
		{
            y -= x->ls->size;
            if (y == 1)
                break;
            --y;
            x = x->rs;
        }
    }
    x->push_down();
    splay(x, z);
}

int a[maxn];

Splay *build(int l, int r) 
{
    if (l > r)
        return null;
    int mid = l + r >> 1;
    Splay *x = new Splay(a[mid]);
    x->ls = build(l, mid - 1);
    x->rs = build(mid + 1, r);
    x->ls->fa = x->rs->fa = x;
    x->update();
    return x;
}

int pos, tot, c;

void insert() 
{
    read(pos);
    read(tot);
    for (int i = 1; i <= tot; i++)
        read(a[i]);
    find(root, pos + 1, null);
    find(root, pos + 2, root);
    root->rs->ls = build(1, tot);
    root->rs->ls->fa = root->rs;
    root->rs->update();
    root->update();
}

void del() 
{
    read(pos);
    read(tot);
    find(root, pos, null);
    find(root, pos + tot + 1, root);
    root->rs->ls->del();
    root->rs->ls = null;
    root->rs->update();
    root->update();
}

void make_same() 
{
    read(pos);
    read(tot);
    read(c);
    find(root, pos, null);
    find(root, pos + tot + 1, root);
    root->rs->ls->same(c);
    root->rs->ls->push_down();
    root->rs->update();
    root->update();
}

void reverse() 
{
    read(pos);
    read(tot);
    find(root, pos, null);
    find(root, pos + tot + 1, root);
    root->rs->ls->reverse();
}

void get_sum() 
{
    read(pos);
    read(tot);
    find(root, pos, null);
    find(root, pos + tot + 1, root);
    printf("%d\n", root->rs->ls->sum);
}

void max_sum() 
{
    find(root, 1, null);
    find(root, root->size, root);
    root->push_down();
    root->rs->push_down();
    root->rs->update();
    root->update();
    printf("%d\n", root->rs->ls->mx);
}

int main() 
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
    read(n);
    read(m);
    root = new Splay(0);
    root->rs = new Splay(0);
    for (int i = 1; i <= n; i++)
        read(a[i]);
    root->rs->ls = build(1, n);
    root->rs->ls->fa = root->rs;
    root->rs->update();
    root->rs->fa = root;
    root->update();
    for (int i = 1; i <= m; i++) 
	{
        char s[15];
        read(s);
        if (!strcmp(s, "INSERT"))
            insert();
        else if (!strcmp(s, "DELETE"))
            del();
        else if (!strcmp(s, "MAKE-SAME"))
            make_same();
        else if (!strcmp(s, "REVERSE"))
            reverse();
        else if (!strcmp(s, "GET-SUM"))
            get_sum();
        else
            max_sum();
    }
}