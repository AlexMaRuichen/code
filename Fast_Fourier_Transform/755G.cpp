#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int maxn=(1<<18)+10;
inline void add(int &x,int y)
{	
	if((x+=y)>=mod)
		x-=mod;
}
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
void DFT(vector <int> &a)
{
	int len=a.size();
	for(int i=0,t=0;i<len;i++)
	{
		if(i<t)
			swap(a[i],a[t]);
		for(int j=len>>1;(t^=j)<j;j>>=1);
	}
	for(int i=2;i<=len;i<<=1)
	{
		int wn=mul(3,(mod-1)/i);
		for(int j=0;j<len;j+=i)
		{
			int w=1,t;
			for(int k=0;k<i>>1;k++,w=wn*1ll*w%mod)
			{
				t=a[j+k+(i>>1)]*1ll*w%mod;
				a[j+k+(i>>1)]=(a[j+k]-t+mod)%mod;
				a[j+k]=(a[j+k]+t)%mod;
			}
		}
	}
}
int len;
vector <int> NTT(vector <int> a)
{
	a.resize(len<<1);
	DFT(a);
	for(int i=0;i<len<<1;i++) 
		a[i]=a[i]*1ll*a[i]%mod;
	reverse(++a.begin(),a.end());
	DFT(a);
	int t=mul(len<<1,mod-2);
	for(int i=0;i<len<<1;i++)
		a[i]=a[i]*1ll*t%mod;
	a.resize(len);
	return a;
}
int n,m;
pair<vector <int>,vector <int> >partition(int n) 
{
	// <v_{n-1},v_{n}>
	if(n==1) 
	{
		vector <int> a(len,0);
		vector <int> b(len,0);
		a[0]=1;
		b[0]=1;
		b[1]=1;
		return make_pair(a,b);
	}
	if(n==2) 
	{
		vector <int> a(len,0);
		vector <int> b(len,0);
		a[0]=1;
		a[1]=1;
		b[0]=1;
		b[1]=3;
		b[2]=1;
		return make_pair(a,b);
	}
	if(n&1) 
	{
		pair <vector <int>,vector <int> >p=partition(n-1);
		vector <int> a=p.first;
		vector <int> b=p.second;
		vector <int> c(len,0);
		for(int i=0;i<len;i++) 
		{
			add(c[i],b[i]);
			if(i>0) 
			{
				add(c[i],b[i-1]);
				add(c[i],a[i-1]);
			}
		}
		return make_pair(b,c);
	}
	pair<vector <int>,vector <int> > p=partition(n>>1);
	vector <int> a=p.first;
	vector <int> b=p.second;
	printf("%d\n",n);
	for(int i=0;i<len;i++)
		printf("%d ",a[i]);
	puts("");
	for(int i=0;i<len;i++)
		printf("%d ",b[i]);
	puts("");
	vector <int> a2=NTT(a);
	vector <int> b2=NTT(b);
	vector <int> my_b(len,0);
	for(int i=0;i<len;i++) 
	{
		add(my_b[i],b2[i]);
		if(i>0) 
			add(my_b[i],a2[i-1]);
	}
	vector <int> z(len,0);
	for(int i=0;i<len;i++) 
	{
		add(z[i],mod-a[i]);
		if(i+1<len) 
		{
			add(z[i],b[i+1]);
			add(z[i],mod-a[i+1]);
		}
	}
	vector <int> z2=NTT(z);
	vector <int> my_z(len,0);
	for(int i=0;i<len;i++) 
	{
		add(my_z[i],a2[i]);
		if(i>0) 
			add(my_z[i],z2[i-1]);
	}
	vector <int> aux(len,0);
	for(int i=0;i<len;i++) 
	{
		add(aux[i],my_b[i]);
		if(i>0)
			add(aux[i],mod-my_z[i-1]);
	}
	vector <int> my_a(len,0);
	my_a[0]=aux[0];
	for(int i=1;i<len;i++) 
	{
		my_a[i]=aux[i];
		add(my_a[i],mod-my_a[i-1]);
	}
	return make_pair(my_a,my_b);
}
int main()
{	
	int n,k;
	scanf("%d%d",&n,&k);
	for(len=4;len<=k;len<<=1);
	vector <int> a=partition(n+1).first;
	for(int i=1;i<=k;i++)
		printf("%d ",i<len?a[i]:0);
	puts("");
}
