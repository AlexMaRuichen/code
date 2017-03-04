#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <string.h>
using namespace std;
const int maxn=60;
const double eps=1e-6;
struct point
{
	double x,y;
	int id;
	point(){}
	point(double x,double y):x(x),y(y){}
}p[maxn];
point operator + (const point &a,const point &b)
{
	return point(a.x+b.x,a.y+b.y);
}
point operator - (const point &a,const point &b)
{
	return point(a.x-b.x,a.y-b.y);
}
double operator * (const point &a,const point &b)
{
	return a.x*b.y-a.y*b.x;
}
double operator ^ (const point &a,const point &b)
{
	return a.x*b.x+a.y*b.y;
}
point operator * (const point &a,const int &x)
{
	return point(a.x*x,a.y*x);
}
bool operator < (const point &a,const point &b)
{
	return fabs(a.y-b.y)>eps?a.y<b.y:a.x<b.x;
}
struct line
{
	point p,v;
	double alpha;
	int id;
	line(){}
	line(const point &p,const point &v,int id):p(p),v(v),id(id)
	{
		alpha=atan2(v.y,v.x);
	}
}l[maxn];
bool v[maxn];
int ans[maxn];
bool operator < (const line &a,const line &b)
{
	return a.alpha<b.alpha;
}
bool left(const line &l,const point &p)
{
	return (p-l.p)*l.v<-eps;
}
int main()
{
	int T;
	scanf("%d",&T);
	int n;
	while(T--)
	{
		memset(v,0,sizeof(v));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%lf%lf",&p[i].id,&p[i].x,&p[i].y);
		point cur(1e9,1e9),last(1e9,1e9);
		for(int i=1;i<=n;i++)
			last=min(last,p[i]);
		v[ans[1]=last.id]=true;
		cur=p[last.id%n+1];
		for(int i=1;i<=n;i++)
			if((cur-last)*(p[i]-last)<-eps)
				cur=p[i];
		for(int i=2;i<=n;i++)
		{
			last=cur;
			v[ans[i]=cur.id]=true;
			int j=1;
			for(j=1;j<=n;j++)
				if(!v[j])
				{
					cur=p[j];
					break;
				}
			for(j++;j<=n;j++)
				if(!v[j]&&(cur-last)*(p[j]-last)<-eps)
					cur=p[j];
		}
		printf("%d",n);
		for(int i=1;i<=n;i++)
			printf(" %d",ans[i]);
		puts("");
	}
}
