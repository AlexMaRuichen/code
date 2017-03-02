#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <numeric>
using namespace std;
const int maxn=1e5+10;
int sa[maxn];
char r[maxn];
int s[maxn];
int h[maxn];
void init(int *s,int *h,int n)
{
	static int m[2][maxn];
	static int cnt[maxn];
	static int *id,*oId;
	int i,cur=0,t=0,k,j;
	id=m[0],oId=m[1];
	for(i=1;i<=n;i++)
		++cnt[s[i]];
	for(i=1;i<=26;i++)
		if(cnt[i])
			id[i]=++t;
	partial_sum(cnt+1,cnt+26+1,cnt+1);
	for(i=1;i<=n;i++)
		oId[i]=id[s[i]],sa[cnt[s[i]]--]=i;
	for(k=1;cur^n;k<<=1,swap(id,oId))
	{
		memset(cnt,0,sizeof(int)*(n+1));
		for(i=1;i<=n;i++)
			++cnt[oId[i]];
		partial_sum(cnt+1,cnt+n+1,cnt+1);
		for(i=n;i;i--)
			if(sa[i]>k)
				id[sa[i]-k]=cnt[oId[sa[i]-k]]--;
		for(i=1;i<=k;i++)
			id[n-i+1]=cnt[oId[n-i+1]]--;
		for(i=1;i<=n;i++)
			sa[id[i]]=i;
		cur=0;
		for(i=1;i<=n;i++)
			id[sa[i]]=(sa[i]+k>n||sa[i-1]+k>n||oId[sa[i]]^oId[sa[i-1]]||oId[sa[i]+k]^oId[sa[i-1]+k])?++cur:cur;
	}
	swap(id,oId);
	for(i=1;i<=n;i++)
		if(id[i]^1)
		{
			for(j=max(1,h[id[i-1]]-1);;j++)
				if(s[i+j-1]==s[sa[id[i]-1]+j-1])
					h[id[i]]=j;
				else
					break;
		}
}
int main()
{
	fread(r+1,1,100000,stdin);
	int n;
	for(n=1;r[n]&&r[n]^'\n';n++)
		s[n]=r[n]-'a'+1;
	init(s,h,--n);
	for(int i=1;i<=n;i++)
		printf("%d ",sa[i]);
	puts("");
	for(int i=2;i<=n;i++)
		printf("%d ",h[i]);
	puts("");
}
