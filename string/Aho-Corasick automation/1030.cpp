#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int maxn=6010;
const int mod=10007;
struct Trie
{
	Trie *ch[26],*fail;
	bool flag;
	Trie(){memset(this,0,sizeof(Trie));}
	void* operator new(size_t);
	void insert(char *s)
	{
		Trie *p=this;
		while(*s)
		{
			if(!p->ch[*s-'A'])
				p->ch[*s-'A']=new Trie();
			p=p->ch[*s++-'A'];
		}
		p->flag=true;
	}
	void build()
	{
		queue <Trie*> q;
		for(int i=0;i<26;i++)
			if(ch[i])
				ch[i]->fail=this,q.push(ch[i]);
			else
				ch[i]=this;
		while(!q.empty())
		{
			Trie *x=q.front();
			q.pop();
			for(int i=0;i<26;i++)
				if(x->ch[i])
				{
					x->ch[i]->fail=x->fail->ch[i];
					x->ch[i]->flag|=x->ch[i]->fail->flag;
					q.push(x->ch[i]);
				}
				else
					x->ch[i]=x->fail->ch[i];
		}
	}
}mempool[maxn],*p=mempool,*root=new Trie();
void* Trie :: operator new(size_t)
{
	return p++;
}
int n,m;
char s[maxn];
int f[110][maxn];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",s),root->insert(s);
	root->build();
	f[0][0]=1;
	int ans=1;
	for(int i=0;i<m;i++)
	{
		ans=ans*26%mod;
		for(int j=0;j<p-mempool;j++)
			if(!mempool[j].flag)
				for(int k=0;k<26;k++)
					f[i+1][mempool[j].ch[k]-mempool]=(f[i+1][mempool[j].ch[k]-mempool]+f[i][j])%mod;
	}
	for(int i=0;i<p-mempool;i++)
		if(!mempool[i].flag)
			ans=(ans+mod-f[m][i])%mod;
	printf("%d\n",ans);
}
