#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int cash;
int _n;
int n[20];
int d[20];
int D[2000];
int N[2000];
int tot;
int f[2][100010];
int tot_sum;
bool s;
void binary_expand(int x);
int bin,t;
int main()
{
	while(scanf("%d",&cash)==1)
	{
		s=false;
		tot=0;
		t=0;
		tot_sum=0;
		memset(f,0x3f,sizeof(f));
		scanf("%d",&_n);
		for(int i=1;i<=_n;i++)
		{
			scanf("%d%d",&n[i],&d[i]);
			tot_sum+=n[i];
			binary_expand(i);
		}
		f[0][0]=0;
		for(int i=1;i<=tot;i++)
			for(int k=0;k<=cash;k++)
				if(k>=D[i])
					f[i&1][k]=min(f[(i-1)&1][k],f[(i-1)&1][k-D[i]]+N[i]);
				else 
					f[i&1][k]=f[(i-1)&1][k];
		for(int i=cash;i;i--)
			if(f[tot&1][i]<=tot_sum)
			{
				printf("%d\n",i);
				s=true;
				break;
			}
		if(!s)
			puts("0");
	}
}
void binary_expand(int x)
{
	bin=1;
	while(n[x]-bin>0)
	{
		D[++t]=d[x]*bin;
		N[t]=bin;
		n[x]-=bin;
		bin<<=1;
		tot++;
	}
	if(n[x])
	{
		D[++t]=d[x]*n[x];
		N[t]=n[x];
		tot++;
	}
}
