#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 1e6;

struct SAM
{
	SAM *ch[26], *fa;
	vector <SAM*> son;
	int cnt, len;
	bool v;
	void* operator new(size_t);
}*root = new SAM(), *last = root, mem[maxn << 1], *e[210];

void* SAM :: operator new(size_t)
{
	static SAM *p = mem;
	return p++;
}

void insert(int x)
{
	SAM *p = last;
	if (p->ch[x])
	{
		SAM *q = p->ch[x];
		if (q->len == p->len + 1)
			last = q;
		else
		{
			SAM *nq = new SAM();
			*nq = *q;
			nq->len = p->len + 1;
			last = q->fa = nq;
			nq->cnt = 0;
			while (p && p->ch[x] == q)
				p->ch[x] = nq, p = p->fa;
		}
	}
	else
	{
		SAM *np = new SAM();
		last = np;
		np->len = p->len + 1;
		while (p && !p->ch[x])
			p->ch[x] = np, p = p->fa;
		if (!p)
			np->fa = root;
		else
		{
			SAM *q = p->ch[x];
			if (q->len == p->len + 1)
				np->fa = q;
			else
			{
				SAM *nq = new SAM();
				*nq = *q;
				nq->len = p->len + 1;
				q->fa = np->fa = nq;
				nq->cnt = 0;
				while (p && p->ch[x] == q)
					p->ch[x] = nq, p = p->fa;
			}
		}
	}
	++last->cnt;
}

void dfs(SAM *x)
{
	for (int i = x->son.size() - 1; ~i; i--)
		dfs(x->son[i]),
		x->cnt += x->son[i]->cnt;
}

void get(SAM *x)
{
	x->v = true;
	if (x->fa)
		x->fa->son.push_back(x);
	for (int i = 0; i < 26; i++)
		if (x->ch[i] && !x->ch[i]->v)
			get(x->ch[i]);
}

char s[1000010];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        char *p = s;
        last = root;
        scanf("%s", s);
        while (*p)
            insert(*p++ - 'a');
        e[i] = last;
    }
    get(root);
    dfs(root);
    for (int i = 1; i <= n; i++)
        printf("%d\n", e[i]->cnt);
}