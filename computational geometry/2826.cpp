#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
const double eps=1e-8;
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
double operator * (const point &a,const point &b)
{
	return a.x*b.y-a.y*b.x;
}
double operator ^ (const point &a,const point &b)
{
	return a.x*b.x+a.y*b.y;
}
point operator * (const point &a,const double &x)
{
	return point(a.x*x,a.y*x);
}
struct line
{
	point p,v;
	line(){}
	line(const point &p,const point &v):p(p),v(v){}
};
bool left(const line &l,const point &p)
{
	return (p-l.p)*l.v<-eps;
}
point intersect(const line &l1,const line &l2)
{
	point u=l1.p-l2.p;
	double tmp=(l2.v*u)/(l1.v*l2.v);
	return l1.p+l1.v*tmp;
}
bool equal(const double &a,const double &b)
{
	return fabs(a-b)<eps;
}
double dis(const point &a)
{
	return sqrt(a.x*a.x+a.y*a.y);
}
int main()
{
	int T;
	scanf("%d",&T);
	point a,b,c,d,tmp,t1;
	line x,y;
	while(T--)
	{
		scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&a.x,&a.y,&b.x,&b.y,&c.x,&c.y,&d.x,&d.y);
		if(dis(a-b)<eps||dis(c-d)<eps)
			goto end;
		if(a.y<b.y)
			swap(a,b);
		if(c.y<d.y)
			swap(c,d);
		if(a.y>c.y)
			swap(a,c),swap(b,d);
		if(fabs((a-b)*(c-d))<eps)
			goto end;
		x=line(a,a-b);
		y=line(c,c-d);
		tmp=intersect(x,y);
		t1=intersect(line(a,point(0,1)),y);
		if(((t1-c)^(t1-d))<eps&&t1.y>a.y)
			goto end;
		if(((tmp-a)^(tmp-b))>eps||((tmp-c)^(tmp-d))>eps)
			goto end;
		t1=intersect(line(a,point(1,0)),y);
		printf("%.2lf\n",fabs((t1-tmp)*(a-tmp))/2);
		continue;
		end:
		puts("0.00");
	}
}
