#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <string.h>
using namespace std;
const int maxn=1048600;
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
cp operator * (const int &a,const cp &b)
{
	return cp(a*b.x,a*b.y);
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
			cp w(1,0),t;
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
char s[maxn];
char t[maxn];
cp a[maxn];
cp b[maxn];
cp c[maxn];
int main()
{
	int n,m;
	scanf("%d%d%s%s",&n,&m,s+1,t+1);
	int len=1;
	for(;len<n+m;len<<=1);
	for(int i=1;i<=n;i++)
		s[i]=s[i]=='*'?0:s[i];
	for(int i=1;i<=m;i++)
		t[i]=t[i]=='*'?0:t[i];

	for(int i=1;i<=n;i++)
		a[i]=cp(s[n-i+1]*s[n-i+1]*s[n-i+1],0);
	for(int i=1;i<=m;i++)
		b[i]=cp(t[i],0);
	DFT(a,len,1);
	DFT(b,len,1);
	for(int i=0;i<len;i++)
		c[i]=a[i]*b[i];
		
	memset(a,0,sizeof(cp)*len);
	memset(b,0,sizeof(cp)*len);
	for(int i=1;i<=n;i++)
		a[i]=cp(s[n-i+1]*s[n-i+1],0);
	for(int i=1;i<=m;i++)
		b[i]=cp(t[i]*t[i],0);
	DFT(a,len,1);
	DFT(b,len,1);
	for(int i=0;i<len;i++)
		c[i]=c[i]-2*a[i]*b[i];

	memset(a,0,sizeof(cp)*len);
	memset(b,0,sizeof(cp)*len);	
	for(int i=1;i<=n;i++)
		a[i]=cp(s[n-i+1],0);
	for(int i=1;i<=m;i++)
		b[i]=cp(t[i]*t[i]*t[i],0);
	DFT(a,len,1);
	DFT(b,len,1);
	for(int i=0;i<len;i++)
		c[i]=c[i]+a[i]*b[i];
	
	DFT(c,len,-1);

	int ans=0;
	for(int i=1;i<=m-n+1;i++)
		if(c[n+i].x<1e-1)
            ++ans;
    printf("%d",ans);
	for(int i=1,j=0;i<=m-n+1;i++)
		if(c[n+i].x<1e-1)
			printf("%c%d",j++?' ':'\n',i);
	puts("");
}
