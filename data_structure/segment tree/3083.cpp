#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=100010;
typedef unsigned int uint;
struct seg_tree
{
	seg_tree *ls,*rs;
	uint mn,lazy;
	seg_tree(){ls=rs=NULL,mn=~0u,lazy=0;}
	void push_down()
	{
		if(lazy)
		{
			ls->lazy=ls->mn=rs->lazy=rs->mn=lazy;
			lazy=0;
		}	
	}
	void update()
	{
		mn=min(ls?ls->mn:~0u,rs?rs->mn:~0u);
	}
	void* operator new(size_t)
	{
		static seg_tree *l,*r;
		if(l==r)
			r=(l=new seg_tree[1<<15])+(1<<15);
		return l++;	
	}
}*root;
void insert(seg_tree *&x,int p,uint v,int l,int r)
{
	if(!x)
		x=new seg_tree();
	if(l==r)
	{
		x->mn=v;
		return;
	}
	int mid=l+r>>1;
	mid>=p?insert(x->ls,p,v,l,mid):insert(x->rs,p,v,mid+1,r);
	x->update();
}
uint query(seg_tree *x,int l,int r,int L,int R)
{
	if(l==L&&r==R)
		return x->mn;
	x->push_down();
	int mid=L+R>>1;
	if(mid>=r)
		return query(x->ls,l,r,L,mid);
	else if(mid<l)
		return query(x->rs,l,r,mid+1,R);
	else
		return min(query(x->ls,l,mid,L,mid),query(x->rs,mid+1,r,mid+1,R));
}
void modify(seg_tree *x,uint v,int l,int r,int L,int R)
{
	if(l==L&&r==R)
	{
		x->mn=x->lazy=v;
		return;
	}
	x->push_down();
	int mid=L+R>>1;
	if(mid>=r)
		modify(x->ls,v,l,r,L,mid);
	else if(mid<l)
		modify(x->rs,v,l,r,mid+1,R);
	else
		modify(x->ls,v,l,mid,L,mid),
		modify(x->rs,v,mid+1,r,mid+1,R);
	x->update();
}
struct edge
{
	int to;
	edge *next;
	edge(){}
	edge(int to,edge *next):to(to),next(next){}
	void* operator new(size_t)
	{
		static edge *l,*r;
		if(l==r)
			r=(l=new edge[1<<15])+(1<<15);
		return l++;
	}
}*head[maxn];
void add(int x,int y)
{
	head[x]=new edge(y,head[x]);
	head[y]=new edge(x,head[y]);
}
int fa[maxn];
int size[maxn];
int pos[maxn];
int top[maxn];
int son[maxn];
int dep[maxn];
void dfs_son(int x)
{
	size[x]=1;
	for(edge *p=head[x];p;p=p->next)
		if(p->to^fa[x])
			fa[p->to]=x,
			dep[p->to]=dep[x]+1,
			dfs_son(p->to),
			size[x]+=size[p->to],
			son[x]=size[p->to]>size[son[x]]?p->to:son[x];
}
void dfs_top(int x,int t)
{
	static int cnt;
	pos[x]=++cnt;
	top[x]=t;
	if(son[x])
		dfs_top(son[x],t);
	for(edge *p=head[x];p;p=p->next)
		if(p->to^fa[x]&&p->to^son[x])
			dfs_top(p->to,p->to);
}
int n,m;
void modify(int x,int y,uint v)
{
	while(top[x]^top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		modify(root,v,pos[top[x]],pos[x],1,n);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	modify(root,v,pos[x],pos[y],1,n);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	int oroot=20000612%n+1;
	dfs_son(oroot);
	dfs_top(oroot,oroot);
	for(int i=1;i<=n;i++)
	{
		static uint x;
		scanf("%u",&x);
		insert(root,pos[i],x,1,n);
	}
	int cap;
	scanf("%d",&cap);
	while(m--)
	{
		static int opt,x,y,id;
		static uint v;
		scanf("%d",&opt);
		if(opt==1)
			scanf("%d",&cap);
		else if(opt==2)
		{
			scanf("%d%d%u",&x,&y,&v);
			modify(x,y,v);
		}
		else
		{
			scanf("%d",&id);
			if(id==cap)
				printf("%u\n",query(root,1,n,1,n));
			else if(pos[cap]>=pos[id]&&pos[cap]<=pos[id]+size[id]-1)
			{
				for(edge *p=head[id];p;p=p->next)
					if(pos[cap]>=pos[p->to]&&pos[cap]<=pos[p->to]+size[p->to]-1&&p->to^fa[id])
					{
						printf("%u\n",min(query(root,1,pos[p->to]-1,1,n),
										  pos[p->to]+size[p->to]<=n?query(root,pos[p->to]+size[p->to],n,1,n):~0u));
						break;
					}
			}
			else 
				printf("%u\n",query(root,pos[id],pos[id]+size[id]-1,1,n));
		}
	}
}
