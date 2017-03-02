#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
const int maxn=300010;
struct SAM
{
	map <int,SAM*> ch;
	SAM *fa;
	int len;
	void insert(int x)
	{
		static SAM *last=this;
		SAM *p=last;
		SAM *np=new SAM();
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
				q->fa=nq;
				np->fa=nq;
				while(p&&p->ch[x]==q)
					p->ch[x]=nq,p=p->fa;
			}
		}
		last=np;
	}
	void query(int n)
	{
		SAM *p=this;
		map <int,SAM*> :: iterator it;
		while(n--)
		{
			it=p->ch.begin();
			printf("%d%c",it->first,n?' ':'\n');
			p=it->second;
		}
	}
	void* operator new(size_t)
	{
		static SAM *l,*r;
		if(l==r)
			return r=(l=new SAM[1<<15])+(1<<15);
		return l++;
	}
}*root=new SAM();
int a[maxn];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),root->insert(a[i]);
	for(int i=1;i<n;i++)
		root->insert(a[i]);
	root->query(n);
}
