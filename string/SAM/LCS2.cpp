#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
int cnt;
int fans;
struct SAM
{
	SAM *ch[26],*fa;
	int len,mx[10];
	bool v;
	vector <SAM*> son;
	void insert(int x)
	{
		static SAM *last=this;
		SAM *p=last,*np=new SAM();
		np->len=p->len+1;
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
				q->fa=np->fa=nq;
				while(p&&p->ch[x]==q)
					p->ch[x]=nq,p=p->fa;
			}
		}
		last=np;
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
	void get()
	{
		int ans=len;
		for(int i=son.size()-1;i>=0;i--)
		{
			son[i]->get();
			for(int j=1;j<=cnt;j++)
				mx[j]=max(mx[j],son[i]->mx[j]);
		}
		
		for(int i=1;i<=cnt;i++)
			ans=min(ans,mx[i]);
		fans=max(ans,fans);
	}
	void match(char *s,int y)
	{
		SAM *p=this;
		int l=0;
		while(*s)
		{
			if(p->ch[*s-'a'])
				++l,p=p->ch[*s-'a'];
			else
			{
				while(p&&!p->ch[*s-'a'])
					p=p->fa;
				if(!p)
					l=0,p=this;
				else
					l=p->len+1,p=p->ch[*s-'a'];
			}
			p->mx[y]=max(p->mx[y],l);
			s++;
		}
	}
	void* operator new(size_t)
	{
		static SAM *l,*r;
		if(l==r)
			r=(l=new SAM[1<<15])+(1<<15);
		return l++;
	}
}*root=new SAM();
char s[100010];
int main()
{
	scanf("%s",s);
	char *p=s;
	while(*p)
		root->insert(*p++-'a');
	root->getson();
	while(scanf("%s",s)!=EOF)
		root->match(s,++cnt);
	root->get();
	printf("%d\n",fans);
}
