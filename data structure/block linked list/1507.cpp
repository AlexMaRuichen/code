#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 1 << 25;
const int size = 6000;
const int maxb = maxn / size * 3;

char str[maxn];

struct block
{
	char str[size];
	block *next;
	int len;
	void* operator new(size_t);
}mem[maxb], *root = new block();

queue <block*> q;

void* block :: operator new(size_t)
{
	static block *p = mem, *g;
	if (!q.empty())
		g = q.front(), q.pop();
	else
		g = p++;
	g->next = NULL;
	g->len = 0;
	return g;
}

block* find(int &x)
{
	static block *pos;
	for (pos = root; pos && x > pos->len; pos = pos->next)
		x -= pos->len;
	return pos;
}

void fill(block *x, int len, char *str, block *next)
{
	x->next = next;
	x->len = len;
	memcpy(x->str, str, len);
}

void spilt(block *x, int len)
{
	if (x->len == len)
		return;
	block *t = new block();
	fill(t, x->len - len, x->str + len, x->next);
	x->next = t;
	x->len = len;
}

void maintain(block *x)
{
	while (x)
	{
		for (block *t = x->next; t && x->len + t->len <= size; t = x->next)
		{
			memcpy(x->str + x->len, t->str, t->len);
			x->len += t->len;
			x->next = t->next;
			q.push(t);
		}
		x = x->next;
	}
}

int ptr;

void insert(int len)
{
	int cur = ptr, curlen;
	block *pos = find(cur), *t;
	spilt(pos, cur);
	for (curlen = 0; curlen + size <= len; curlen += size, pos = pos->next)
	{
		t = new block();
		fill(t, size, str + curlen, pos->next);
		pos->next = t;
	}
	if (curlen < len)
	{
		t = new block();
		fill(t, len - curlen, str + curlen, pos->next);
		pos->next = t;
	}
	maintain(pos);
}

void erase(int len)
{
	int cur = ptr;
	block *pos = find(cur), *p;
	spilt(pos, cur);
	for (p = pos->next; p && len > p->len; p = p->next)
		len -= p->len;
	spilt(p, len);
	p = p->next;
	for (block *x = pos->next; x != p; x = pos->next)
		pos->next = x->next,
		q.push(x);
	maintain(pos);
}

void get(int len)
{
	int cur = ptr, curlen;
	block *pos = find(cur);
	curlen = min(len, pos->len - cur);
	memcpy(str, pos->str + cur, curlen);
	for (pos = pos->next; pos && curlen + pos->len <= len; pos = pos->next)
	{
		memcpy(str + curlen, pos->str, pos->len);
		curlen += pos->len;
	}
	if (curlen < len && pos)
		memcpy(str + curlen, pos->str, len - curlen);
	str[len] = 0;
}

void readstring(int x = -1)
{
	char ch = getchar();
	char *s = str;
	while (ch < 32 || ch > 126)
		ch = getchar();
	if(x ^ -1)
		while (x--)
		{
			if(ch == '\n' || ch == '\r')
				++x;
			else
				*s++ = ch;
			ch = getchar();
		}
	else
	{
		while((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
			*(s++) = ch, ch = getchar();
		*s = 0;		
	}
}

void debug()
{
	for (block *p = root; p; p = p->next)
		puts(p->str);
}

int n;

int main()
{
	scanf("%d",&n);
	for(int i = 1, x; i <= n; i++)
	{
		readstring();
		if(!strcmp(str, "Insert"))
		{
			scanf("%d", &x);
			readstring(x);
			insert(x);
		}
		else if(!strcmp(str, "Move"))
			scanf("%d", &ptr);
		else if(!strcmp(str, "Delete"))
		{
			scanf("%d", &x);
			erase(x);
		}
		else if(!strcmp(str, "Get"))
		{
			scanf("%d", &x);
			get(x);
			puts(str);
		}
		else if(!strcmp(str, "Prev"))
			--ptr;
		else
			++ptr;
	}
}