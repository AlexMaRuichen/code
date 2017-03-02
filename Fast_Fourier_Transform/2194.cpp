#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
const int maxn=(1<<18)+10;
typedef struct complex
{
	double x,y;
	complex(){}
	complex(double x,double y):x(x),y(y){}
}cp;
inline cp operator + (register const cp &a,register const cp &b)
{
	return cp(a.x+b.x,a.y+b.y);
}
inline cp operator - (register const cp &a,register const cp &b)
{
	return cp(a.x-b.x,a.y-b.y);
}
inline cp operator * (register const cp &a,register const cp &b)
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
			cp t,w(1,0);
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
int ans[maxn];
void FFT(cp *a,cp *b,cp *c,int len)
{
	DFT(a,len,1);
	DFT(b,len,1);
	for(int i=0;i<len;i++)
		c[i]=a[i]*b[i];
	DFT(c,len,-1);
	for(int i=0;i<len;i++)
		ans[i]=int(c[i].x+0.1);
}
cp a[maxn];
cp b[maxn];
cp c[maxn];
int n;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%lf%lf",&a[i].x,&b[i].x);
	reverse(b,b+n);
	int len;
	for(len=1;len<=(n<<1);len<<=1);
	FFT(a,b,c,len);
	for(int i=0;i<n;i++)
		printf("%d\n",ans[i+n-1]);
	
}
