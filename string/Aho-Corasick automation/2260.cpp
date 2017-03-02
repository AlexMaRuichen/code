#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
#define strn str[now]=='W'?0:str[now]=='S'?1:str[now]=='E'?2:3
using namespace std;
const int maxn=1e7+10;
const int maxm=1e5+10;
char str[maxn];
char bak[maxm][110];
struct Trie
{
	Trie *ch[4],*fail;
	bool flag;
	void* operator new(size_t);
	Trie()
	{
		memset(ch,0,sizeof(ch));
		fail=NULL;
		flag=false;
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
	}
	void build()
	{
		queue <Trie*> q;
		for(int i=0;i<4;i++)
			if(this->ch[i])
				this->ch[i]->fail=this,q.push(this->ch[i]);
		while(!q.empty())
		{
			Trie *x=q.front();
			q.pop();
			for(int i=0;i<4;i++)
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
	void process(char str[])
	{
		Trie *p=this;
		int now=0;
		while(str[now])
		{
			while(!p->ch[strn]&&p!=this)
				p=p->fail;
			if(p->ch[strn])
				p=p->ch[strn];
			Trie *tmp=p;
			while(tmp!=this&&!tmp->flag)
				tmp->flag=true,tmp=tmp->fail;
			++now;
		}
	}
	int query(char str[])
	{
		Trie *p=this;
		int now=0,ans=0;
		while(str[now])
		{
			if(p->ch[strn]->flag)
				++ans;
			else
				break;
			p=p->ch[strn];
			++now;
		}
		return ans;
	}
}*root=new Trie(),Tdata[maxm<<2];
void* Trie:: operator new(size_t)
{
	static Trie* p=Tdata;
	return p++;
}
int n;
int main()
{
	scanf("%*d%d",&n);
	scanf("%s",str);
	for(int i=1;i<=n;i++)
		scanf("%s",bak[i]),root->insert(bak[i]);
	root->build();
	root->process(str);
	for(int i=1;i<=n;i++)
		printf("%d\n",root->query(bak[i]));
}
