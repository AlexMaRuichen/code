#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int w;
bool flag;
int n,m;
int fa[110];
int s[110];
int getfa(int x)
{
	if(fa[x]!=x)
	{
		int tmp=fa[x];
		fa[x]=getfa(tmp);
		s[x]+=s[tmp];
	}
	return fa[x];
}
void merge(int x,int y,int z)
{
	int fx=getfa(x);
	int fy=getfa(y);
	if(fx==fy)
	{
		if(s[y]-s[x]!=z)
			flag=true;
		return;
	}
	fa[fx]=fy;
	s[fx]=s[y]-s[x]-z;
}
int main()
{
	scanf("%d",&w);
	while(w--)
	{
		memset(s,0,sizeof(s));
		flag=false;
		scanf("%d%d",&n,&m);
		for(int i=0;i<=n;i++)
			fa[i]=i;
		while(m--)
		{
			int s,t,v;
			scanf("%d%d%d",&s,&t,&v);
			if(!flag)
				merge(s-1,t,v);
		}
		if(flag)
			puts("false");	
		else
			puts("true");
	}
}
