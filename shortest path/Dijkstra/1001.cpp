#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <functional>

using namespace std;

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
	static char ch;
	x = 0;
	while (ch < '0')
		ch = getc();
	while (ch >= '0')
		x = (x << 1) + (x << 3) + ch - '0', ch = getc();
}

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

const int maxn = 2e6 + 10;
const int maxm = 6e6 + 10;

struct edge
{
	int to, len;
	edge *next;
	edge() {}
	edge(int to, int len, edge *next) :to(to), len(len), next(next) {}
	void* operator new(size_t);
}*head[maxn], mem[maxm];

void* edge :: operator new(size_t)
{
	static edge *p = mem;
	return p++;
}

void add(int x, int y, int z)
{
	head[x] = new edge(y, z, head[x]);
	head[y] = new edge(x, z, head[y]);
}

typedef pair <int, int> point;
point heap[maxm];
int f[maxm];
bool v[maxm];

int dijkstra(int S, int T)
{
	memset(f, 0x3f, sizeof(f));
	int size;
	heap[size = 1] = point(f[S] = 0, S);
	while (size)
	{
		int x = heap[1].second;
		pop_heap(heap + 1, heap + size-- + 1, greater <point> ());
		if (v[x])
			continue;
		v[x] = true;
		for (edge *p = head[x]; p; p = p->next)
			if (tense(f[p->to], f[x] + p->len))
				heap[++size] = point(f[p->to], p->to),
				push_heap(heap + 1, heap + size + 1, greater <point> ());
	}
	return f[T];
}

int main()
{
	int n, m;
	read(n);
	read(m);
	if (n == 1 || m == 1)
	{
		n = max(n, m) - 1;
		int ans = ~0u >> 1, x;
		while (n--)
			read(x), tense(ans, x);
		printf("%d\n", ans);
	}
	else
	{
		int mask = (n - 1) * (m - 1);
		int S = (n - 1) * (m - 1) * 2 + 1;
		int T = (n - 1) * (m - 1) * 2 + 2;
		for (int i = 1, x; i <= n; i++)
			for (int j = 1; j < m; j++)
			{
				read(x);
				if (i == 1)
					add((i - 1) * (m - 1) + j, T, x);
				else if (i == n)
					add((i - 2) * (m - 1) + mask + j, S, x);
				else
					add((i - 2) * (m - 1) + mask + j, (i - 1) * (m - 1) + j, x);
			}
		for (int i = 1, x; i < n; i++)
			for (int j = 1; j <= m; j++)
			{
				read(x);
				if (j == 1)
					add(S, (i - 1) * (m - 1) + mask + 1, x);
				else if (j == m)
					add(i * (m - 1), T, x);
				else
					add((i - 1) * (m - 1) + j - 1, (i - 1) * (m - 1) + mask + j, x);
			}
		for (int i = 1, x; i < n; i++)
			for (int j = 1; j < m; j++)
			{
				read(x);
				add((i - 1) * (m - 1) + j, (i - 1) * (m - 1) + j + mask, x);
			}
		printf("%d\n", dijkstra(S, T));
	}
}