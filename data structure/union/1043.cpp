#include <stdio.h>
#include <algorithm>
using namespace std;
int n,m;
int fa[50010];
int s[50010];
int ans;	
int getfa(int x)
{
	if(fa[x]!=x)
	{
		int tmp=fa[x];
		fa[x]=getfa(tmp);
		s[x]=(s[x]+s[tmp])%300;
	}
	return fa[x];
}
void merge(int x,int y,int z)
{
	int fx=getfa(x);
	int fy=getfa(y);
	if(fx==fy)
	{
		if((s[x]+300+z)%300!=s[y])
			ans++;
		return;
	}
	fa[fy]=fx;
	s[fy]=(s[x]+z+300-s[y])%300;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		fa[i]=i;
	while(m--)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		merge(x,y,z);
	}
	printf("%d",ans);
}
