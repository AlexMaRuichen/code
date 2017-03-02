#include <bits/stdc++.h>
using namespace std;
#define N 110000
int has[N],tr[N],rank[N],sa[N],h[N],len;
char s[N];
int cmp(int x,int y,int k)
{
	if(x+k>len||y+k>len)return 0;
	return rank[x]==rank[y]&&rank[x+k]==rank[y+k];
}
void getsa()
{
	int i,cnt;
	for(i=1;i<=len;i++)
		has[s[i]]++;
	for(i=1,cnt=0;i<=128;i++)
		if(has[i])
			tr[i]=++cnt;
	for(i=1;i<=128;i++)
		has[i]+=has[i-1];
	for(i=1;i<=len;i++)
		rank[i]=tr[s[i]],sa[has[s[i]]--]=i;
	for(int k=1;cnt!=len;k<<=1)
	{
		for(i=1;i<=len;i++)
			has[i]=0;
		for(i=1;i<=len;i++)
			has[rank[i]]++;
		for(i=1;i<=len;i++)
			has[i]+=has[i-1];
		for(i=len;i>=1;i--)
			if(sa[i]>k)
				tr[sa[i]-k]=has[rank[sa[i]-k]]--;
		for(i=1;i<=k;i++)
			tr[len-i+1]=has[rank[len-i+1]]--;
		for(i=1;i<=len;i++)
			sa[tr[i]]=i;
		for(i=1,cnt=0;i<=len;i++)
			tr[sa[i]]=cmp(sa[i],sa[i-1],k) ? cnt:++cnt;
		for(i=1;i<=len;i++)
			rank[i]=tr[i];
	}
	for(i=1;i<=len;i++)
	{
		if(rank[i]==1)continue;
		for(int j=max(1,h[rank[i-1]]-1);;j++)
		{
			if(s[i+j-1]==s[sa[rank[i]-1]+j-1])h[rank[i]]=j;
			else break;
		}
	}
}
int main()
{
	//freopen("tt.in","r",stdin);
	scanf("%s",s+1);
	len=strlen(s+1);
	getsa();
	for(int i=1;i<=len;i++)printf("%d ",sa[i]);
	puts("");
	for(int i=2;i<=len;i++)printf("%d ",h[i]);
	puts("");
	return 0;
}

