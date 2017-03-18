#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1000010;
char getc()
{
	static const int len=1<<15;
	static char buf[len],*s,*t;
	if(s==t)
	{
		t=(s=buf)+fread(buf,1,len,stdin);
		if(s==t)
			return EOF;
	}
	return *s++;
}
void read(register int &x)
{
	static char ch;
	static bool flag;
	x=flag=0;
	while(ch<'0')
	{
		if(ch=='-')
			flag=true;
		ch=getc();
	}
	while(ch>='0')
		x=(x<<1)+(x<<3)+ch-'0',ch=getc();
	flag?x=-x:1;
}
void read(register char *s)
{
	static char ch;
	while(ch<'A')
		ch=getc();
	while(ch>='A')
		*s++=ch,ch=getc();
}
struct heap
{
	heap *ls,*rs;
	int val,pos,dis;
	heap();
	heap(const int &p,const int &v);
	void* operator new(size_t);
}nil,*null=&nil,*node[maxn],mem[maxn];
void* heap :: operator new(size_t)
{
	static heap *p=mem;
	return p++;
}
heap :: heap()
{
	ls=rs=this;
	pos=val=0;
	dis=-1;
}
heap :: heap(const int &p,const int &v)
{
	ls=rs=null;
	pos=p;
	val=v;
	dis=0;
}
heap* merge(heap *x,heap *y)
{
	if(x==null)
		return y;
	if(y==null)
		return x;
	if(x->val>y->val)
		swap(x,y);
	x->rs=merge(x->rs,y);
	if(x->ls->dis>x->rs->dis)
		swap(x->ls,x->rs);
	x->dis=x->rs->dis+1;
	return x;
}
bool dead[maxn];
int fa[maxn];
int rank[maxn];
int getfa(int x)
{
	static int a,b;
	a=x;
	while(a^fa[a])
		a=fa[a];
	while(x^fa[x])
		b=fa[x],fa[x]=a,x=b;
	return a;
}
void merge(int x,int y)
{
	x=getfa(x);
	y=getfa(y);
	if(x==y)
		return;
	if(rank[x]>rank[y])
		swap(x,y);
	else if(rank[x]==rank[y])
		++rank[y];
	fa[x]=y;
	node[y]=merge(node[y],node[x]);
}
int n,m;
int main()
{
	read(n);
	for(int i=1,x;i<=n;i++)
		read(x),node[i]=new heap(i,x),fa[i]=i;
	read(m);
	for(int i=1,x,y;i<=m;i++)
	{
		static char s[5];
		read(s);
		if(s[0]=='M')
		{
			read(x);
			read(y);
			if(dead[x]||dead[y])
				continue;
			merge(x,y);
		}
		else
		{
			read(x);
            if(dead[x])  
            {  
                puts("0");  
                continue;  
            }  
            printf("%d\n",node[x=getfa(x)]->val);  
            dead[node[x]->pos]=true;  
            node[x]=merge(node[x]->ls,node[x]->rs);  

		}
	}
}