#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <math.h>
#include <stdlib.h>
using namespace std;
const double pi=acos(-1.0);
int t;
double x,y,m;
double px[1010],py[1010];
int n;
double tx,ty;
double ansx,ansy;
double dis(double x,double y)
{
	double ans=0;
	for(int i=1;i<=m;i++)
		ans+=sqrt((x-px[i])*(x-px[i])+(y-py[i])*(y-py[i]));
	return ans;
}
double Rand()  
{  
    return rand()%1000/1000.0;  
}  
void hill_climbing()
{
	double T=max(x,y);
	double delta=0.993;
	double nx,ny;
	while(T>0.001)
	{
		double r=Rand();
		nx=tx+(x/y)*T*(r*2-1);
		ny=ty+(y/x)*T*(r*2-1);
		if(nx>x||ny>y||nx<0||ny<0)
			continue;
		double j=dis(ansx,ansy)-dis(nx,ny);
		if(j<0)
			tx=nx,ty=ny;
		T*=delta;
	}
	if(dis(ansx,ansy)-dis(nx,ny)<0)
		ansx=nx,ansy=ny;
}
int main()
{
	srand(time(NULL));
	rand();
	scanf("%d",&t);
	while(t--)
	{
		scanf("%lf%lf%lf",&x,&y,&m);
		ansx=x/2;
		ansy=y/2;
		for(int i=1;i<=m;i++)
			scanf("%lf%lf",&px[i],&py[i]);
		for(int i=1;i<=30;i++)
			for(int j=1;j<=30;j++)
			{
				tx=rand()%int(x)+1;
				ty=rand()%int(y)+1;
				hill_climbing();
			}
		printf("The safest point is (%.1lf, %.1lf).\n",ansx,ansy);
	}
}
