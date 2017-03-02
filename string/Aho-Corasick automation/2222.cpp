#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
struct Trie
{
	Trie *ch[26],*fail;
	int cnt;
	Trie()
	{
		memset(this,0,sizeof(Trie));
	}
	void insert(char *s)
	{
		Trie *p=this;
		while(*s)
		{
			if(!p->ch[*s-'a'])
				p->ch[*s-'a']=new Trie();
			p=p->ch[*s++-'a'];
		}
		++p->cnt;
	}
	void build()
	{
		queue <Trie*> q;
		for(int i=0;i<26;i++)
			if(ch[i])
				ch[i]->fail=this,q.push(ch[i]);
		while(!q.empty())
		{
			Trie *x=q.front();
			q.pop();
			for(int i=0;i<26;i++)
				if(x->ch[i])
				{
					Trie *p=x->fail;
					while(p!=this&&!p->ch[i])
						p=p->fail;
					if(p->ch[i])
						p=p->ch[i];
					x->ch[i]->fail=p;
					q.push(x->ch[i]);
				}
		}
	}
	int query(char *s)
	{
		int ans=0;
		Trie *p=this;
		while(*s)
		{
			while(!p->ch[*s-'a']&&p!=this)
				p=p->fail;
			if(p->ch[*s-'a'])
				p=p->ch[*s-'a'];
			for(Trie *tmp=p;tmp!=this&&tmp->cnt^-1;tmp->cnt=-1,tmp=tmp->fail)
				ans+=tmp->cnt;
			s++;
		}
		return ans;
	}
}*root;
char s[1000010];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		root=new Trie();
		int n;
		scanf("%d",&n);
		while(n--)
			scanf("%s",s),root->insert(s);
		root->build();
		scanf("%s",s);
		printf("%d\n",root->query(s));
	}
}
