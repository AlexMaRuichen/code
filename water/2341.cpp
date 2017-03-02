#include <stdio.h>
#include <algorithm>
using namespace std;
int n,k;
char s[10];
int dis;
int c;
int cnt;
typedef pair <int,int> point;
point p[200010];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%s",&dis,s);
		if(s[0]=='L')
		{
			p[++cnt]=point(c,-1);
			c-=dis;
			p[++cnt]=point(c,1);
		}
		else
		{
			p[++cnt]=point(c,1);
			c+=dis;
			p[++cnt]=point(c,-1);
		}
	}
	sort(p+1,p+cnt+1);
	int t=0,ans=0;
	for(int i=1;i<cnt;i++)
	{
		t+=p[i].second;
		if(t>=k)
			ans+=p[i+1].first-p[i].first;
	}
	printf("%d\n",ans);
}
