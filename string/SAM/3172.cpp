#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
struct SAM
{
	SAM *ch[26],*fa;
	int len,cnt;
	bool v;
	vector <SAM*> son;
	void insert(int x);
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
		for(int i=son.size()-1;~i;i--)
			son[i]->dfs(),cnt+=son[i]->cnt;
	}
}*root=new SAM(),*last,*end[200];
void SAM :: insert(int x)
{
	SAM *p=last;
	if(p->ch[x])
	{
		SAM *q=p->ch[x];
		if(p->len+1==q->len)
			last=q;
		else
		{
			SAM *nq=new SAM();
			last=nq;
			*nq=*q;
			nq->cnt=0;
			nq->len=p->len+1;
			q->fa=nq;
			while(p&&p->ch[x]==q)
				p->ch[x]=nq,p=p->fa;
		}
	}
	else
	{
		SAM *np=new SAM();
		np->len=p->len+1;
		last=np;
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
				nq->cnt=0;
				np->fa=q->fa=nq;
				while(p&&p->ch[x]==q)
					p->ch[x]=nq,p=p->fa;
			}
		}
	}
	++last->cnt;
}
char s[1000010];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		char *p=s;
		last=root;
		scanf("%s",s);
		while(*p)
			root->insert(*p++-'a');
		end[i]=last;
	}
	root->getson();
	root->dfs();
	for(int i=1;i<=n;i++)
		printf("%d\n",end[i]->cnt);
}
