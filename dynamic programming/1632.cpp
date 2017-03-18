#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn=90;
const int mod=1e4;
int n,m;
int a[maxn];
struct hpc
{
	int len;
	int x[maxn];
	hpc()
	{
		len=1;
		memset(x,0,sizeof(x));
	}
	void operator += (const hpc &s)
	{
		int l=max(s.len,len);
		for(int i=1;i<=l;i++)
		{
			x[i]+=s.x[i];
			x[i+1]+=x[i]/mod;
			x[i]%=mod;
		}
		while(x[l+1])
			++l;
		len=l;
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
	hpc operator * (const int &s) const
	{
		hpc res=*this;
		res*=s;
		return res;
	}

	hpc operator + (const hpc &s) const
	{
		hpc res=*this;
		res+=s;
		return res;
	}
	void print()
	{
		printf("%d",x[len]);
		for(int i=len-1;i;i--)
			printf("%04d",x[i]);
	}
}f[maxn][maxn],ans,A,B;
hpc MAX(hpc a,hpc b)
{
	if(a.len!=b.len)
	{
		if(a.len>b.len)
			return a;
		else
			return b;
	}
	for(int i=a.len;i;i--)
		if(a.x[i]!=b.x[i])
		{
			if(a.x[i]>b.x[i])
				return a;
			else
				return b;
		}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=m;i++)
			scanf("%d",&a[i]);
		hpc idx;
		idx.x[1]=1;

		for(int i=1;i<=m+1;i++,idx*=2)
			for(int j=1;j<=i;j++)
			{
				A=f[i-1][j-1]+idx*a[j-1];
				B=f[i-1][j]+idx*a[j+m-i+1];
				f[i][j]=MAX(A,B);
			}
		hpc tmp;
		for(int i=1;i<=m;i++)
			tmp=MAX(tmp,f[m+1][i]);
		ans+=tmp;
	}
	ans.print();
	puts("");
}

