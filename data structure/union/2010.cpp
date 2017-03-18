#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
char m[]="M";
char q[]="C";
char opt[10];
int p;
int fa[30010];
int s[30010];
int getfa(int x);
void merge(int x,int y);
int main()
{
	scanf("%d",&p);
	for(int i=1;i<=30000;i++)
		fa[i]=i,s[i]=1;
	for(int i=1;i<=p;i++)
	{
		int x,y;
		scanf("%s%d",opt,&x);
		if(!strcmp(opt,m))
		{
			scanf("%d",&y);
			merge(x,y);
		}
		else if(!strcmp(opt,q))
		{
			printf("%d\n",s[x]-s[fa[x]]);
		}
	}
	for(int i=1;i<=10;i++)
		printf("%d ",s[i]);
}
int getfa(int x)
{
	if(fa[x]!=x)
	{
		int tmp=fa[x];
		fa[x]=getfa(tmp);
		s[x]=(s[x]+s[tmp]);
	}
	return fa[x];
}
void merge(int x,int y)
{
	int fx=getfa(x);
	int fy=getfa(y);
	if(fx==fy)
		return;
	fa[fx]=fy;
	getfa(x);
}
