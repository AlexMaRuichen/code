#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define M 300300
using namespace std;
struct abcd{
	abcd *fa,*ls,*rs;
	int num,xor_sum;
	bool rev_mark;
	abcd(int x);
	void Reverse();
	void Push_Up();
	void Push_Down();
}*null=new abcd(0),*tree[M];
abcd :: abcd(int x)
{
	fa=ls=rs=null;
	num=x;xor_sum=x;
	rev_mark=0;
}
void abcd :: Reverse()
{
	swap(ls,rs);
	rev_mark^=1;
}
void abcd :: Push_Up()
{
	xor_sum=ls->xor_sum^rs->xor_sum^num;
}
void abcd :: Push_Down()
{
	if(fa->ls==this||fa->rs==this)
		fa->Push_Down();
	if(rev_mark)
	{
		ls->Reverse();
		rs->Reverse();
		rev_mark=0;
	}
}
void Zig(abcd *x)
{
	abcd *y=x->fa;
	y->ls=x->rs;
	x->rs->fa=y;
	x->rs=y;
	x->fa=y->fa;
	if(y==y->fa->ls)
		y->fa->ls=x;
	else if(y==y->fa->rs)
		y->fa->rs=x;
	y->fa=x;
	y->Push_Up();
}
void Zag(abcd *x)
{
	abcd *y=x->fa;
	y->rs=x->ls;
	x->ls->fa=y;
	x->ls=y;
	x->fa=y->fa;
	if(y==y->fa->ls)
		y->fa->ls=x;
	else if(y==y->fa->rs)
		y->fa->rs=x;
	y->fa=x;
	y->Push_Up();
}
void Splay(abcd *x)
{
	x->Push_Down();
	while(x->fa->ls==x||x->fa->rs==x)
	{
		abcd *y=x->fa,*z=y->fa;
		if(x==y->ls)
		{
			if(y==z->ls)
				Zig(y);
			Zig(x);
		}
		else
		{
			if(y==z->rs)
				Zag(y);
			Zag(x);
		}
	}
	x->Push_Up();
}
void Access(abcd *x)
{
	abcd *y=null;
	while(x!=null)
	{
		Splay(x);
		x->rs=y;
		x->Push_Up();
		y=x;
		x=x->fa;
	}
}
void Move_To_Root(abcd *x)
{
	Access(x);
	Splay(x);
	x->Reverse();
}
abcd* Find_Root(abcd *x)
{
	for(;x->fa!=null;x=x->fa);
	return x;
}
void Link(abcd *x,abcd *y)
{
	if( Find_Root(x)==Find_Root(y) )
		return ;
	Move_To_Root(x);
	x->fa=y;
}
void Cut(abcd *x,abcd *y)
{
	if( x==y || Find_Root(x)!=Find_Root(y) )
		return ;
	Move_To_Root(x);
	Access(y);
	Splay(y);
	if(y->ls==x)
	{
		x->fa=null;
		y->ls=null;
		y->Push_Up();
	}
}
void Change(abcd *x,int y)
{
	Splay(x);
	x->num=y;
	x->Push_Up();
}
int Query(abcd *x,abcd *y)
{
	Move_To_Root(x);
	Access(y);
	Splay(y);
	return y->xor_sum;
}
int n,m;
int main()
{
	int i,x,y,p;
	cin>>n>>m;
	for(i=1;i<=n;i++)
		scanf("%d",&x),tree[i]=new abcd(x);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&p,&x,&y);
		switch(p)
		{
			case 0:printf("%d\n", Query(tree[x],tree[y]) );break;
			case 1:Link(tree[x],tree[y]);break;
			case 2:Cut(tree[x],tree[y]);break;
			case 3:Change(tree[x],y); break;
		}
	}
	return 0;
}


