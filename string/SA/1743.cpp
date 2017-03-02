#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <string.h>
using namespace std;
const int maxn=20010;
int h[maxn];
int sa[maxn];
int n;
void Suffix_Array(int *s,int n)
{
	static int cnt[maxn];
	static int m[2][maxn];
	static int *id,*oid;
	id=m[0];
	oid=m[1];
	memset(id,0,sizeof(m[0]));
	memset(oid,0,sizeof(m[0]));
	memset(cnt,0,sizeof(cnt));
	memset(h,0,sizeof(h));
	for(int i=1;i<=n;i++)
		++cnt[s[i]];
	for(int i=1,t=0;i<=200;i++)
		if(cnt[i])
			id[i]=++t;
	partial_sum(cnt+1,cnt+200+1,cnt+1);
	for(int i=1;i<=n;i++)
		oid[i]=id[s[i]],sa[cnt[s[i]]--]=i;
	for(int k=1,cur=0;cur^n;k<<=1,swap(id,oid))
	{
		memset(cnt,0,sizeof(int)*(n+1));
		for(int i=1;i<=n;i++)
			++cnt[oid[i]];
		partial_sum(cnt+1,cnt+n+1,cnt+1);
		for(int i=n;i;i--)
			if(sa[i]>k)
				id[sa[i]-k]=cnt[oid[sa[i]-k]]--;
		for(int i=1;i<=k;i++)
			id[n-i+1]=cnt[oid[n-i+1]]--;
		for(int i=1;i<=n;i++)
			sa[id[i]]=i;
		cur=0;
		for(int i=1;i<=n;i++)
			id[sa[i]]=(sa[i]+k>n||sa[i-1]+k>n||oid[sa[i]]^oid[sa[i-1]]||oid[sa[i]+k]^oid[sa[i-1]+k])?++cur:cur;
	}
	swap(id,oid);
	for(int i=1;i<=n;i++)
		if(id[i]^1)
			for(int j=max(1,h[id[i-1]]-1);;j++)
				if(s[i+j-1]==s[sa[id[i]-1]+j-1])
					h[id[i]]=j;
			else
				break;
}
int a[maxn];
int s[maxn];
bool check(int x)
{
	int mn=sa[1],mx=sa[1];
	for(int i=2;i<=n;i++)
		if(h[i]<x)
			mn=mx=sa[i];
		else 
		{
			mn=min(mn,sa[i]);
			mx=max(mx,sa[i]);
			if(mx-mn>=x)
				return true;
		}
	return false;
}
void solve()
{
	int l=0,r=n/2,mid;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(check(mid))
			l=mid+1;
		else 
			r=mid;
	}
	if(l<5)
		puts("0");
	else 
		printf("%d\n",l);
}
int main()
{
	while(scanf("%d",&n)&&n)
	{
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),s[i]=a[i]-a[i-1]+100;
		Suffix_Array(s,n);
		int ans=0;
		for(int i=1;i<=n;i++)
			ans=max(ans,h[i]+1);
		solve();
	}
}
