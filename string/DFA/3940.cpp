#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int maxn=1e5+10;
struct Trie
{
	Trie *ch[26],*fail;
	int mx;
	Trie()
	{
		memset(this,0,sizeof(Trie));
	}
	void insert(char *s)
	{
		char *t=s;
		Trie *p=this;
		while(*t)
		{
			if(!p->ch[*t-'a'])
				p->ch[*t-'a']=new Trie();
			p=p->ch[*t++-'a'];
		}
		p->mx=max(p->mx,int(t-s));
	}
	void build()
	{
		queue <Trie*> q;
		for(int i=0;i<26;i++)
			if(!ch[i])
				ch[i]=this;
			else
				ch[i]->fail=this,q.push(ch[i]);
		while(!q.empty())
		{
			Trie *x=q.front();
			q.pop();
			for(int i=0;i<26;i++)
				if(!x->ch[i])
					x->ch[i]=x->fail->ch[i];
				else
					x->ch[i]->fail=x->fail->ch[i],
					x->ch[i]->mx=max(x->ch[i]->mx,x->ch[i]->fail->mx),
					q.push(x->ch[i]);
		}
	}
}*root=new Trie();
char stack[maxn];
char bak[maxn];
char s[maxn];
int n;
Trie* x[maxn];
int main()
{
	scanf("%s",bak);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%s",s),root->insert(s);
	root->build();
	x[0]=root;
	int top=0;
	for(int i=1;bak[i-1];i++)
	{
		stack[++top]=bak[i-1];
		x[top]=x[top-1]->ch[bak[i-1]-'a'];
		if(x[top]->mx)
			top-=x[top]->mx;
	}
	stack[top+1]=0;
	puts(stack+1);
}
