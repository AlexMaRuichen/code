#include <stdio.h>
#include <algorithm>
using namespace std;
int n,a;
int x[200010];
int lower_bound(int x);
int upper_bound(int x);
int ans;
int main()
{
	freopen("add.in","r",stdin);
	freopen("add.out","w",stdout);
	scanf("%d%d",&n,&a);
	for(int i=1;i<=n;i++)
		scanf("%d",&x[i]);
	sort(x+1,x+n+1);
	int last=0;
//	for(int i=1;i<=n;i++)
//		printf("%d ",x[i]);
//	puts("");
	for(int i=1;i<=n;i++)
	{
		if(last!=x[i]&&x[lower_bound(x[i])]==x[i]&&x[lower_bound(x[i]+a)]==x[i]+a)
		{
			last=x[i];
			int x1,x2,y1,y2;
			x1=lower_bound(x[i]);
			x2=upper_bound(x[i]);
			y1=lower_bound(x[i]+a);
			y2=upper_bound(x[i]+a);
			if(x[x1]==x[i]&&x[y1]==x[i]+a)
				/*printf("%d %d %d %d\n",x1,x2,y1,y2),*/ans+=(x2-x1)*(y2-y1);
		}
	}
	printf("%d",ans);
}
int lower_bound(int m)
{
	int l=0,r=n+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(x[mid]>=m)
			r=mid;
		else	
			l=mid+1;
	}
	return l;
}
int upper_bound(int m)
{
	int l=0,r=n+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(x[mid]>m)
			r=mid;
		else	
			l=mid+1;
	}
	return l;
}
