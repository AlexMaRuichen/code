#include <stdio.h>
#include <algorithm>
#include <map>
#include <string.h>
#define lowbit(x) ((x)&(-x))
using namespace std;
map <int,int> id;
long long bit[100010];
int n1,n2;
int p[100010];
int c;
long long ans;
void modify(int x,long long y)
{
	for(int i=x;i<=n1+n2;i+=lowbit(i))
		bit[i]+=y;
}
long long query(int x)
{
	long long ans=0;
	for(int i=x;i>=1;i-=lowbit(i))
		ans+=bit[i];
	return ans;
}
bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
	while(scanf("%d%d",&n1,&n2)==2)
	{
		memset(bit,0,sizeof(bit));
		ans=0;
		for(int i=n1;i>=1;i--)
		{
			scanf("%d",&p[i]);
			id[p[i]]=i;
		}
		for(int i=n1+1;i<=n1+n2;i++)
		{
			scanf("%d",&p[i]);
			id[p[i]]=i;
		}
		c=n1;
		sort(p+1,p+n1+n2+1,cmp);
		for(int i=1;i<=n1+n2;i++)
		{
			if(id[p[i]]>c)
			{
				ans+=id[p[i]]-c-1-(query(id[p[i]])-query(c));
				modify(id[p[i]],1);
				c=id[p[i]]-1;
			}
			else if(id[p[i]]==c)
				modify(id[p[i]],1);
			else
			{
				ans+=c-id[p[i]]-(query(c)-query(id[p[i]]));
				modify(id[p[i]],1);
				c=id[p[i]];
			}
		}
		printf("%lld\n",ans);
	}
}
