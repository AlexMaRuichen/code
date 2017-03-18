#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
const int maxn=(1<<19)+10;
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
		cp wn=cp(cos(2*M_PI*type/i),sin(2*M_PI*type/i));
		for(int j=0;j<len;j+=i)
		{
			cp t,w(1,0);
			for(int k=0;k<(i>>1);k++,w=w*wn)
			{
				t=w*a[j+k+(i>>1)];
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
inline void FFT(cp *a,cp *b,cp *c,int len)
{
	DFT(a,len,1);
	DFT(b,len,1);
	for(int i=0;i<len;i++)
		c[i]=a[i]*b[i];
	DFT(c,len,-1);
	for(int i=0;i<len;i++)
		ans[i]+=int(c[i].x+0.5);
}
cp a[maxn];
cp b[maxn];
cp c[maxn];
char s[maxn];
char t[maxn];
int n,m,k;
void process(char x,int len)
{
	static int sum[maxn];
	for(int i=1;i<=n;i++)
		sum[i]=(s[i-1]==x)+sum[i-1];
	for(int i=0;i<n;i++)
		a[i]=cp(sum[min(i+k,n-1)+1]-sum[max(0,i-k)]>0,0);
	for(int i=n;i<len;i++)
		a[i]=cp(0,0);
	for(int i=0;i<m;i++)
		b[m-i-1]=cp(t[i]==x,0);
	for(int i=m;i<len;i++)
		b[i]=cp(0,0);
	FFT(a,b,c,len);
}
int main()
{
	scanf("%d%d%d%s%s",&n,&m,&k,s,t);
	int len=1;
	for(len=1;len<=n+m;len<<=1);
	for(int i=0;i<10;i++)
		process(i+'0',len);
	int cnt=0;
	for(int i=0;i<len;i++)
		cnt+=ans[i]==m;
	printf("%d\n",cnt);
}
