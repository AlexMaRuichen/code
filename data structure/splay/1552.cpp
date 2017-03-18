#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
const int inf=~0u>>2;
typedef pair<int,int> id;
bool cmp(const id &a,const id &b)
{
	return a.second<b.second;
}
int n;
id p[maxn];
struct Splay
{
	Splay *ls,*rs,*fa;
	int size;
	bool rev;
	Splay();
	void update();
	void reverse();
	void push_down();
	void* operator new(size_t);
}*null=new Splay(),*ptr[maxn],Tdata[maxn],*root=null;
bool flag;
Splay :: Splay()
{
	size=flag?1:0;
	rev=0;
	ls=rs=fa=null;
}
void Splay :: update()
{
	size=ls->size+rs->size+1;
}
void Splay :: reverse()
{
	swap(ls,rs);
	rev^=1;
}
void Splay :: push_down()
{
	if(rev)
	{
		ls->reverse();
		rs->reverse();
		rev=0;
	}
}
void* Splay :: operator new(size_t)
{
	static Splay *p=Tdata;
	return p++;
}
void zig(Splay *x)
{
	Splay *y=x->fa;
	y->push_down();
	x->push_down();
	y->ls=x->rs;
	x->rs->fa=y;
	x->rs=y;
	x->fa=y->fa;
	if(y==y->fa->ls)
		y->fa->ls=x;
	else if(y==y->fa->rs)
		y->fa->rs=x;
	y->fa=x;
	y->update();
	if(root==y)
		root=x;
}
void zag(Splay *x)
{
	Splay *y=x->fa;
	y->push_down();
	x->push_down();
	y->rs=x->ls;
	x->ls->fa=y;
	x->ls=y;
	x->fa=y->fa;
	if(y==y->fa->ls)
		y->fa->ls=x;
	else if(y==y->fa->rs)
		y->fa->rs=x;
	y->fa=x;
	y->update();
	if(root==y)
		root=x;
}
void splay(Splay *x,Splay *t)
{
	Splay *y,*z;
	x->push_down();
	while(true)
	{
		y=x->fa;
		z=y->fa;
		if(y==t)
			break;
		else if(z==t)
		{
			if(x==y->ls)
				zig(x);
			else
				zag(x);
			break;
		}
		else if(x==y->ls)
		{
			if(y==z->ls)
				zig(y);
			zig(x);
		}
		else
		{
			if(y==z->rs)
				zag(y);
			zag(x);
		}
	}
	x->update();
}
void find(Splay *x,int y,Splay *z)
{
	while(true)
	{
		x->push_down();
		if(y<=x->ls->size)
			x=x->ls;
		else
		{
			y-=x->ls->size;
			if(y==1)
				break;
			--y;
			x=x->rs;
		}
	}
	splay(x,z);
}
Splay *build(int l,int r)
{
	if(l>r)
		return null;
	int mid=(l+r)>>1;
	ptr[p[mid].first]=new Splay();
	ptr[p[mid].first]->ls=build(l,mid-1);
	ptr[p[mid].first]->rs=build(mid+1,r);
	ptr[p[mid].first]->ls->fa=ptr[p[mid].first]->rs->fa=ptr[p[mid].first];
	ptr[p[mid].first]->update();
	return ptr[p[mid].first];
}
int rank;
int main()
{
	flag=true;
	root=new Splay();
	root->rs=new Splay();
	root->rs->fa=root;
	root->update();	
	scanf("%d",&n);	
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i].first),p[i].second=i;
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++)
		p[i].first=i;
	sort(p+1,p+n+1,cmp);
	root->rs->ls=build(1,n);
	root->rs->ls->fa=root->rs;
	root->rs->update();
	root->update();
	for(int i=1;i<=n;i++)
	{
		splay(ptr[i],null);
		rank=root->ls->size;
		if(i^1)
			putchar(' ');
		printf("%d",rank);
		find(root,i,null);
		find(root,rank+2,root);
		root->rs->ls->reverse();
	}
}
