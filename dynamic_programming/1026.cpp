#include <stdio.h>
#define abs(x) ((x)>0?(x):-(x))
int f[11][10];
int sum[11];
int calc(int x)
{
	static int s[11];
	s[0]=0;
	int ans=0;
	while(x)
		s[++s[0]]=x%10,x/=10;
	for(int i=1;i<s[s[0]];i++)
		ans+=f[s[0]][i];
	for(int i=s[0]-1;i;i--)
		for(int j=1;j<=9;j++)
			ans+=f[i][j];
	for(int i=s[0]-1;i;i--)
	{
		for(int j=0;j<s[i];j++)
			if(abs(s[i+1]-j)>1)
				ans+=f[i][j];
		if(abs(s[i+1]-s[i])<2)
			break;
	}
	return ans;
}
int main()
{
	int l,r;
	scanf("%d%d",&l,&r);
	for(int i=0;i<10;i++)
		f[1][i]=1;
	for(int i=2;i<=10;i++)
		for(int j=0;j<10;j++)
		{
			for(int k=0;k<j-1;k++)
				f[i][j]+=f[i-1][k];
			for(int k=j+2;k<10;k++)
				f[i][j]+=f[i-1][k];
			sum[i]+=f[i][j];
		}
	printf("%d\n",calc(r+1)-calc(l));
}
