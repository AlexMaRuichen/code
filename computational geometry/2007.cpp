#include <stdio.h>
#include <algorithm>
using namespace std;
struct point
{
	double x,y;
	point(){}
	point(double x,double y):x(x),y(y){}
}p[60];
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
int main()
{
	
}
