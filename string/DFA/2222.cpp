#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
int vis[10010];
int size[10010];
struct Trie
{
	Trie *ch[26],*fail,*last;
	int cnt;
	Trie()
	{
		memset(this,0,sizeof(Trie));
	}
	void insert(char *s,int id)
	{
		Trie *p=this;
		while(*s)
		{
			if(!p->ch[*s-'a'])
				p->ch[*s-'a']=new Trie();
			p=p->ch[*s++-'a'];
		}
		size[id]=size[p->cnt]+1;
		p->cnt=id;
	}
	void build()
	{
		queue <Trie*> q;
		fail=this;
		for(int i=0;i<26;i++)
			if(!ch[i])
				ch[i]=this;
			else
				q.push(ch[i]),ch[i]->fail=this;
		while(!q.empty())
		{
			Trie *x=q.front();
			q.pop();
			for(int i=0;i<26;i++)
				if(!x->ch[i])
					x->ch[i]=x->fail->ch[i];
				else
					x->ch[i]->fail=x->fail->ch[i],
					x->ch[i]->last=x->ch[i]->fail->cnt?x->ch[i]->fail:x->ch[i]->fail->last,
					q.push(x->ch[i]);
		}
	}
	void query(char *s)
	{
		Trie *p=this;
		while(*s)
		{
			p=p->ch[*s-'a'];
			if(p->cnt)
				print(p);
			else if(p->last)
				print(p->last);
			s++;
		}
	}
	void print(Trie *x)
	{
		if(x)
		{
			if(vis[x->cnt])
				return;
			vis[x->cnt]=1;
			print(x->last);
		}
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
		memset(vis,0,sizeof(vis));
		memset(size,0,sizeof(size));
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",s);
			root->insert(s,i);
		}
		root->build();
		int ans=0;
		scanf("%s",s);
		root->query(s);
		for(int i=1;i<=n;i++)
			if(vis[i])
				ans+=size[i];
		printf("%d\n",ans);
	}
}
