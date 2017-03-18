#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
struct Splay
{
	Splay *ls,*rs,*fa;
	ll size,val;
	void update()
	{
		size=ls->size+rs->size+1;
	}
	Splay(ll x);
}*null=new Splay(0),*root=null;
Splay :: Splay(ll x)
{
	ls=rs=fa=null;
	size=x?1:0;
	val=x;
}
int sta;
void zig(Splay *x)
{
	Splay *y=x->fa;
	y->ls=x->rs;
	x->rs->fa=y;
	x->rs=y;
	x->fa=y->fa;
	if(y==y->fa->ls)
		y->fa->ls=x;
	else
		y->fa->rs=x;
	y->fa=x;
	y->update();
	if(root==y)
		root=x;
}
void zag(Splay *x)
{
	Splay *y=x->fa;
	y->rs=x->ls;
	x->ls->fa=y;
	x->ls=y;
	x->fa=y->fa;
	if(y==y->fa->ls)
		y->fa->ls=x;
	else
		y->fa->rs=x;
	y->fa=x;
	y->update();
	if(root==y)
		root=x;
}
void splay(Splay *x,Splay *t)
{
	static Splay *y,*z;
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
				zig(y),zig(x);
			else
				zig(x),zag(x);
		}
		else
		{
			if(y==z->rs)
				zag(y),zag(x);
			else
				zag(x),zig(x);
		}
	}
	x->update();
}
void insert(Splay* &x,ll y,Splay *z)
{
	if(x==null)
	{
		x=new Splay(y);
		x->fa=z;
		splay(x,null);
		return;
	}
	if(x->val>y)
		insert(x->ls,y,x);
	else
		insert(x->rs,y,x);
}
void q_pre(Splay *x,ll y,Splay *z)
{
	Splay *ans=x;
	while(x!=null)
	{
		if(x->val<=y)
			ans=x,x=x->rs;
		else if(x->val>y)
			x=x->ls;
	}
	splay(ans,z);
}
void q_suc(Splay *x,ll y,Splay *z)
{
	Splay *ans=x;
	while(x!=null)
	{
		if(x->val>=y)
			ans=x,x=x->ls;
		else if(x->val<y)
			x=x->rs;
	}
	splay(ans,z);
}
void find(Splay *x,int y,Splay *z)
{
	while(x->val!=y)
		if(x->val>y)
			x=x->ls;
		else
			x=x->rs;
	splay(x,z);
}
void print(Splay *x)
{
	if(x==null)
		return;
	printf("ls:%lld %lld rs:%lld size:%lld\n",x->ls->val,x->val,x->rs->val,x->size);
	print(x->ls);
	print(x->rs);
}
ll ans;
int n;
int main()
{
	scanf("%d",&n);
	while(n--)
	{	
		static ll x,t,num,g;
		scanf("%lld%lld",&g,&x);
		if(g==sta)
			insert(root,x,null);
		else if(root->size)
		{
			t=~0ull>>1;
			if(root->size==1)
			{
				ans=(ans+abs(root->val-x))%1000000;
				root=null;
				continue;
			}
			q_pre(root,x,null);
			if(abs(root->val-x)<t)
				t=abs(root->val-x),num=root->val;
			q_suc(root,x,null);
			if(abs(root->val-x)<t)
				t=abs(root->val-x),num=root->val;
			ans=(ans+t)%1000000;
			find(root,num,null);
			if(root->ls==null&&root->rs==null)
				root=null;
			else if(root->ls==null)
				root->rs->fa=null,root=root->rs,root->update();
			else if(root->rs==null)
				root->ls->fa=null,root=root->ls,root->update();
			else
			{
				Splay *y=root->ls;
				while(y->rs!=null)
					y=y->rs;
				splay(y,root);
				root->rs->update();
				root->rs->fa=root->ls;
				root->ls->rs=root->rs;
				root->ls->fa=null;
				root=root->ls;
				root->update();
			}
		}
		else
			sta=g,insert(root,x,null);
	}
	printf("%lld\n",ans);
}
