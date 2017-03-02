#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=10010;
const int maxm=20010*2;
int n,k,m;
int fa[maxn];
int size[maxn];
int mr;
struct edge
{
	int x,y,l1,l2;
}t[maxm];
bool cmp(edge a,edge b)
{
	if(a.l1!=b.l1)
		return a.l1<b.l1;
	return a.l2<b.l2;
}
void init()
{
	for(int i=1;i<=n;i++)
		fa[i]=i,size[i]=1;
}
int getfa(int x)
{
	if(fa[x]!=x)
		fa[x]=getfa(fa[x]);
	return fa[x];
}
void merge(int x,int y)
{
	x=getfa(x);
	y=getfa(y);
	if(x==y)
		return;
	if(size[x]>size[y])
		swap(x,y);
	fa[x]=y;
	size[y]+=size[x];
}
bool kruskal(int g)
{
	int ms=0;
	int tot=0;
	for(int i=1;i<m;i++)
	{
		int x=getfa(t[i].x);
		int y=getfa(t[i].y);
		if(x==y)
			continue;
		if(t[i].l1<=g)
		{
			merge(x,y);
			ms=max(ms,max(size[x],size[y]));
			tot++;
		}
		else if(t[i].l2<=g)
		{
			merge(x,y);
			ms=max(ms,max(size[x],size[y]));
		}
		else
			continue;
	}
	return ((ms==n)&&(tot>=k));
}
int main()
{
	scanf("%d%d%d",&n,&k,&m);
	
	for(int i=1;i<m;i++)
	{
		scanf("%d%d%d%d",&t[i].x,&t[i].y,&t[i].l1,&t[i].l2);
		mr=mr>t[i].l1?mr:t[i].l1;
	}
	sort(t+1,t+m,cmp);
	int l=0,r=mr;
	while(l<r)
	{
		init();
		int mid=(l+r)>>1;
		if(kruskal(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%d\n",l);
}
