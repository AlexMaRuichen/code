#include <stdio.h>
#include <algorithm>
using namespace std;
struct SAM
{
	SAM *ch[26],*fa;
	int len;
	int insert(int x);
	void* operator new(size_t)
	{
		static SAM *l,*r;
		if(l==r)
			r=(l=new SAM[1<<15])+(1<<15);
		return l++;
	}
}*root=new SAM(),*last;
int SAM :: insert(int x)
{
	SAM *p=last;
	SAM *np=new SAM();
	np->len=p->len+1;
	while(p&&!p->ch[x])
		p->ch[x]=np,p=p->fa;
	if(!p)
	{
		np->fa=this;
		last=np;
		return np->len;
	}
	else
	{
		SAM *q=p->ch[x];
		if(p->len+1==q->len)
		{
			np->fa=q;
			last=np;
			return np->len-q->len;
		}
		else
		{
			SAM *nq=new SAM();
			*nq=*q;
			nq->len=p->len+1;
			np->fa=q->fa=nq;
			while(p&&p->ch[x]==q)
				p->ch[x]=nq,p=p->fa;
			last=np;
			return np->len-nq->len;
		}
	}
}
char s[100100];
long long ans;
int main()
{
	int n;
	scanf("%d\n",&n);
	fread(s,1,100050,stdin);
	char *p=s;
	for(int i=1;i<=n;i++)
	{
		last=root;
		while(*p<'a'||*p>'z')
			p++;
		while(*p>='a'&&*p<='z')
			ans+=root->insert(*p++-'a'),printf("%lld\n",ans);
	}
}
