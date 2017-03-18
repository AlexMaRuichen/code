#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=500010;
int n,m;
struct Splay
{
	Splay *ls,*rs,*fa;
	int color,size,lcolor,rcolor,same,cnt;
	bool rev;
	Splay(){};
	Splay(int x);
	void update();
	void push_down();
	void reverse();
	void modify(int x);
	void* operator new(size_t);
}*null=new Splay(0),*root=null,Tdata[maxn];
bool flag;
Splay :: Splay(int x)
{
	cnt=size=flag?1:0;
	color=lcolor=rcolor=x;
	rev=false;
	ls=rs=fa=null;
}
void Splay :: update()
{
	size=ls->size+rs->size+1;
	lcolor=ls->lcolor?ls->lcolor:color;
	rcolor=rs->rcolor?rs->rcolor:color;
	cnt=ls->cnt+rs->cnt+1;
	if(ls->rcolor==color&&color==rs->lcolor)
		cnt-=2;
}
void Splay :: push_down()
{
	if(same)
	{
		ls->modify(same);
		rs->modify(same);
		same=0;
	}
	if(rev)
	{
		ls->reverse();
		rs->reverse();
		rev=0;
	}
}
void Splay :: reverse()
{
	swap(ls,rs);
	swap(lcolor,rcolor);
	rev^=1;
}
void Splay :: modify(int x)
{
	lcolor=rcolor=color=x;
	cnt=1;
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
int a[maxn];
void insert(Splay *&x,int y,Splay *z)
{
	if(x==null)
	{
		x=new Splay(y);
		x->fa=z;
		splay(x,null);
		return;
	}
	insert(x->rs,y,x);
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
void print(Splay *x)
{
	if(x==null)
		return;
	print(x->ls);
	printf("%d\n",x->color);
	print(x->rs);
}
int pointer=1;
int q;
int main()
{
	freopen("necklace1.in","r",stdin);
	flag=true;
	insert(root,0,null);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),insert(root,a[i],null);
	insert(root,0,null);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		static char s[maxn];
		static int x,y,ans;
		scanf("%s",s);
		if(s[1]=='S')
		{
			scanf("%d%d",&x,&y);
			find(root,x,null);
			find(root,y+2,root);
			ans=root->rs->ls->cnt;
			if(root->rs->ls->rcolor==root->rs->ls->lcolor)
				--ans;
			printf("%d\n",max(ans,1));
		}
		else if(s[0]=='R')
		{
			scanf("%d",&x);
			pointer=(pointer+x)%n;
			pointer=!pointer?n:pointer;
		}
		else if(s[0]=='F')
		{
			find(root,pointer+1,null);
			root->reverse();
		}
		else if(s[0]=='S')
		{
			scanf("%d%d",&x,&y);
			if(x>y)
				swap(x,y);
			find(root,x+1,null);
			find(root,y+1,root);
			swap(root->ls,root->rs->ls);
			root->fa=root->rs;
			root->rs=root->rs->rs;
			root->rs->rs->fa=root;
			root->rs->rs=root;
			root=root->fa;
			root->fa=null;
			root->rs->update();
			root->update();
		}
		else if(s[0]=='P')
		{
			scanf("%d%d%d",&x,&y,&ans);
			if(x>y)
				swap(x,y);
			find(root,x,null);
			find(root,y+2,root);
			root->rs->ls->modify(ans);
			root->rs->update();
			root->update();
		}
		else if(s[0]=='C')
		{
			find(root,pointer+1,null);
			ans=root->cnt;
			if(root->lcolor==root->rcolor)
				--ans;
			printf("%d\n",max(ans,1));
		}
	}
}
