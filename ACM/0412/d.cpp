#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <queue>

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

using namespace std;

const int maxn = 50010;

struct link
{
	int x, y;
	link *l, *r;
	link();
	link(int X, int Y);
	void* operator new(size_t);
}*root, nil, *null = &nil, mem[maxn], *ptr;

link :: link()
{
	x = y = 0;
	l = r = this;
}

link :: link(int X, int Y)
{
	x = X;
	y = Y;
	l = r = null;
}

queue <link*> q;
void* link :: operator new(size_t)
{
	static link *g;
	if (!q.empty())
		g = q.front(), q.pop();
	else
		g = ptr++;
	return g;
}

void print()
{
	for (link *p = root->r; p != null; p = p->r)
		printf("%d %d\n", p->x, p->y);
	puts("");
}

int main()
{
	int n;
	while (scanf("%d", &n) && n)
	{
		memset(mem, 0, sizeof(mem));
		while (!q.empty())
			q.pop();
		ptr = mem;
		root = new link(0, 0);
		while (n--)
		{
			static int opt, x, y;
			static long long ans;
			scanf("%d%d%d", &opt, &x, &y);
			if (opt == -1)
			{
				for (link *p = root->r; p != null; p = p->r)
					if (p->x == x && p->y == y)
					{
						p->l->r = p->r;
						p->r->l = p->l;
						q.push(p);
						break;
					}
			}
			else if (opt == 1)
			{
				link *p = new link(x, y);
				p->l = root;
				p->r = root->r;
				root->r->l = p;
				root->r = p;
			}
			else
			{
				ans = -(~0ull >> 2);
				for (link *p = root->r; p != null; p = p->r)
					relax(ans, p->x * 1ll * x + p->y * 1ll * y);
				printf("%lld\n", ans);
			}
//			print();
		}
	}
}