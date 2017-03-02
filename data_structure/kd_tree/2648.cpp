#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=500010;
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
inline int dis(const point &a,const point &b)
{
	return abs(a.x-b.x)+abs(a.y-b.y);
}
struct kdt
{
	kdt *ls,*rs;
	int xmx,ymx,xmn,ymn;
	point p;
	kdt(){}
	kdt(const point &p):p(p)
	{
		ls=rs=NULL;
		xmx=xmn=p.x;
		ymx=ymn=p.y;
	}
	void update()
	{
		if(ls)
		{
			xmx=max(xmx,ls->xmx);
			xmn=min(xmn,ls->xmn);
			ymx=max(ymx,ls->ymx);
			ymn=min(ymn,ls->ymn);
		}
		if(rs)
		{
			xmx=max(xmx,rs->xmx);
			xmn=min(xmn,rs->xmn);
			ymx=max(ymx,rs->ymx);
			ymn=min(ymn,rs->ymn);
		}
	}
	int dis(const point &p)
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
	void* operator new(size_t)
	{
		static kdt *l,*r;
		if(l==r)
			r=(l=new kdt[1<<15])+(1<<15);
		return l++;
	}
}*root;
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
}
void query(kdt *x,const point &p,int &ans)
{
	ans=min(dis(p,x->p),ans);
	int l=x->ls?x->ls->dis(p):~0u>>1;
	int r=x->rs?x->rs->dis(p):~0u>>1;
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
		static int ans,opt;
		static point a;
		scanf("%d%d%d",&opt,&a.x,&a.y);
		if(opt==1)
			insert(root,a,false);
		else
		{
			query(root,a,ans=~0u>>1);
			printf("%d\n",ans);
		}
	}
}
