#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=500010;
const int inf=1e9;
struct point
{
	int x,y;
}p[maxn];
inline bool operator != (const point &a,const point &b)
{
	return a.x^b.x||a.y^b.y;
}
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
	int xmx,xmn,ymx,ymn;
	kdt(){}
	kdt(const point &p):p(p)
	{
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
	int mxdis(const point &p)
	{
		int ans=0;
		ans+=max(p.x-xmn,xmx-p.x);
		ans+=max(p.y-ymn,ymx-p.y);
		return ans;
	}
	void* operator new(size_t)
	{
		static kdt mempool[maxn],*p=mempool;
		return p++;
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
void qmx(kdt *x,const point &p,bool flag,int &ans)
{
	ans=max(ans,dis(p,x->p));
	int l=x->ls?x->ls->mxdis(p):-inf;
	int r=x->rs?x->rs->mxdis(p):-inf;
	if(l>r)
	{
		if(x->ls&&l>ans)
			qmx(x->ls,p,flag^1,ans);
		if(x->rs&&r>ans)
			qmx(x->rs,p,flag^1,ans);
	}
	else
	{
		if(x->rs&&r>ans)
			qmx(x->rs,p,flag^1,ans);
		if(x->ls&&l>ans)
			qmx(x->ls,p,flag^1,ans);
	}
}
void qmn(kdt *x,const point &p,bool flag,int &ans)
{
	if(p!=x->p)
		ans=min(ans,dis(p,x->p));
	int l=x->ls?x->ls->mndis(p):inf;
	int r=x->rs?x->rs->mndis(p):inf;
	if(l<r)
	{
		if(x->ls&&l<ans)
			qmn(x->ls,p,flag^1,ans);
		if(x->rs&&r<ans)
			qmn(x->rs,p,flag^1,ans);
	}
	else
	{
		if(x->rs&&r<ans)
			qmn(x->rs,p,flag^1,ans);
		if(x->ls&&l<ans)
			qmn(x->ls,p,flag^1,ans);
	}
}
int main()
{
	int n,ans=inf;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].x,&p[i].y);
	build(root,1,n,false);
	for(int i=1;i<=n;i++)
	{
		static int mx,mn;
		qmx(root,p[i],false,mx=-inf);
		qmn(root,p[i],false,mn=inf);
		ans=min(ans,mx-mn);
	}
	printf("%d\n",ans);
}
