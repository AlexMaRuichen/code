#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
struct Trie
{
	Trie *ch[2],*fail;
	bool flag;
	short in;
	Trie()
	{
		memset(this,0,sizeof(Trie));
	}
	void insert(char *s)
	{
		Trie *p=this;
		while(*s)
		{
			if(!p->ch[*s-'0'])
				p->ch[*s-'0']=new Trie();
			p=p->ch[*s++-'0'];
		}
		p->flag=true;
	}
	void build()
	{
		queue <Trie*> q;
		while(!q.empty())
			q.pop();
		for(int i=0;i<2;i++)
			if(!ch[i])
				ch[i]=this;
			else
				ch[i]->fail=this,q.push(ch[i]);
		while(!q.empty())
		{
			Trie *x=q.front();
			q.pop();
			for(int i=0;i<2;i++)
				if(!x->ch[i])
					x->ch[i]=x->fail->ch[i];
				else
					x->ch[i]->fail=x->fail->ch[i],
					x->ch[i]->flag|=x->ch[i]->fail->flag,
					q.push(x->ch[i]);
		}
	}
	void *operator new(size_t);
}*root,mempool[30010],*p=mempool;
void* Trie :: operator new(size_t)
{
	return p++;
}
queue <Trie*> q;
int topo()
{
	int cnt=0;
	for(Trie *x=mempool;x<p;x++)
		if(!x->flag)
		{
			++cnt;
			++x->ch[0]->in;
			++x->ch[1]->in;
		}
	for(Trie *x=mempool;x<p;x++)
		if(!x->flag&&!x->in)
			q.push(x);
	int ans=0;
	while(!q.empty())
	{
		++ans;
		Trie *x=q.front();
		q.pop();
		for(int i=0;i<2;i++)
			if(!x->ch[i]->flag&&!--x->ch[i]->in)
				q.push(x->ch[i]);
	}
	return ans^cnt;
}
char s[30010];
int main()
{
	int n;
	scanf("%d",&n);
	root=new Trie();
	for(int i=1;i<=n;i++)
		scanf("%s",s),root->insert(s);
	root->build();
	if(topo())
		puts("TAK");
	else
		puts("NIE");
}
