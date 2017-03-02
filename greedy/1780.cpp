#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=1010;
int n;
long long a[maxn];
long long b[maxn];
const int maxlen=100010;
const int mod=1e4;
struct hpc
{
	int x[maxlen];
	int len;
	char s[maxlen];
	hpc()
	{
		len=1;
		memset(x,0,sizeof(x));
	}
	void read()
	{
		scanf("%s",s+1);
		int l=strlen(s+1),num=0,cnt=0;
		int rem=l%4;
		len=(l+3)/4;
		for(int i=1;i<=l;i++)
		{
			num=(num<<3)+(num<<1);
			num+=s[i]-'0';
			if((i-rem)%4==0)
			{
				x[len-cnt++]=num;
				num=0;
			}
		}
		if(num)
			x[len-cnt]=num;
	}
	void print()
	{
		printf("%d",x[len]);
		for(int i=len-1;i;i--)
			printf("%04d",x[i]);
		puts("");
	}
	void operator *= (const int &s)
	{
		long long num=0;
		for(int i=1;i<=len;i++)
		{
			num+=s*x[i];
			x[i]=num%mod;
			num/=mod;
		}
		if(num)
			x[++len]=num;
	}
	void operator /= (const int &s)
	{
		int num=0;
		for(int i=len;i;i--)
		{
			x[i]+=num*mod;
			num=x[i]%s;
			x[i]/=s;
		}
		while(x[len]==0&&len>1)
			len--;
	}
	hpc operator * (const int &s) const
	{
		hpc res=*this;
		res*=s;
		return res;
	}
	hpc operator / (const int &s) const
	{
		hpc res=*this;
		res/=s;
		return res;
	}

	bool operator < (const hpc &s) const
	{
		if(len!=s.len)
			return len<s.len;
		for(int i=len;i;i--)
			if(x[i]!=s.x[i])
				return x[i]<s.x[i];
	}
}A,ans;
long long B;
int p[maxn];
bool cmp(int x,int y)
{
	return a[x]*b[x]<a[y]*b[y];
}
int main()
{
	scanf("%d",&n);
	A.read();
	scanf("%lld",&B);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&a[i],&b[i]),p[i]=i;
	sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n;i++)
		ans=max(ans,A/b[p[i]]),A*=a[p[i]];
	ans.print();
}
