#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn=(1<<18)+10;
#ifdef ONLINE_JUDGE
const long double M_PI=acos(-1);
#endif
struct cp
{
	long double x,y;
	cp(){}
	cp(long double x,long double y):x(x),y(y){}
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
int n;
int sum[maxn];
long long zero[maxn];
long long ans;
cp a[maxn];
cp b[maxn];
cp c[maxn];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			zero[i]=zero[i-1]+(1+i)*i/2;
		for(int i=1;i<=n;i++)
			scanf("%d",&sum[i]),sum[i]+=sum[i-1];
		for(int i=1,l=0;i<=n;i=l+1)
			if(sum[i]^sum[i-1])    
				l=i;
			else
			{
				for(l=i;l<n&&sum[l+1]==sum[i];l++);
					ans+=zero[l-i+1];
			}
		printf("%lld\n",ans);
		int len;
		for(len=1;len<sum[n]<<1;len<<=1);
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(c,0,sizeof(c));
		for(int i=1;i<=n;i++)
			a[sum[i]].x+=i;
		for(int i=1;i<=n;i++)
			b[sum[n]-sum[i-1]].x+=1;
		DFT(a,len,1);
		DFT(b,len,1);
		for(int i=0;i<len;i++)
			c[i]=a[i]*b[i];
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++)
			a[sum[i]].x+=1;
		for(int i=1;i<=n;i++)
			b[sum[n]-sum[i-1]].x+=i-1;
		DFT(a,len,1);
		DFT(b,len,1);
		for(int i=0;i<len;i++)
			c[i]=c[i]-a[i]*b[i];
		DFT(c,len,-1);
		for(int i=1;i<=sum[n];i++)
			printf("%lld\n",(long long)(c[i+sum[n]].x+0.5));
	}
}
