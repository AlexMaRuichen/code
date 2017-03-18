#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int sum;
int w[110];
int totalw;
int n;
int t;
int f[100010];
bool v[110];
int fa[100010];
int main()
{
	scanf("%d",&totalw);
	scanf("%d",&n);
	if(totalw==0)
	{
		for(int i=1;i<=n;i++)
			printf("%d ",i);
		return 0;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	f[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=totalw;j>=w[i];j--)
		{
			if(f[j-w[i]])
			{
				if(f[j]==0)
					f[j]=1,fa[j]=i;
				else 
					f[j]=-1;
			}
			else if(f[j-w[i]]==-1)
				f[j]=-1;
		}
	if(!f[totalw]||f[totalw]==-1)
	{
		printf("%d\n",f[totalw]);
		return 0;
	}
	int s=totalw;
	while(s!=0)
	{
		v[fa[s]]=true;
		s-=w[fa[s]];
	}
	for(int i=1;i<=n;i++)
		if(!v[i])
			printf("%d ",i);
}
