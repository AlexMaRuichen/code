#include <stdio.h>
#include <algorithm>
#define lowbit(x) (x)&(-x)
using namespace std;
const int maxn=20010;
const int N=20000;
struct point
{
	int x,y,pos,ans;
}p[maxn];
bool cmp(const point &a,const point &b)
{
	return a.x^b.x?a.x<b.x:a.y<b.y;
}
bool rec(const point &a,const point &b)
{
	return a.pos<b.pos;
}
int bit[maxn];
int n;
void update(int x,int y)
{
	for(int i=x;i<=N;i+=lowbit(i))
		bit[i]=max(bit[i],y);
}
int query(int x)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans=max(bit[i],ans);
	return ans;
}
void del(int x)
{
	for(int i=x;i<=N;i+=lowbit(i))
		bit[i]=0;
}
int f[maxn];
int ans;
void CDQ(int l,int r)
{
	if(l==r)
		return;
	int mid=l+r>>1;
	CDQ(l,mid);
	sort(p+l,p+mid+1,cmp);
	sort(p+mid+1,p+r+1,cmp);
	int i=l,j=mid+1;
	while(j<=r)
	{
		while(i<=mid&&p[i].x<p[j].x)
			update(p[i].y,p[i].ans),++i;
		p[j].ans=max(query(p[j].y)+1,p[j].ans);
		ans=max(ans,p[j].ans);
		++j;
	}
	for(i=l;i<=mid;i++)
		del(p[i].y);
	sort(p+l,p+r+1,rec);
	CDQ(mid+1,r);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].x,&p[i].y),p[i].ans=1,p[i].pos=i;
	CDQ(1,n);
	printf("%d\n",ans);
}
