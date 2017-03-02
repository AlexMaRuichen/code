#include <stdio.h>
#include <algorithm>
using namespace std;
int cnt;
int n;
int tcnt;
int ans=~0u>>1;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&c[i].x,&c[i].id);
		if(m[c[i].id]==0)
			cnt++;
		m[c[i].id]++;
	}
	sort(c+1,c+n+1,cmp);
	int l=1,r=1;
	while(l<=n)
	{
		if(t[c[l].id]==0)
			++tcnt;
		++t[c[l].id];
		if(cnt==tcnt)
		{
			while(tcnt>=cnt)
			{
				--t[c[r].id];
				if(t[c[r].id]==0)
					--tcnt;
				++r;
			}
			ans=min(ans,c[l].x-c[r-1].x);
		}
		++l;
	}
	printf("%d\n",ans);
}
