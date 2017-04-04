#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 3010;
typedef unsigned int uint;

struct edge
{
	int to;
	edge *next;
	edge() {}
	edge(int to, edge *next) :to(to), next(next) {};
	void* operator new(size_t);
}*head[maxn], mem[maxn << 1], *p;

void* edge :: operator new(size_t)
{
	return p++;
}

void add(int x, int y)
{
	head[x] = new edge(y, head[x]);
}

uint Hash(int x)
{
	vector <int> v;
	uint hash = 31;
	for (edge *p = head[x]; p; p = p->next)
		v.push_back(Hash(p->to));
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++)
		hash = hash * 100 + v[i];
	return hash;
}


char s[maxn];
char t[maxn];
int fa[maxn];

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		memset(head, 0, sizeof(head));
		p = mem;
		scanf("%s%s", s, t);
		int cnt = 0;
		int cur = ++cnt;
		for (int i = 0; s[i]; i++)
			if (s[i] == '0')
			{
				fa[++cnt] = cur;
				add(cur, cnt);
				cur = cnt;
			}
			else if (s[i] == '1')
				cur = fa[cur];
		uint ans1 = Hash(1);
		memset(head, 0, sizeof(head));
		p = mem;
		cnt = 0;
		cur = ++cnt;
		for (int i = 0; t[i]; i++)
			if (t[i] == '0')
			{
				fa[++cnt] = cur;
				add(cur, cnt);
				cur = cnt;
			}
			else if (t[i] == '1')
				cur = fa[cur];
		uint ans2 = Hash(1);
		puts(ans1 == ans2 ? "same" : "different");
	}
}