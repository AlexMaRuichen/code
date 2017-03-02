#include <stdio.h>
#include <string.h>
#define max(a,b) (a)>(b)?(a):(b)
const int maxn=1e4+10;
const int mod=1e4;
struct hpc
{
	int len;
	int x[maxn];
	hpc()
	{
		len=1;
		memset(x,0,sizeof(x));
	}
	void read()
	{
		char s[maxn];
		scanf("%s",s+1);
		int l=strlen(s+1);
		int rem=l%4;
		len=(l+3)/4;
		int num=0;
		int cnt=9;
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
	}
	void operator += (const hpc &s)
	{
		int l=max(len,s.len);
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
	void operator *= (const hpc &s)
	{
		hpc res;
		res.len=len+s.len;
		for(int i=1;i<=len;i++)
		{
			int num=0,t;
			for(int j=1;j<=s.len;j++)
			{
				t=x[i]*s.x[j]+res.x[i+j-1]+num;
				res.x[i+j-1]=t%mod;
				num=t/mod;
			}
			if(num)
				res.x[i+s.len]=num;
		}
		*this=res;
		while(!x[len]&&len>1)
			--len;
	}
	hpc operator + (const hpc &s) const
	{
		hpc res=*this;
		res+=s;
		return res;
	}
	hpc operator * (const hpc &s) const
	{
		hpc res=*this;
		res*=s;
		return res;
	}
	void print()
	{
		printf("%d",x[len]);
		for(int i=len-1;i;i--)
			printf("%04d",x[i]);
		puts("");
	}
};
struct matrix
{
	hpc x[2][2];
	matrix()
	{}
	matrix operator * (const matrix &s) const
	{
		matrix res;
		static hpc t;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)
				{
					t=x[i][k]*s.x[k][j];
					res.x[i][j]+=t;
				}
		return res;
	}
};
matrix mul(matrix s,int y)
{
	matrix res;
	res.x[0][0].x[1]=1;
	res.x[1][1].x[1]=1;
	while(y)
	{
		if(y&1)
			res=res*s;
		s=s*s;
		y>>=1;
	}
	return res;
}
int main()
{
	matrix base;
	matrix init;
	int n;
	scanf("%d",&n);
	base.x[0][1].x[1]=1;
	init.x[0][0].x[1]=1;
	init.x[0][1].x[1]=1;
	init.x[1][0].x[1]=1;
	init=mul(init,n);
	base=base*init;
	base.x[0][1].print();
}
