#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
const int maxn=(1<<18)+10;
struct cp
{
	double x,y;
	cp(){}
	cp(double x,double y):x(x),y(y){}
};
cp operator + (const cp &a,const cp &b)
{
	return cp(a.x+b.x,a.y+b.y);
}
cp operator - (const cp &a,const cp &b)
{
	return cp(a.x-b.x,a.y-b.y);
}
cp operator * (const cp &a,const cp &b)
{
	return cp(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
}
void DFT(cp *a,int len,int type)
{
	for(int i=0,t=0;i<len;i++)
	{
		if(t<i)
			swap(a[i],a[t]);
		for(int j=len>>1;(t^=j)<j;j>>=1);
	}
	for(int i=2;i<=len;i<<=1)
	{
		cp wn(cos(2*M_PI*type/i),sin(2*M_PI*type/i));
		for(int j=0;j<len;j+=i)
		{
			cp w(1,0),t;
			for(int k=0;k<(i>>1);k++,w=w*wn)
			{
				t=a[j+k+(i>>1)]*w;
				a[j+k+(i>>1)]=a[j+k]-t;
				a[j+k]=a[j+k]+t;
			}
		}
	}
	if(type<0)
		for(int i=0;i<len;i++)
			a[i].x/=len;
}
void FFT(cp *a,cp *b,cp *c,int len)
{
	DFT(a,len,1);
	DFT(b,len,1);
	for(int i=0;i<len;i++)
		c[i]=a[i]*b[i];
	DFT(c,len,-1);
}
cp a[maxn];
cp b[maxn];
cp c[maxn];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%lf",&a[i].x);
	for(int i=0;i<n-1;i++)
		b[i].x=-1.0/(n-i-1)/(n-i-1);
	for(int i=n;i<(n<<1)-1;i++)
		b[i].x=1.0/(i-n+1)/(i-n+1);
	int len;
	for(len=1;len<n<<1;len<<=1);
	FFT(a,b,c,len);
	for(int i=n-1;i<(n<<1)-1;i++)
		printf("%lf\n",c[i].x);
}
