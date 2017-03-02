#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <string.h>
using namespace std;
const int maxn=60010;
int n;
char r[5];
int s[maxn];
int sa[maxn];
int m[2][maxn];
int *id=m[0],*oid=m[1];
void Suffix_Array(int *s,int n)
{
	static int cnt[maxn];
	for(int i=1;i<=n;i++)
		++cnt[s[i]];
	for(int i=1,t=0;i<=27;i++)
		if(cnt[i])
			id[i]=++t;
	partial_sum(cnt+1,cnt+27+1,cnt+1);
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
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%1s",r),s[i]=r[0]-'A'+2;
	s[++n]=1;
	for(int i=n-1;i;i--)
		s[n+i]=s[n-i];
	n=(n<<1)-1;
	Suffix_Array(s,n);
	int l=1,r=n>>1;
	swap(id,oid);
	int cnt=0;
	while(l<=r)
	{
		if(s[l]>s[r])
			putchar(s[r--]+'A'-2);
		else if(s[l]<s[r])
			putchar(s[l++]+'A'-2);
		else if(id[l]<id[n-r+1])
			putchar(s[l++]+'A'-2);
		else 
			putchar(s[r--]+'A'-2);
		if((++cnt)%80==0)
			putchar('\n');
	}
	if(cnt%80)
		puts("");
}
