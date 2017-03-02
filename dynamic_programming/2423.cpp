#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=100010;
int n;
typedef pair<int,int> cow;
cow c[maxn];
char s[10];
int sum;
int ans;
int last[maxn<<1];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%s",&c[i].first,s);
		if(s[0]=='W')
			c[i].second=-1;
		else
			c[i].second=1;
	}
	sort(c+1,c+n+1);
	sum=n;
	memset(last,0x3f,sizeof(last));
	last[sum]=c[1].first;
	for(int i=1;i<n;i++)
	{
		sum+=c[i].second;
		last[sum]=min(last[sum],c[i+1].first);
	}
	for(int i=2*n;i>=0;i--)
		last[i]=min(last[i+2],last[i]);
	sum=n;
	for(int i=1;i<=n;i++)
	{
		sum+=c[i].second;
		ans=max(ans,c[i].first-last[sum]);
	}
	printf("%d\n",ans);
}
