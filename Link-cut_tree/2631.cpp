#include <stdio.h>
#include <algorithm>
using namespace std;
typedef unsigned int uint;
const int maxn=1e5+10;
const int mod=51061;
int n,q;
struct Splay
{
	Splay *ls,*rs,*fa;
	uint sum,size,add,mul,val;
	bool rev;
	Splay(){}
	Splay(int x);
	void reverse();
	void* operator new(size_t);
	void multiply(uint x);
	void plus(uint x);
	void update();
	void push_down();
}*null=new Splay(0),*ptr[maxn],mempool[maxn];
void Splay :: reverse()
{
	if(this==null)
		return;
	rev^=1;
	swap(ls,rs);
}
void Splay :: multiply(uint x)
{
	if(this==null)
		return;
	val=val*x%mod;
	mul=mul*x%mod;
	add=add*x%mod;
	sum=sum*x%mod;
}
void Splay :: plus(uint x)
{
	if(this==null)
		return;
	val=(val+x)%mod;
	add=(add+x)%mod;
	sum=(sum+x*size%mod)%mod;
}
void Splay :: update()
{
	sum=(ls->sum+rs->sum+val)%mod;
	size=ls->size+rs->size+1;
}
void Splay :: push_down()
{
	if(this==null)
		return;
	if(this==fa->ls||this==fa->rs)
		fa->push_down();
	if(mul^1)
	{
		ls->multiply(mul);
		rs->multiply(mul);
		mul=1;
	}
	if(add^0)
	{
		ls->plus(add);
		rs->plus(add);
		add=0;
	}
	if(rev^false)
	{
		ls->reverse();
		rs->reverse();
		rev=false;
	}
}
Splay :: Splay(int x)
{
	ls=rs=fa=null;
	add=0;
	sum=val=x;
	size=x?1:0;
	mul=1;
	rev=false;
}
void* Splay :: operator new(size_t)
{
	static Splay *p=mempool;
	return p++;
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
}
void splay(Splay *x)
{
	Splay *y,*z;
	x->push_down();
	while(x==x->fa->ls||x==x->fa->rs)
	{
		y=x->fa;
		z=y->fa;
		if(x==y->ls)
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
void access(Splay *x)
{
	Splay *y=null;
	while(x!=null)
	{
		splay(x);
		x->rs=y;
		x->update();
		y=x;
		x=x->fa;
	}
}
void move_to_root(Splay *x)
{
	access(x);
	splay(x);
	x->reverse();
}
void link(Splay *x,Splay *y)
{
	move_to_root(x);
	x->fa=y;
}
void cut(Splay *x,Splay *y)
{
	move_to_root(x);
	access(y);
	splay(y);
	x->fa=null;
	y->ls=null;
	y->update();
}
void process_plus(Splay *x,Splay *y,uint z)
{
	move_to_root(x);
	access(y);
	splay(y);
	y->plus(z);
}
void process_mul(Splay *x,Splay *y,uint z)
{
	move_to_root(x);
	access(y);
	splay(y);
	y->multiply(z);
}
void query(Splay *x,Splay *y)
{
	move_to_root(x);
	access(y);
	splay(y);
	printf("%u\n",y->sum);
}
int to[maxn<<1];
int next[maxn<<1];
int head[maxn];
int tot;
void add(int x,int y)
{
	to[++tot]=x;
	next[tot]=head[y];
	head[y]=tot;
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
}
bool v[maxn];
void dfs(int x)
{
	v[x]=true;
	for(int i=head[x];i;i=next[i])
		if(!v[to[i]])
		{
			ptr[to[i]]->fa=ptr[x];
			dfs(to[i]);
		}
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		ptr[i]=new Splay(1);
	for(int i=1;i<n;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1);
	for(int i=1;i<=q;i++)
	{
		static char s[10];
		static uint x,y,z;
		scanf("%s",s);
		if(s[0]=='+')
		{
			scanf("%u%u%u",&x,&y,&z);
			process_plus(ptr[x],ptr[y],z);
		}
		else if(s[0]=='-')
		{
			scanf("%u%u",&x,&y);
			cut(ptr[x],ptr[y]);
			scanf("%u%u",&x,&y);
			link(ptr[x],ptr[y]);
		}
		else if(s[0]=='*')
		{
			scanf("%u%u%u",&x,&y,&z);
			process_mul(ptr[x],ptr[y],z);
		}
		else if(s[0]=='/')
		{
			scanf("%u%u",&x,&y);
			query(ptr[x],ptr[y]);
		}
	}
}
