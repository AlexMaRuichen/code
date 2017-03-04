#include<math.h>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define eps 1e-8
struct poi 
{
	double x,y;
	poi(){}
	poi(double x,double y):x(x),y(y){}
	friend poi operator+(poi p1,poi p2)
	{
		return poi(p1.x+p2.x,p1.y+p2.y);
	}
	friend poi operator-(poi p1,poi p2)
	{
		return poi(p1.x-p2.x,p1.y-p2.y);
	}
	friend double operator^(poi p1,poi p2)
	{
		return p1.x*p2.y-p1.y*p2.x;
	}
	friend double operator*(poi p1,poi p2)
	{
		return p1.x*p2.x+p1.y*p2.y;
	}
	friend poi operator*(double k,poi p1)
	{
		return poi(p1.x*k,p1.y*k);
	}
	friend double dis(poi p1)
	{
		return sqrt(p1.x*p1.x+p1.y*p1.y);
	}
}a1,a2,b1,b2,tmp,t1;
struct line
{
	poi p,v;
	line(){}
	line(poi p,poi v):p(p),v(v){}
}a,b;
int n;
poi intersect(line l1,line l2)
{
	poi u=l1.p-l2.p;
	double tmp=(l2.v^u)/(l1.v^l2.v);
	return l1.p+tmp*l1.v;
};
int main()
{
	//freopen("tt.in","r",stdin);
	scanf("%d",&n);
	while(n--)
	{
		scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&a1.x,&a1.y,&a2.x,&a2.y,&b1.x,&b1.y,&b2.x,&b2.y);
		if(dis(a1-a2)<eps||dis(b1-b2)<eps)
			goto end;
		if(a1.y<a2.y)
			swap(a1,a2);
		if(b1.y<b2.y)
			swap(b1,b2);
		if(a1.y>b1.y)
		{	
			swap(a1,b1);
			swap(a2,b2);
		}
		a=line(a1,a1-a2);
		b=line(b1,b1-b2);
		if(fabs(a.v.x*b.v.y-a.v.y*b.v.x)<eps)
			goto end;
		tmp=intersect(a,b);
		t1=intersect(line(a1,poi(0,1)),b);
		if((t1-b1)*(t1-b2)<eps&&t1.y>a1.y)
			goto end;
		if((tmp-a1)*(tmp-a2)>eps||(tmp-b1)*(tmp-b2)>eps)
			goto end;
		t1=intersect(line(a1,poi(1,0)),b);
		printf("%.2lf\n",fabs((t1-tmp)^(a1-tmp))/2);
		continue;
		end:
		printf("0.00\n");
	}
	return 0;
}

