#include <stdio.h>
#include <map>
#include <queue>
#include <string.h>
#include <algorithm>
#define min(a,b) (a)<(b)?(a):(b)
using namespace std;
const int maxn=3e5+10;
typedef unsigned int uint;
char s[15];
int n;
uint BKDR_hash(char *s)
{
	static uint num,seed=29;
	num=0;
	char *str=s;
	while(*str)
		num=num*seed+*(str++);
	return num;
}
int tot;
map <uint,int> hash;
struct Splay
{
	Splay *ls,*rs,*fa;
	char name[15];
	long long score;
	int size;
	Splay(){}
	Splay(long long x,char *s);
	void update()
	{
		size=ls->size+rs->size+1;
	}
	void* operator new(size_t);
}*ptr[maxn],Tdata[maxn],*null=new Splay(0,""),*root=null;
queue <Splay*> q;
void* Splay :: operator new(size_t)
{
	static Splay *p=Tdata,*r;
	if(q.empty())
		r=p++;
	else
		r=q.front(),q.pop();
	return r;
}
Splay :: Splay(long long x,char *s)
{
	ls=rs=fa=null;
	size=null?1:0;
	strcpy(name,s);
	score=x;
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
	if(y==root)
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
void insert(Splay* &x,long long y,char* s,Splay *z)
{
	if(x==null)
	{
		x=new Splay(y,s);
		x->fa=z;
		splay(x,null);
		return;
	}
	if(y>x->score)
		insert(x->ls,y,s,x);
	else
		insert(x->rs,y,s,x);
}
bool flag;
void print(Splay *x)
{
	if(x==null)
		return;
	print(x->ls);
	if(!flag)
		flag=true,printf("%s",x->name);
	else
		printf(" %s",x->name);
	print(x->rs);
}
int main()
{
	scanf("%d",&n);
	insert(root,-(~0ull>>2),"",null);
	insert(root,~0ull>>2,"",null);
	for(int i=1;i<=n;i++)
	{
		static uint hash_val,hash_num;
		char ch=getchar(),*str=s;
		long long num=0;
		while(ch!='?'&&ch!='+')
			ch=getchar();
		while(ch!=' '&&ch!='\r'&&ch!='\n')
			*(str++)=ch,ch=getchar();
		*(str)=0;
		if(s[0]=='+')
		{

			while(ch<'0'||ch>'9')
				ch=getchar();
			while(ch>='0'&&ch<='9')
				num=(num<<1)+(num<<3)+ch-'0',ch=getchar();
			hash_val=BKDR_hash(s+1);
			hash_num=hash[hash_val];
			if(hash_num)
			{
				splay(ptr[hash_num],null);
				int r=root->ls->size;
				find(root,r,null);
				find(root,r+2,root);
				q.push(root->rs->ls);
				root->rs->ls=null;
				root->rs->update();
				root->update();
				insert(root,num,s+1,null);
				ptr[hash_num]=root;
			}
			else
			{
				insert(root,num,s+1,null);
				hash[hash_val]=++tot;
				ptr[tot]=root;	
			}
		}
		else if(s[0]=='?')
		{
			if(s[1]>='0'&&s[1]<='9')
			{
				char *str=s+1;
				while(*str)
					num=(num<<1)+(num<<3)+*(str++)-'0';
				find(root,num,null);
				find(root,min(num+11,root->size),root);
				flag=false;
				print(root->rs->ls);
				puts("");
			}
			else
			{
				hash_val=BKDR_hash(s+1);
				splay(ptr[hash[hash_val]],null);
				printf("%d\n",root->ls->size);
			}
		}
	}
}
