#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=50010;
struct point
{
	int x,y,h;
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
	int xmn,xmx,ymn,ymx;
	long long sum;
	kdt(){}
	kdt(const point &p):p(p)
	{
		ls=rs=NULL;
		xmn=xmx=p.x;
		ymn=ymx=p.y;
		sum=p.h;
	}
	void update()
	{
		sum=p.h;
		if(ls)
		{
			xmn=min(xmn,ls->xmn);
			xmx=max(xmx,ls->xmx);
			ymn=min(ymn,ls->ymn);
			ymx=max(ymx,ls->ymx);
			sum+=ls->sum;
		}
		if(rs)
		{
			xmn=min(xmn,rs->xmn);
			xmx=max(xmx,rs->xmx);
			ymn=min(ymn,rs->ymn);
			ymx=max(ymx,rs->ymx);
			sum+=rs->sum;
		}
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
int check(kdt *x,int a,int b,int c)
{
	int ans=0;
	x->xmn*1ll*a+x->ymn*1ll*b<c?++ans:--ans;
	x->xmx*1ll*a+x->ymn*1ll*b<c?++ans:--ans;
	x->xmn*1ll*a+x->ymx*1ll*b<c?++ans:--ans;
	x->xmx*1ll*a+x->ymx*1ll*b<c?++ans:--ans;
	return ans;
}
long long query(kdt *x,int a,int b,int c)
{
	if(!x)
		return 0;
	int sta=check(x,a,b,c);
	if(sta==-4)
		return 0;
	else if(sta==4)
		return x->sum;
	else
		return  query(x->ls,a,b,c)+
				query(x->rs,a,b,c)+
				((x->p.x*1ll*a+x->p.y*1ll*b<c)?x->p.h:0);
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].h);
	build(root,1,n,false);
	for(int i=1;i<=m;i++)
	{
		static int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		printf("%lld\n",query(root,a,b,c));
	}
}
