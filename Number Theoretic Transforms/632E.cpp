#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=(1<<20)+10;
int mod;
int mul(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1)
			ans=ans*1ll*x%mod;
		x=x*1ll*x%mod;
		y>>=1;
	}
	return ans;
}
void NTT(int *a,int len,int type)
{
	for(int i=0,t=0;i<len;i++)
	{
		if(t<i)
			swap(a[i],a[t]);
		for(int j=len>>1;(t^=j)<j;j>>=1);
	}
	for(int i=2;i<=len;i<<=1)
	{
		int wn=mul(3,(mod-1)/i);
		for(int j=0;j<len;j+=i)
		{
			int w=1,t;
			for(int k=0;k<(i>>1);k++,w=w*1ll*wn%mod)
			{
				t=a[j+k+(i>>1)]*1ll*w%mod;
				a[j+k+(i>>1)]=(a[j+k]+mod-t)%mod;
				a[j+k]=(a[j+k]+t)%mod;
			}
		}
	}
	if(type<0)
	{
		reverse(a+1,a+len);
		int inv=mul(len,mod-2);
		for(int i=0;i<len;i++)
			a[i]=a[i]*1ll*inv%mod;
	}
}
int cnt[maxn];
int tnc[maxn];
int mx;
int a[maxn];
int b[maxn];
int n,k;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		mx=max(x,mx);
		++tnc[x];
		++cnt[x];
	}
	int len;
	for(len=1;len<=mx*k;len<<=1);
	mod=998244353;
	NTT(cnt,len,1);
	for(int i=0;i<len;i++)
		a[i]=mul(cnt[i],k);
	NTT(a,len,-1);
	mod=1004535809;
	NTT(tnc,len,1);
	for(int i=0;i<len;i++)
		b[i]=mul(tnc[i],k);
	NTT(b,len,-1);
	for(int i=0;i<len;i++)
		if(a[i]||b[i])
			printf("%d ",i);
	puts("");
}
