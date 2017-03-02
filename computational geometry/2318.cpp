#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <math.h>
using namespace std;
const double eps=1e-8;
const int maxn=5010;
struct point
{
	double x,y;
	point(){}
	point(double x,double y):x(x),y(y){}
};
point operator + (const point &a,const point &b)
{
	return point(a.x+b.x,a.y+b.y);
}
point operator - (const point &a,const point &b)
{
	return point(a.x-b.x,a.y-b.y);
}
point operator * (const point &a,const int &x)
{
	return point(a.x*x,a.y*x);
}
double operator * (const point &a,const point &b)
{
	return a.x*b.y-a.y*b.x;
}
double operator ^ (const point &a,const point &b)
{
	return a.x*b.x+a.y*b.y;
}
bool operator < (const point &a,const point &b)
{
	return a.x!=b.x?a.x<b.x:a.y<b.y;
}
struct line
{
	point p,v;
	line(){}
	line(const point &p,const point &v):p(p),v(v){}
}l[maxn];
bool left(const line &l,const point &p)
{
	return (p-l.p)*l.v<eps;
}
bool operator < (const line &a,const line &b)
{
	return a.p<b.p;
}
int n,m,xmn,ymn,xmx,ymx;
int cnt[maxn];
int ans[maxn];
int main()
{
	while(scanf("%d",&n)&&n)
	{
		memset(cnt,0,sizeof(cnt));
		memset(ans,0,sizeof(ans));
		scanf("%d%d%d%d%d",&m,&xmn,&ymx,&xmx,&ymn);
		l[0]=line(point(xmn,ymx),point(xmn,ymn));
		l[0].v=l[0].v-l[0].p;
		l[n+1]=line(point(xmx,ymx),point(xmx,ymn));
		l[n+1].v=l[n+1].v-l[n+1].p;
		for(int i=1;i<=n;i++)
		{
			scanf("%lf%lf",&l[i].p.x,&l[i].v.x);
			l[i].p.y=ymx;
			l[i].v.y=ymn;
			l[i].v=l[i].v-l[i].p;
		}
		sort(l+1,l+n+1);
		point p;
		for(int i=1;i<=m;i++)
		{
			scanf("%lf%lf",&p.x,&p.y);
			if(p.x<xmn||p.x>xmx||p.y<ymn||p.y>ymx)
				continue;
			int t=0;
			while(left(l[t],p)&&left(l[t+1],p))
				++t;
			++cnt[t];
		}
		for(int i=0;i<=n;i++)
			++ans[cnt[i]];
		puts("Box");
		for(int i=1;i<=m;i++)
			if(ans[i])
				printf("%d: %d\n",i,ans[i]);
	}
}
