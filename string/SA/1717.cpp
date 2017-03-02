#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <numeric>
using namespace std;
const int maxn=20010;
const int N=1000000;
int sa[maxn];
int a[maxn];
int h[maxn];
int n,k;
void Suffix_Array(int *s,int n)
{
	static int cnt[N+10];
	static int m[2][N+10];
	static int *id=m[0],*oid=m[1];
	for(int i=1;i<=n;i++)
		++cnt[s[i]];
	for(int i=1,t=0;i<=N;i++)
		if(cnt[i])
			id[i]=++t;
	partial_sum(cnt+1,cnt+N+1,cnt+1);
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
bool check(int x)
{
	for(int l=1,r=1;l<=n;l=r+1,r=l)
	{
		while(h[r+1]>=x)
			++r;
		if(r-l>=k-1)
			return true;
	}
	return false;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	Suffix_Array(a,n);
	int l=0,r=20001,mid;
	while(l<r)
	{
		mid=l+r>>1;
		if(check(mid))
			l=mid+1;
		else
			r=mid;
	}
	printf("%d\n",l-1);
}
