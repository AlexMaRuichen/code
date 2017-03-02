#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=110;
int n,b;
int v[maxn];
int a[maxn];
int f[100001];
int ans=0;
int main()
{
	scanf("%d%d",&n,&b);
	for(int i=1;i<=b;i++)
		scanf("%d",&v[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=n;i>1;i--)
		if(a[i-1])
			a[i]-=a[i-1]-1;
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int j=1;j<=b;j++)
		for(int i=v[j];i<=100000;i++)
			f[i]=min(f[i],f[i-v[j]]+1);
	for(int i=1;i<=n;i++)
	{
		if(f[a[i]]==0x3f3f3f3f)
		{
			puts("-1");
			return 0;
		}
		ans+=f[a[i]];
	}
	printf("%d\n",ans);
}
