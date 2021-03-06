#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
const int maxn=(1<<17)+10;
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
	return *s++;
}

typedef struct complex
{
	double x,y;
	complex(){};
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
			swap(a[t],a[i]);
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
int t;
int main()
{
	register char x=getc();
	while(x<'0'||x>'9')
        x=getc();
    while(x>='0'&&x<='9')
        n=(n<<1)+(n<<3)+x-'0',x=getc();
	t=0;
    while(x<'0'||x>'9')
        x=getc();
    while(x>='0'&&x<='9')
        a[t++].x=x-'0',x=getc();
    reverse(a,a+n);
    t=0;
    while(x<'0'||x>'9')
        x=getc();
    while(x>='0'&&x<='9')
        b[t++].x=x-'0',x=getc();
    reverse(b,b+n);
    int len;
    for(len=1;len<=n<<1;len<<=1);
	FFT(a,b,c,len);
	register int i;
	for(i=0;i<=len;i++)
		ans[i+1]+=ans[i]/10,ans[i]%=10;
	for(i=len;!ans[i];--i);
	for(;i>=0;i--)
		putchar(ans[i]+'0');
	puts("");
}
