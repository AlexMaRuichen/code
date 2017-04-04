#include <stdio.h>
#include <algorithm>
using namespace std;
int k,n;
int mul(int x,int y);
int cnt;
int f[1010];
int i;
int main()
{
	scanf("%d%d",&k,&n);
	while(cnt<=n)
	{
		f[++cnt]=mul(k,i);
		i++;
		int tmp=cnt;
		for(int i=1;i<tmp&&cnt<=n;i++)
			f[++cnt]=f[tmp]+f[i];	
	}
	printf("%d\n",f[n]);
}
int mul(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1)
			ans*=x;
		x*=x;
		y>>=1;
	}
	return ans;
}
