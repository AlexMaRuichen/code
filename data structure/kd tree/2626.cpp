#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
const ll inf=1e18;
struct point
{
	int x,y,id;
	point(int x=0,int y=0):x(x),y(y){}
}p[maxn];
typedef pair<ll,int> pa;
bool cmp(const pa &a,const pa &b)
{
	return a.first^b.first?a.first>b.first:a.second<b.second;
}
pa heap[maxn];
bool cmpx(const point &a,const point &b)
{
	return a.x<b.x;
}
bool cmpy(const point &a,const point &b)
{
	return a.y<b.y;
}
inline ll dis(const point &a,const point &b)
{
	return (a.x-b.x)*1ll*(a.x-b.x)+(a.y-b.y)*1ll*(a.y-b.y);
}
struct kdt
{
	kdt *ls,*rs;
	point p;
	int xmn,xmx,ymn,ymx;
	kdt(){}
	kdt(const point &p):p(p)
	{
		ls=rs=NULL;
		xmn=xmx=p.x;
		ymn=ymx=p.y;
	}
	void update()
	{
		if(ls)
		{
			xmn=min(xmn,ls->xmn);
			xmx=max(xmx,ls->xmx);
			ymn=min(ymn,ls->ymn);
			ymx=max(ymx,ls->ymx);
		}
		if(rs)
		{
			xmn=min(xmn,rs->xmn);
			xmx=max(xmx,rs->xmx);
			ymn=min(ymn,rs->ymn);
			ymx=max(ymx,rs->ymx);
		}
	}
	ll mxdis(const point &p)
	{
		return  max(max(dis(p,point(xmn,ymn)),dis(p,point(xmx,ymn))),
					max(dis(p,point(xmn,ymx)),dis(p,point(xmx,ymx))));
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
int k;
void query(kdt *&x,const point &p)
{
	ll dist=dis(p,x->p);
	if(cmp(pa(dist,x->p.id),heap[1]))
	{
		pop_heap(heap+1,heap+k+1,cmp);
		heap[k]=pa(dist,x->p.id);
		push_heap(heap+1,heap+k+1,cmp);
	}
	ll l=x->ls?x->ls->mxdis(p):-inf;
	ll r=x->rs?x->rs->mxdis(p):-inf;
	if(l>r)
	{
		if(x->ls&&l>=heap[1].first)
			query(x->ls,p);
		if(x->rs&&r>=heap[1].first)
			query(x->rs,p);
	}
	else
	{
		if(x->rs&&r>=heap[1].first)
			query(x->rs,p);
		if(x->ls&&l>=heap[1].first)
			query(x->ls,p);	
	}
}
int main()
{
	int n,m;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].x,&p[i].y),p[i].id=i;
	build(root,1,n,false);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		static point t;
		scanf("%d%d%d",&t.x,&t.y,&k);
		for(int i=1;i<=k;i++)
			heap[i]=pa(-inf,0);
		query(root,t);
		printf("%d\n",heap[1].second);
	}
}
