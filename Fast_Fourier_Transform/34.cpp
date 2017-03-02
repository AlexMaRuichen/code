#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
const int maxn=(1<<18)+10;
char getc()
{
	static const int len=1<<15;
	static char buf[len],*s=buf,*t=buf;
	if(s==t)
	{
		t=(s=buf)+fread(buf,1,len,stdin);
		if(s==t)
			return EOF;
	}
	return *(s++);
}
void read(register int &x)
{
	char ch=getc();
	x=0;
	while(ch<'0'||ch>'9')
		ch=getc();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+ch-'0',ch=getc();
}
typedef struct complex
{
	double x,y;
	complex(){}
	complex(double a,double b):x(a),y(b){}
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
	if(type==-1)
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
		ans[i]=(int)(c[i].x+0.1);
}
cp a[maxn];
cp b[maxn];
cp c[maxn];
int n,m;
int main()
{
	read(n);
	read(m);
	register int x;
	for(int i=0;i<=n;i++)
		read(x),a[i].x=x;
	for(int i=0;i<=m;i++)
		read(x),b[i].x=x;
	int len;
	for(len=1;len<=n+m;len<<=1);
	FFT(a,b,c,len);
	for(int i=0;i<=n+m;i++)
		printf("%d ",ans[i]);
	puts("");
}
