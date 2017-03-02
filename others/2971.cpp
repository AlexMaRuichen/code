#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
typedef pair<int,int> bale;
int n,b;
bale bales[maxn];
int ans=~0u>>1;
int main()
{
	scanf("%d%d",&n,&b);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&bales[i].second,&bales[i].first);
	sort(bales+1,bales+n+1);
	int pos=lower_bound(bales+1,bales+n+1,bale(b,0))-bales;
	int j=pos;
	for(int i=pos-1;i;i--)
		while(j<=n&&bales[j].first<=bales[i].first+bales[i].second)
			ans=min(ans,bales[j].first-bales[i].first-bales[j].second),j++;
	j=pos-1;
	for(int i=pos;i<=n;i++)
		while(j&&bales[i].first-bales[i].second<=bales[j].first)
			ans=min(ans,bales[i].first-bales[j].first-bales[j].second),j--;
	if(ans==~0u>>1)
		puts("-1");
	else
		printf("%d\n",max(ans,0));
}
