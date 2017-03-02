#include <stdio.h>
#include <string.h>
#include <algorithm>
#define strn str[now]-'a'
using namespace std;
const int maxn=210;
const int maxm=1e6+10;
char s[maxn][maxm];
int t;
struct Trie
{
	Trie *ch[26],*fail;
	int cnt;
	int flag;
	Trie()
	{
		memset(ch,0,sizeof(ch));
		fail=NULL;
		cnt=0;
	}
	Trie* insert(char str[])
	{
		Trie *p=this;
		int now=0;
		while(str[now])
		{
			if(!p->ch[strn])
				p->ch[strn]=new Trie();
			p=p->ch[strn];
			++p->cnt;
			++now;
		}
		return p;
	}
	void build();
}*root=new Trie(),*end[maxn];
struct queue
{
	Trie* a[maxm];
	int l,r;
	queue()
	{
		l=1,r=0;
	}
	bool empty()
	{
		return l>r;
	}
	void push(Trie* x)
	{
		a[++r]=x;
	}
	Trie* front()
	{
		return a[l];
	}
	void pop()
	{
		++l;
	}
}q;
void Trie :: build()
{
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
				while(!p->ch[i]&&p!=this)
					p=p->fail;
				if(p->ch[i])
					p=p->ch[i];
				x->ch[i]->fail=p;
				q.push(x->ch[i]);
			}
	}
	for(int i=q.r;i;i--)
		q.a[i]->fail->cnt+=q.a[i]->cnt;
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]),end[i]=root->insert(s[i]);
	root->build();
	for(t=1;t<=n;t++)
		printf("%d\n",end[t]->cnt);
}
