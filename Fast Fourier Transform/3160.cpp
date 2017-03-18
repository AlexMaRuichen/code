#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <string.h>
using namespace std;
const int maxn=(1<<18)+10;
const int mod=1e9+7;
char s[maxn>>1];
char r[maxn];
int  p[maxn];
inline int lower_bound()
{
	int l=1,r=1e5+1,mid;
	while(l<r)
	{
		mid=l+r>>1;
		if(s[mid]=='a'||s[mid]=='b')
			l=mid+1;
		else
			r=mid;
	}
	return l-1;
}
int n;
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
int ans[maxn];
inline void DFT(cp *a,int len,int type)
{
	static int i,t,j,k;
	for(i=0,t=0;i<len;i++)
	{
		if(t<i)
			swap(a[i],a[t]);
		for(int j=len>>1;(t^=j)<j;j>>=1);
	}
	for(i=2;i<=len;i<<=1)
	{
		cp wn(cos(2*M_PI*type/i),sin(2*M_PI*type/i));
		for(j=0;j<len;j+=i)
		{
			cp t,w(1,0);
			for(k=0;k<(i>>1);k++,w=w*wn)
			{
				t=a[j+k+(i>>1)]*w;
				a[j+k+(i>>1)]=a[j+k]-t;
				a[j+k]=a[j+k]+t;
			}
		}
	}
	if(type<0)
		for(i=0;i<len;i++)
			a[i].x/=len;
}
cp a[maxn];
cp c[maxn];
int cnt;
inline int manacher()
{
	r[0]='&';
	r[1]='^';
	int len=n,i,ans=0,mx=1,id=1;
	for(i=1;i<=len;i++)
		r[i<<1]=s[i],r[i<<1|1]='^';
	len=len<<1|1;
	for(i=1;i<=len;i++)
	{
		if(mx>i)
			p[i]=min(p[(id<<1)-i],mx-i);
		else
			p[i]=1;
		while(r[i-p[i]]==r[i+p[i]])
			++p[i];
		if(mx<p[i]+i)
			mx=p[i]+i,id=i;
		if((ans+=(p[i]>>1))>=mod)
			ans-=mod;
	}
	return ans;
}
int Pow[maxn];
int len,i;
int main()
{
	fread(s+1,1,100000,stdin);
	n=lower_bound();
	for(len=1;len<=(n<<1);len<<=1);
	Pow[0]=1;
	for(i=1;i<maxn;i++)
		if((Pow[i]=(Pow[i-1]<<1))>=mod)
			Pow[i]-=mod;
	for(i=1;i<=n;i++)
		a[i].x=s[i]=='a'?1:0;
	DFT(a,len,1);
	for(i=0;i<len;i++)
		c[i]=a[i]*a[i];
	memset(a,0,sizeof(a));
	for(i=1;i<=n;i++)
		a[i].x=s[i]=='b'?1:0;
	DFT(a,len,1);
	for(i=0;i<len;i++)
		c[i]=c[i]+a[i]*a[i];
	DFT(c,len,-1);
	for(i=0;i<len;i++)
		ans[i]+=(int)(c[i].x+0.1);	
	for(i=0;i<len;i++)
		if((cnt+=Pow[ans[i]+1>>1]-1)>=mod)
			cnt-=mod;
	printf("%d\n",((cnt-manacher())%mod+mod)%mod);
}
