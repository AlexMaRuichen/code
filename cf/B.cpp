#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
char a[maxn];
int n;
int cntr,cntb;
int ans=~0u>>1;
int main()
{
	scanf("%d",&n);
	scanf("%s",a+1);
	for(int i=1;i<=n;i++)
		if((i&1)&&(a[i]!='r'))
			cntr++;
		else if(((i&1)==0)&&(a[i]!='b'))
			cntb++;
	ans=min(ans,max(cntr,cntb));
	cntr=cntb=0;
	for(int i=1;i<=n;i++)
		if((i&1)&&(a[i]!='b'))
			cntr++;
		else if(((i&1)==0)&&(a[i]!='r'))
			cntb++;
	ans=min(ans,max(cntr,cntb));
	printf("%d %d\n",ans,'.');
}
