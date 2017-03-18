#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn=5010;
const int maxm=100010;
int n,m;
int a[maxn];
int c[maxm];
int f[maxn];
int main()
{
	memset(f,0x3f,sizeof(f));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=m;i++)
		scanf("%d",&c[i]);
	for(int i=m-1;i;i--)
		c[i]=min(c[i],c[i+1]);
	f[0]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			f[i]=min(f[i],f[j-1]+c[a[i]-a[j]+1]);
	printf("%d\n",f[n]);
}
