#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct Treap{
	Treap *ls,*rs;
	int key,num;
	Treap(int x);
}*null=new Treap(0),*root=null;
Treap :: Treap(int x)
{
	ls=rs=null;
	key=rand();
	num=x;
}
void Zig(Treap *&x)
{
	Treap *y=x->ls;
	x->ls=y->rs;
	y->rs=x;
	x=y;
}
void Zag(Treap *&x)
{
	Treap *y=x->rs;
	x->rs=y->ls;
	y->ls=x;
	x=y;
}
void Insert(Treap *&x,int y)
{
	if(x==null)
	{
		x=new Treap(y);
		return ;
	}
	if(y==x->num)
		return ;
	if(y<x->num)
	{
		Insert(x->ls,y);
		if(x->ls->key>x->key)
			Zig(x);
	}
	else
	{
		Insert(x->rs,y);
		if(x->rs->key>x->key)
			Zag(x);
	}
}
int Pred(Treap *x,int y)
{
	if(x==null)
		return 0xefefefef;
	if(y<x->num)
		return Pred(x->ls,y);
	return max( x->num , Pred(x->rs,y) );
}
int Secc(Treap *x,int y)
{
	if(x==null)
		return 0x7fffffff;
	if(y>x->num)
		return Secc(x->rs,y);
	return min( x->num , Secc(x->ls,y) );
}
int n,ans;
int main()
{
	int i,x;
	srand(19980402);
	while(~scanf("%d",&n) )
	{
		root=null;ans=0;
		for(i=1;i<=n;i++)
		{
			if(scanf("%d",&x)==EOF)x=0;
			int pred=Pred(root,x),secc=Secc(root,x);
				if(i^1)
				ans+=min( x-pred , secc-x );
			else
				ans+=x;
			Insert(root,x);
		}	
		cout<<ans<<endl;
	}
}
