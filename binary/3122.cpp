#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
const double pi=3.141592653589793238462;
const double eps=0.000001;
int t;
int n,f;
int r[10010];
int m;
bool check(double x)
{
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		ans+=r[i]/x;
	}
	return ans>=f;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&f);
		f++;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&r[i]);
			r[i]*=r[i];
			m=m>r[i]?m:r[i];
		}
		double l=0,r=m;
		while(r-l>eps)
		{
			double mid=(l+r)/2;
			if(check(mid))
				l=mid;
			else
				r=mid;
		}
		printf("%.4lf\n",1.0*l*pi);
	}
}
