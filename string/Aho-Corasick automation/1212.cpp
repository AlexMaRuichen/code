#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int maxn=(1<<20)+10;
char s[maxn];
struct Trie
{
	Trie *ch[26],*fail;
	int len;
	Trie(){memset(this,0,sizeof(Trie));}
	void insert(char *s)
	{
		Trie *p=this;
		char *o=s;
		while(*s)
		{
			if(!p->ch[*s-'a'])
				p->ch[*s-'a']=new Trie();
				p=p->ch[*s++-'a'];
		}
		p->len=int(s-o);
	}
	void build()
	{
		queue <Trie*> q;
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
				if(x->ch[i])
				{
					x->ch[i]->fail=x->fail->ch[i];
					q.push(x->ch[i]);
				}
				else
					x->ch[i]=x->fail->ch[i];
		}
	}
}*root=new Trie();
int dp()
{
	Trie *p=root;
	static bool f[maxn];
	f[0]=true;
	int ans=0;
	for(int i=1;s[i];i++)
	{
		f[i]=false;
		p=p->ch[s[i]-'a'];
		for(Trie *x=p;x!=root;x=x->fail)
			if(x->len)
			{
				f[i]|=f[i-x->len];
				if(f[i])
					break;
			}
		if(f[i])
			ans=i;
	}
	return ans;
}
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",s),root->insert(s);
	root->build();
	for(int i=1;i<=m;i++)
		scanf("%s",s+1),printf("%d\n",dp());
}
