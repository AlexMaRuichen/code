#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 500010;
const int size = 1000;
const int maxb = maxn / size * 3;
const int inf = 1e9;

template <typename T> inline T& relax(T& a, const T &b)
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
		if (ch == '-')
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

struct block
{
	int a[size];
	block *next;
	bool rev, sam;
	int same, smx[2], mx, len, sum;
	void* operator new(size_t);
	void pushdown();
	void update();
}*root = new block(), mem[maxb];

queue <block*> Q;

void debug()
{
	for (block *p = root; p; p = p->next, puts(""))
	{
		printf("len : %d mx : %d smx[0] : %d smx[1] : %d sum : %d\n", p->len, p->mx, p->smx[0], p->smx[1], p->sum);
		for (int i = 0; i < p->len; i++)
			printf("%d ", p->a[i]);
	}
}

void* block :: operator new(size_t)
{
	static block *p = mem, *g;
	if (!Q.empty())
		g = Q.front(), Q.pop();
	else
		g = p++;
	return g;
}
void block :: pushdown()
{
	if (sam)
	{
		for (int i = 0; i < len; i++)	
			a[i] = same;
		sum = len * same;
		mx = smx[0] = smx[1] = max(len * same, same);
		sam = rev = false;
	}
	else if (rev)
	{
		reverse(a, a + len);
		swap(smx[0], smx[1]);
		rev = false;
	}
}

void block :: update()
{
	sum = 0;
	smx[0] = smx[1] = mx = -inf;
	for (int i = 0; i < len; i++)
	{
		relax(relax(mx, a[i]), smx[1] + a[i]);
		relax(smx[0], sum + a[i]);
		smx[1] = max(a[i], smx[1] + a[i]);
		sum += a[i];
	}
}

void merge(block *x, block *y)
{
	x->pushdown();
	y->pushdown();
	relax(relax(x->mx, y->mx), x->smx[1] + y->smx[0]);
	relax(x->smx[0], x->sum + y->smx[0]);
	x->smx[1] = max(y->smx[1], x->smx[1] + y->sum);
	x->sum += y->sum;
	memcpy(x->a + x->len, y->a, sizeof(int) * y->len);
	x->len += y->len;
	x->next = y->next;
	Q.push(y);
}

void fill(block *x, int len, int *a, block *next)
{
	x->next = next;
	x->len = len;
	memcpy(x->a, a, sizeof(int) * len);
	x->update();
}

void spilt(block *x, int len)
{
	if (x->len == len)
		return;
	x->pushdown();
	block *t = new block();
	fill(t, x->len - len, x->a + len, x->next);
	x->len = len;
	x->next = t;
	x->update();
}

block* find(int &x)
{
	static block *pos;
	pos = root;
	for (; pos && x > pos->len; pos = pos->next)
		x -= pos->len;
	return pos;
}

void maintain(block *x)
{
//	debug();
	while (x)
	{
		for (block *t = x->next; t && x->len + t->len <= size; t = x->next)
			merge(x, t);
		x = x->next;
	}
}

void insert(int p, int len, int *a)
{
	int curlen;
	block *pos = find(p), *t;
	spilt(pos, p);
	for (curlen = 0; curlen + size <= len; curlen += size, pos = pos->next)
	{
		t = new block();
		fill(t, size, a + curlen, pos->next);
		pos->next = t;
	}
	if (curlen < len)
	{
		t = new block();
		fill(t, len - curlen, a + curlen, pos->next);
		pos->next = t;
	}
	maintain(pos);
}

void erase(int p, int len)
{
	--p;
	block *pos = find(p), *t;
	spilt(pos, p);
	for (t = pos->next; t && len > t->len; t = t->next)
		len -= t->len;
	spilt(t, len);
	t = t->next;
	for (block *x = pos->next; x != t; x = pos->next)
		pos->next = x->next,
		Q.push(x);
	maintain(pos);
}

void makesame(int p, int len, int v)
{
	--p;
	block *pos = find(p), *t;
	spilt(pos, p);
	for (t = pos->next; t && len > t->len; t = t->next)
		t->sam = true, 
		t->same = v,
		t->sum = t->len * v,
		t->mx = t->smx[0] = t->smx[1] = max(v, v * t->len),
		len -= t->len;
	if (len)
	{
		spilt(t, len);
		t->sam = true;
		t->same = v;
		t->sum = t->len * v;
		t->mx = t->smx[0] = t->smx[1] = max(v, v * t->len);
	}
	maintain(pos);
}

block* stack[maxb];

void reverse(int p, int len)
{
	static int cnt;
	cnt = 0;
	--p;
	block *pos = find(p), *t;
	spilt(pos, p);
	for (t = pos->next; t && len > t->len; t = t->next)
		stack[++cnt] = t,
		len -= t->len;
	spilt(t, len);
	stack[++cnt] = t;
	pos->next = stack[cnt];
	stack[0] = t->next;
	for (int i = cnt; i; i--)
		stack[i]->rev ^= 1,
		stack[i]->next = stack[i - 1];
	maintain(pos);
}

int getsum(int p, int len)
{
	--p;
	int sum = 0;
	block *pos = find(p), *t;
	spilt(pos, p);
	for (t = pos->next; t && len > t->len; t = t->next)
		sum += t->sum,
		len -= t->len;
	spilt(t, len);
	sum += t->sum;
	maintain(pos);
	return sum;
}

int maxsum()
{
	int mx = -inf, smx[2] = {-inf, -inf}, sum = 0;
	for (block *p = root; p; p = p->next)
	{
		relax(relax(mx, p->mx), smx[1] + p->smx[p->rev]);
		relax(smx[0], sum + p->smx[p->rev]);
		smx[1] = max(p->smx[p->rev ^ 1], smx[1] + p->sum);
		sum += p->sum;
	}
	return mx;
}

int a[maxn];

int main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	int n, m;
	read(n);
	read(m);
	for (int i = 0; i < n; i++)
		read(a[i]);
	insert(0, n, a);
	while (m--)
	{
		static char opt[10];
		static int pos, tot, v;
		read(opt);
        if (opt[0] == 'I')
		{
			read(pos);
			read(tot);
			for (int i = 0; i < tot; i++)
				read(a[i]);
            insert(pos, tot, a);
		}
		else if (opt[0] == 'D')
		{
			read(pos);
			read(tot);
            erase(pos, tot);
		}
		else if (opt[4] == '-')
		{
			read(pos);
			read(tot);
			read(v);
            makesame(pos, tot, v);
		}
		else if (opt[0] == 'R')
		{
			read(pos);
			read(tot);
            reverse(pos, tot);
		}
		else if (opt[0] == 'G')
		{
            read(pos);
			read(tot);
			printf("%d\n", getsum(pos, tot));
		}
		else
		{
            printf("%d\n", maxsum());
		}
	}
}