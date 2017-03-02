#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
#define strn str[now]-'a'
using namespace std;
const int maxn=1e6+10;
char str[maxn];
struct Trie
{
	Trie *ch[26],*fail;
	int cnt;
	Trie()
	{
		memset(ch,0,sizeof(ch));
		fail=NULL;
		cnt=0;
	}
	void insert(char str[])
	{
		Trie *p=this;
		int now=0;
		while(str[now])
		{
			if(!p->ch[strn])
				p->ch[strn]=new Trie();
			p=p->ch[strn];
			++now;
		}
		p->cnt++;
	}
	void build()
	{
		queue <Trie*> q;
		for(int i=0;i<26;i++)
			if(this->ch[i])
				this->ch[i]->fail=this,q.push(this->ch[i]);
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
	int query(char str[])
	{
		int now=0,ans=0;
		Trie *p=this;
		while(str[now])
		{
			while(!p->ch[strn]&&p!=this)
				p=p->fail;
			if(p->ch[strn])
				p=p->ch[strn];
			Trie *tmp=p;
			while(tmp!=this&&tmp->cnt!=-1)
				ans+=tmp->cnt,tmp->cnt=-1,tmp=tmp->fail;
			++now;
		}
		return ans;
	}
}*root;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		root=new Trie();
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",str);
			root->insert(str);
		}
		root->build();
		scanf("%s",str);
		printf("%d\n",root->query(str));
	}
}
