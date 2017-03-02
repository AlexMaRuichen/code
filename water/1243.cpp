#include <stdio.h>
#include <algorithm>
#include <utility>
using namespace std;
pair <int,int> p[2000];
int n;
int sum;
int main()
{
	scanf("%d",&n);
	p[0].first=0;
	p[0].second=0;	
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		p[i].first=x;
		p[i].second=x-p[i-1].first;
		int ans=0;
		for(int j=i;j;j--)
		{
			ans++;
			if(p[j].second)
			{
				p[j].second--;
				break;
			}
		}
		if(i==1)
			printf("%d",ans);
		else
			printf(" %d",ans);
	}	
}
