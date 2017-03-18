#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=110;
const int maxm=1000010;
const int seed[]={10007,11113,12007,13001,14009};
int n,m;
char s[10010];
int a[5][maxn];
int r[5][15000];
int p[5][maxn];
int cnt;
int ans[maxm];
int main()
{
	scanf("%d%d",&n,&m);
	register int i,j,k;
	for(i=0;i<=n;i++)
	{
		static int len;
		static bool flag;
		scanf("%s",s+1);
		len=strlen(s+1);
		flag=false;
		for(k=0;k<5;k++)
			if(s[1]!='-')
				a[k][i]=s[1]-'0';
			else
				a[k][i]=0,flag=true;
		for(k=0;k<5;k++)
		{
			for(j=2;j<=len;j++)
				a[k][i]=(a[k][i]*10+s[j]-'0')%seed[k];
			if(flag)
				a[k][i]=-a[k][i];
		}
	}
	for(k=0;k<5;k++)
		for(i=1;i<seed[k];i++)
		{
			p[k][0]=1;
			for(j=1;j<=n;j++)
				p[k][j]=(p[k][j-1]*i)%seed[k];
			for(j=0;j<=n;j++)
				r[k][i]=(r[k][i]+p[k][j]*a[k][j])%seed[k];
		}
	for(i=1;i<=m;i++)
	{
		for(k=0;k<5;k++)
			if(r[k][i%seed[k]])
				goto lableA;
		++cnt;
		ans[cnt]=i;
		lableA:;
	}
	printf("%d\n",cnt);
	for(i=1;i<=cnt;i++)
		printf("%d\n",ans[i]);
}
