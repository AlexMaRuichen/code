#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=1000010;
const int inf=1e9;
struct point
{
	int x,y;
}p[maxn];
int tot;
inline int dis(const point &a,const point &b)
{
	return abs(a.x-b.x)+abs(a.y-b.y);
}
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
	int xmn,xmx,ymn,ymx,size;
	kdt(){}
	kdt(const point &p):p(p)
	{
		ls=rs=NULL;
		xmn=xmx=p.x;
		ymn=ymx=p.y;
		size=1;
	}
	int mndis(const point &p)
	{
		int ans=0;
		if(p.x<xmn)
			ans+=xmn-p.x;
		if(p.x>xmx)
			ans+=p.x-xmx;
		if(p.y<ymn)
			ans+=ymn-p.y;
		if(p.y>ymx)
			ans+=p.y-ymx;
		return ans;
	}
	void update()
	{
		size=1;
		if(ls)
		{
			xmn=min(xmn,ls->xmn);
			xmx=max(xmx,ls->xmx);
			ymn=min(ymn,ls->ymn);
			ymx=max(ymx,ls->ymx);
			size+=ls->size;
		}
		if(rs)
		{
			xmn=min(xmn,rs->xmn);
			xmx=max(xmx,rs->xmx);
			ymn=min(ymn,rs->ymn);
			ymx=max(ymx,rs->ymx);
			size+=rs->size;
		}
	}
	void* operator new (size_t);
}*root,**mark;
bool oflag;
queue <kdt*> q;
void* kdt::operator new (size_t)
{
	static kdt mem[maxn],*p=mem,*g;
	if(!q.empty())
	{
		g=q.front();
		q.pop();
		return g;
	}
	return p++;
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
void query(kdt *x,const point &p,int &ans)
{
	ans=min(ans,dis(p,x->p));
	int l=x->ls?x->ls->mndis(p):inf;
	int r=x->rs?x->rs->mndis(p):inf;
	if(l<r)
	{
		if(x->ls&&l<ans)
			query(x->ls,p,ans);
		if(x->rs&&r<ans)
			query(x->rs,p,ans);
	}
	else
	{
		if(x->rs&&r<ans)
			query(x->rs,p,ans);
		if(x->ls&&l<ans)
			query(x->ls,p,ans);
	}
}
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].x,&p[i].y);
	build(root,1,n,false);
	while(m--)
	{
		static int opt,ans;
		static point p;
		scanf("%d%d%d",&opt,&p.x,&p.y);
		if(opt==1)
		{
			mark=NULL;
			insert(root,p,false);
			if(mark)
			{
				tot=0;
				travel(*mark);
				build(*mark,1,tot,oflag);
			}
		}
		else
		{
			query(root,p,ans=inf);
			printf("%d\n",ans);
		}
	}
}
