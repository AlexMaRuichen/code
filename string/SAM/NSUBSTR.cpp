#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
int f[250010];
struct SAM
{
	SAM *ch[26],*fa;
	int cnt,len;
	bool v;
	vector <SAM*> son;
	void insert(int x)
	{
		static SAM *last=this;
		SAM *p=last,*np=new SAM();
		np->len=p->len+1;
		np->cnt=1;
		while(p&&!p->ch[x])
			p->ch[x]=np,p=p->fa;
		if(!p)
			np->fa=this;
		else
		{
			SAM *q=p->ch[x];
			if(p->len+1==q->len)
				np->fa=q;
			else
			{
				SAM *nq=new SAM();
				*nq=*q;
				nq->len=p->len+1;
				np->fa=q->fa=nq;
				nq->cnt=0;
				while(p&&p->ch[x]==q)
					p->ch[x]=nq,p=p->fa;
			}
		}
		last=np;
	}
	void* operator new(size_t)
	{
		static SAM *l,*r;
		if(l==r)
			r=(l=new SAM[1<<15])+(1<<15);
		return l++;
	}
	void getson()
	{
		v=true;
		if(fa)
			fa->son.push_back(this);
		for(int i=0;i<26;i++)
			if(ch[i]&&!ch[i]->v)
				ch[i]->getson();
	}
	void dfs()
	{
		for(int i=son.size()-1;i>=0;i--)
		{
			son[i]->dfs();
			cnt+=son[i]->cnt;
		}
		f[len]=max(f[len],cnt);
	}
}*root=new SAM();
char s[250010],*p=s;
int main()
{
	fread(s,1,250000,stdin);
	int n=0;
	while(*p>='a')
		root->insert(*p++-'a'),++n;
	root->getson();
	root->dfs();
	for(int i=n;i;i--)
		f[i]=max(f[i+1],f[i]);
	for(int i=1;i<=n;i++)
		printf("%d\n",f[i]);
}
