#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn=160;
int n;
struct seg
{
	int l,r;
}s[maxn];
int ans;
int c1,c2;
bool cmp(seg a,seg b)
{
	return a.r<b.r;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&s[i].l,&s[i].r);
	sort(s+1,s+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		if(s[i].l>=c1)
			++ans,c1=s[i].r;
		else if(s[i].l>=c2)
			++ans,c2=s[i].r;
		if(c1<c2)
			c1^=c2^=c1^=c2;
	}
	printf("%d\n",ans);
}
