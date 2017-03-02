#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <utility>
using namespace std;
const int mod=99999997;
int n;
pair <int,int> a[100010];
pair <int,int> b[100010];
int c[100010];
int t[100010];
bool cmp(pair <int,int>a,pair <int,int>b)
{
	return a.first<b.first;
}
int ans;
void merge_sort(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	merge_sort(l,mid);
	merge_sort(mid+1,r);
	int cnt=l;
	int px=l,py=mid+1;
	while(cnt<=r)
	{
		if(px>mid)
			t[cnt++]=c[py++];
		else if(py>r)
			t[cnt++]=c[px++];
		else if(c[px]>c[py])
		{
			t[cnt++]=c[py++];
			(ans+=mid-px+1)%=mod;
		}
		else 
			t[cnt++]=c[px++];
	}
	for(int i=l;i<=r;i++)
		c[i]=t[i];
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i].first),a[i].second=i;
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i].first),b[i].second=i;;
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;i++)
		c[b[i].second]=a[i].second;
	merge_sort(1,n);
	printf("%d\n",ans);
}
