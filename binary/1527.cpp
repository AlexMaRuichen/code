#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=100010;
const long double eps=0.00001;
int n;
double x[maxn];
double y[maxn];
double s[maxn];
double sum;
bool check(double d)
{
	double c=0;
	for(int i=1;i<=n;i++)
	{
		double t=s[i]/d;
		if((max(c+t,y[i])-min(c+t,y[i]))<(1e-9)*max(c+t,y[i]))
			c=max(c+t,x[i]);
		else if(c+t>y[i])
			return false;
		c=max(c+t,x[i]);
	}
	return true;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf%lf",&x[i],&y[i],&s[i]);
		sum=max(s[i],sum);
	}
	double l=eps,r=1e8;
	while(r-l>=eps)
	{
		double mid=(l+r)/2.0;
		if(check(mid))
			r=mid;
		else
			l=mid;
	}
	printf("%.2lf\n",l);
}
