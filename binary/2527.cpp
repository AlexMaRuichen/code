#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=3e5+10;
typedef long long ll;
const int inf=1e9;
char getc()
{
	static const int len=1<<15;
	static char buf[len],*s=buf,*t=buf;
	if(s==t)
	{
		t=(s=buf)+fread(buf,1,len,stdin);
		if(s==t)
			return EOF;
	}
	return *(s++);
}
void read(register int &x)
{
	static char ch=getc();
	x=0;
	while(ch<'0'||ch>'9')
		ch=getc();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+ch-'0',ch=getc();
}
struct seg_tree
{
	seg_tree *ls,*rs;
	ll val;
	seg_tree(){ls=rs=NULL,val=0;}
	void* operator new(size_t)
	{
		static seg_tree *l=NULL,*r=NULL;
		if(l==r)
			r=(l=new seg_tree[1<<15])+(1<<15);
		return l++;
	}
}*root;
void build(seg_tree *&x,int l,int r)
{
	x=new seg_tree();
	if(l==r)
		return;
	int mid=l+r>>1;
	build(x->ls,l,mid);
	build(x->rs,mid+1,r);
}
ll query(seg_tree *x,int p,int L,int R)
{
	if(L==R)
		return x->val;
	int mid=L+R>>1;
	if(mid>=p)
		return x->val+query(x->ls,p,L,mid);
	else
		return x->val+query(x->rs,p,mid+1,R);
}
void modify(seg_tree *x,int v,int l,int r,int L,int R)
{
	if(l==L&&r==R)
	{
		x->val+=v;
		return;
	}
	int mid=L+R>>1;
	if(mid>=r)
		modify(x->ls,v,l,r,L,mid);
	else if(mid<l)
		modify(x->rs,v,l,r,mid+1,R);
	else
		modify(x->ls,v,l,mid,L,mid),
		modify(x->rs,v,mid+1,r,mid+1,R);
}
int q[maxn];
struct mod
{
	int l,r,val;
}modi[maxn];
int n,m,k;
struct edge
{
	int to;
	edge *next;
	edge(){}
	edge(int to,edge *next):to(to),next(next){}
	void* operator new(size_t)
	{
		static edge *l=NULL,*r=NULL;
		if(l==r)
			r=(l=new edge[1<<15])+(1<<15);
		return l++;
	}
}*head[maxn];
void add(int x,int y)
{
	head[x]=new edge(y,head[x]);
}
int g[maxn];
int ans[maxn];
void bin(int l,int r,int L,int R)
{
	static int bak[maxn];
	static int cur;
	if(L>R)
		return;
	if(l==r)
	{
		for(int i=L;i<=R;i++)
			ans[q[i]]=l;
		return;
	}
	int mid=l+r>>1;
	while(cur<mid)
	{
		++cur;
		if(modi[cur].l<=modi[cur].r)
			modify(root,modi[cur].val,modi[cur].l,modi[cur].r,1,m);
		else
			modify(root,modi[cur].val,1,modi[cur].r,1,m),
			modify(root,modi[cur].val,modi[cur].l,m,1,m);
	}
	while(cur>mid)
	{
		if(modi[cur].l<=modi[cur].r)
			modify(root,-modi[cur].val,modi[cur].l,modi[cur].r,1,m);
		else
			modify(root,-modi[cur].val,1,modi[cur].r,1,m),
			modify(root,-modi[cur].val,modi[cur].l,m,1,m);
		--cur;
	}
	int left=L,right=R;
	for(int i=L;i<=R;i++)
	{
		int x=q[i];
		ll ans=0;
		for(edge *p=head[x];p;p=p->next)
		{
			ans+=query(root,p->to,1,m);
			if(ans>inf)
				ans=inf;
		}
		if(ans>=g[x])
			bak[left++]=x;
		else
			bak[right--]=x;
	}
	memcpy(q+L,bak+L,sizeof(int)*(R-L+1));
	bin(l,mid,L,left-1);
	bin(mid+1,r,right+1,R);
}
int main()
{
	read(n);
	read(m);
	for(int i=1;i<=m;i++)
	{
		static int x;
		read(x);
		add(x,i);
	}
	for(int i=1;i<=n;i++)
		read(g[i]),q[i]=i;
	build(root,1,m);
	read(k);
	for(int i=1;i<=k;i++)
	{
		read(modi[i].l);
		read(modi[i].r);
		read(modi[i].val);
	}
	bin(1,k+1,1,n);
	for(int i=1;i<=n;i++)
		if(ans[i]<=k)
			printf("%d\n",ans[i]);
		else
			puts("NIE");
}
