#include <stdio.h>
#include <string.h>
#include <algorithm>
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int maxn=1e5;
struct cow
{
	int l,r,id,ans;
}c[maxn+10];
int bit[maxn+10];
int n;
void modify(int x,int y)
{
	for(int i=x;i<=maxn+1;i+=lowbit(i))
		bit[i]+=y;
}
bool cmpseg(cow a,cow b)
{
	if(a.r!=b.r)
		return a.r>b.r;
	return a.l<b.l;
}
bool cmpid(cow a,cow b)
{
	return a.id<b.id;
}
int query(int x)
{
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i))
		ans+=bit[i];
	return ans;
}
int main()
{
	while(scanf("%d",&n)==1&&n)
	{
		memset(c,0,sizeof(c));
		memset(bit,0,sizeof(bit));
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&c[i].l,&c[i].r);
			c[i].l++;
			c[i].r++;
			c[i].id=i;
		}
		sort(c+1,c+n+1,cmpseg);
		for(int i=1;i<=n;i++)
		{
			if(c[i].l==c[i-1].l&&c[i].r==c[i-1].r)
				c[i].ans=c[i-1].ans;
			else
				c[i].ans+=query(c[i].l);
			modify(c[i].l,1);
		}
		sort(c+1,c+n+1,cmpid);
		for(int i=1;i<=n;i++)
			printf("%d ",c[i].ans);
		puts("");
	}
}
