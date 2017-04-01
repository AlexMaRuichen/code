#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=100010;
const int N=1e9;
struct point
{
	int x,y;
}p[maxn];
bool cmpx(const point &a,const point &b)
{
	return a.x<b.x;
}
bool cmpy(const point &a,const point &b)
{
	return a.y<b.y;
}
struct kdt
{
	kdt *ls,*rs;
	point p;
	int xmx,xmn,ymx,ymn;
	int size;
	kdt(){}
	kdt(const point &p):p(p)
	{
		xmx=xmn=p.x;
		ymx=ymn=p.y;
		size=1;
	}
	void update()
	{
		size=1;
		if(ls)
		{
			xmx=max(xmx,ls->xmx);
			ymx=max(ymx,ls->ymx);
			xmn=min(xmn,ls->xmn);
			ymn=min(ymn,ls->ymn);
			size+=ls->size;
		}
		if(rs)
		{
			xmx=max(xmx,rs->xmx);
			ymx=max(ymx,rs->ymx);
			xmn=min(xmn,rs->xmn);
			ymn=min(ymn,rs->ymn);
			size+=rs->size;
		}
	}
	void* operator new(size_t);
}**mark;
queue <kdt*> q;
void* kdt :: operator new(size_t)
{
	static kdt *l,*r,*g;
	if(!q.empty())
	{
		g=q.front();
		q.pop();
		return g;
	}
	else if(l==r)
		r=(l=new kdt[1<<15])+(1<<15);
	return l++;
}
bool oflag;
int tot;
void insert(kdt *&x,const point &p,bool flag)
{
	if(!x)
	{
		x=new kdt(p);
		return;
	}
	if((flag?cmpy:cmpx)(p,x->p))
		insert(x->ls,p,flag^1);
	else
		insert(x->rs,p,flag^1);
	x->update();
	if(max(x->ls?x->ls->size:0,x->rs?x->rs->size:0)>x->size*4/5)
		mark=&x,oflag=flag;
}
void travel(kdt *x)
{
	if(!x)
		return;
	travel(x->ls);
	travel(x->rs);
	p[++tot]=x->p;
	q.push(x);
}
void build(kdt *&x,int l,int r,bool flag)
{
	if(l>r)
		return;
	int mid=l+r>>1;
	nth_element(p+l,p+mid,p+r+1,flag?cmpy:cmpx);
	x=new kdt(p[mid]);
	build(x->ls,l,mid-1,flag^1);
	build(x->rs,mid+1,r,flag^1);
	x->update();
}
int query(kdt *x,int xmn,int ymn,int xmx,int ymx)
{
	if(x->xmn>=xmn&&x->ymn>=ymn&&x->xmx<=xmx&&x->ymx<=ymx)
		return x->size;
	if(x->xmx<xmn||x->ymx<ymn||x->xmn>xmx||x->ymn>ymx)
		return 0;
	return (x->ls?query(x->ls,xmn,ymn,xmx,ymx):0)
			+(x->rs?query(x->rs,xmn,ymn,xmx,ymx):0)
			+(x->p.x>=xmn&&x->p.x<=xmx&&x->p.y>=ymn&&x->p.y<=ymx);
}
struct chairtree
{
	chairtree *ls,*rs;
	kdt *t;
	chairtree(){ls=rs=NULL,t=NULL;}
	void* operator new(size_t)
	{
		static chairtree *l,*r;
		if(l==r)
			r=(l=new chairtree[1<<15])+(1<<15);
		return l++;
	}
}*root=new chairtree();
void insert(chairtree *&x,const point &v,int p,int l,int r)
{
	if(!x)
		x=new chairtree();
	mark=NULL;
	insert(x->t,v,false);
	if(mark)
	{
		tot=0;
		travel(*mark);
		build(*mark,1,tot,oflag);
	}
	if(l==r)
		return;
	int mid=l+r>>1;
	if(mid>=p)
		insert(x->ls,v,p,l,mid);
	else
		insert(x->rs,v,p,mid+1,r);
}
int query(chairtree *x,int v,int xmn,int ymn,int xmx,int ymx,int l,int r)
{
	if(l==r)
		return l;
	int mid=l+r>>1;
	int t=x->rs?query(x->rs->t,xmn,ymn,xmx,ymx):0;
	if(t>=v)
		return query(x->rs,v,xmn,ymn,xmx,ymx,mid+1,r);
	else
		return query(x->ls,v-t,xmn,ymn,xmx,ymx,l,mid);
}
int Q;
int main()
{
	scanf("%*d%d",&Q);
	while(Q--)
	{
		static int opt,lastans,v,xmn,xmx,ymn,ymx;
		static point p;
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d%d",&p.x,&p.y,&v);
			p.x^=lastans;
			p.y^=lastans;
			insert(root,p,v,1,N);
		}
		else 
		{
			scanf("%d%d%d%d%d",&xmn,&ymn,&xmx,&ymx,&v);
			xmn^=lastans;
			ymn^=lastans;
			xmx^=lastans;
			ymx^=lastans;
			v^=lastans;
			if(query(root->t,xmn,ymn,xmx,ymx)<v)
				lastans=0,puts("NAIVE!ORZzyz.");
			else
				printf("%d\n",lastans=query(root,v,xmn,ymn,xmx,ymx,1,N));
		}
	}
}

