#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn=1024*1024*2+10;
int n;
char s[maxn];
char *str;
void readstring(int x=-1)
{
	char ch=getchar();
	str=s;
	while(ch<32||ch>126)
		ch=getchar();
	if(x^-1)
		while(x--)
		{
			if(ch=='\n'||ch=='\r')
				++x;
			else
				*(++str)=ch;
			ch=getchar();
		}
	else
	{
		while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
			*(str++)=ch,ch=getchar();
		*str=0;		
	}
}
struct Splay
{
	Splay *ls,*rs,*fa;
	char val;
	int size;
	Splay(){};
	Splay(char x);
	void update()
	{
		size=ls->size+rs->size+1;	
	}
	void del();
	void* operator new(size_t);
}*null=new Splay(0),*root=null,Tdata[maxn];
queue <Splay*> q;
Splay :: Splay(char x)
{
	val=x;
	size=x?1:0;
	ls=rs=fa=null;
}
void Splay :: del()
{
	if(this==null)
		return;
	ls->del();
	rs->del();
	q.push(this);
}
void* Splay :: operator new(size_t)
{
	static Splay *p=Tdata,*r;
	if(q.empty())
		r=p++;
	else
		r=q.front(),q.pop();
	return r;
}
void zig(Splay *x)
{
	Splay *y=x->fa;
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
Splay* build(int l,int r)
{
	if(l>r)
		return null;
	int mid=l+r>>1;
	Splay *x=new Splay(s[mid]);
	x->ls=build(l,mid-1);
	x->rs=build(mid+1,r);
	x->ls->fa=x->rs->fa=x;
	x->update();
	return x;
}
int ptr=1;
int tot;
void insert()
{
	scanf("%d",&tot);
	readstring(tot);
	find(root,ptr,null);
	find(root,ptr+1,root);
	root->rs->ls=build(1,tot);
	root->rs->ls->fa=root->rs;
	root->rs->update();
	root->update();
}
void move()
{
	scanf("%d",&tot);
	ptr=tot+1;
}
void del()
{
	scanf("%d",&tot);
	find(root,ptr,null);
	find(root,ptr+tot+1,root);
	root->rs->ls->del();
	root->rs->ls=null;
	root->rs->update();
	root->update();
}
void print(Splay* x)
{
	if(x==null)
		return;
	print(x->ls);
	putchar(x->val);
	print(x->rs);
}
void get()
{
	scanf("%d",&tot);
	find(root,ptr,null);
	find(root,ptr+tot+1,root);
	print(root->rs->ls);
	puts("");
}
void prev()
{
	--ptr;
}
void next()
{
	++ptr;
}
int main()
{
	scanf("%d",&n);
	root=new Splay('A');
	root->rs=new Splay('A');
	root->rs->fa=root;
	root->update();
	for(int i=1;i<=n;i++)
	{
		readstring();
		if(!strcmp(s,"Insert"))
			insert();
		else if(!strcmp(s,"Move"))
			move();
		else if(!strcmp(s,"Delete"))
			del();
		else if(!strcmp(s,"Get"))
			get();
		else if(!strcmp(s,"Prev"))
			prev();
		else
			next();
	}
}
