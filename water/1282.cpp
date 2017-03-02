#include <stdio.h>
#include <algorithm>
using namespace std;
int h[10];
int ans;
int main()
{
	for(int i=1;i<=7;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		h[i]=x+y;
		ans=max(h[i],ans);
	}
	if(ans<=8)
	{
		puts("0");
		return 0;
	}
	else
		for(int i=1;i<=7;i++)
			if(h[i]==ans)
			{
				printf("%d",i);
				return 0;
			}
}
