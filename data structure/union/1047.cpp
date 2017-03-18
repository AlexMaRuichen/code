#include <stdio.h>
#include <algorithm>
const int maxn=50010;
int n,m;
int fa[maxn];
int size[maxn];
int s[maxn];
int ans;
int getfa(int x)
{
	if(fa[x]!=x)
	{
		int tmp=fa[x];
		fa[x]=getfa(tmp);
		s[x]=(s[x]+s[tmp])%3;
	}
	return fa[x];
}
void merge(int opt,int x,int y)
{
	int fx=getfa(x);
	int fy=getfa(y);
	if(fx==fy)
	{
		if(opt==1&&s[x]!=s[y])
			ans++;
		if(opt==2&&s[x]!=(s[y]+2)%3)
			ans++;
	}
	else
	{
		fa[fy]=fx;
		s[fy]=(s[x]+(opt-1)+(3-s[y]))%3;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		fa[i]=i;
	while(m--)
	{
		int opt,x,y;
		scanf("%d%d%d",&opt,&x,&y);
		if(x>n||y>n||(opt==2&&x==y))
		{
			ans++;
			continue;
		}
		merge(opt,x,y);
	}
	printf("%d",ans);
}
