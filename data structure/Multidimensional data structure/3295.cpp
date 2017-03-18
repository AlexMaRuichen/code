#include <stdio.h>
#include <algorithm>
#include <string.h>
#define lowbit(x) (x)&(-x) 
using namespace std;
const int maxn=100010;
struct seg_tree
{
	seg_tree *ls,*rs;
	int cnt;
	void* operator new(size_t);
}*root[maxn],mempool[maxn*70];
void* seg_tree :: operator new(size_t)
{
	static seg_tree *p=mempool;
	return p++;
}
void insert(seg_tree *&x,int v,int l,int r)
{
	if(!x)
		x=new seg_tree();
	++x->cnt;
	if(l==r)
		return;
	int mid=l+r>>1;
	if(mid>=v)
		insert(x->ls,v,l,mid);
	else
		insert(x->rs,v,mid+1,r);
}
int query(seg_tree *x,int v,int l,int r)
{
	if(!x)
		return 0;
	if(!x->cnt)
		return 0;
	if(l==r)
		return x->cnt;
	int mid=l+r>>1;
	if(mid>=v)
		return query(x->ls,v,l,mid);
	else
		return (x->ls?x->ls->cnt:0)+query(x->rs,v,mid+1,r);
}
int n,m;
int a[maxn];
int pos[maxn];
void INSERT(int x,int y)
{
	for(int i=x;i<=n;i+=lowbit(i))
		insert(root[i],y,1,n);
}

int QUERY(int x,int y)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans+=query(root[i],y,1,n);
	return ans;
}
long long ans;
int bit[maxn];
int get(int x)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans+=bit[i];
	return ans;
}
void update(int x)
{
	for(int i=x;i<=n;i+=lowbit(i))
		++bit[i];
}
int lmx[maxn];
int rmx[maxn];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),
		pos[a[i]]=i,
		ans+=(lmx[i]=get(n)-get(a[i])),
		update(a[i]);
	for(int i=n;i;i--)
		bit[i]=0;
	for(int i=n;i;i--)
		rmx[i]=get(a[i]),
		update(a[i]);

	for(int i=1;i<=m;i++)
	{
		printf("%lld\n",ans);
		static int x;
		scanf("%d",&x);
		x=pos[x];
		ans-=lmx[x]+rmx[x]-(QUERY(x-1,n)-QUERY(x-1,a[x]))-(QUERY(n,a[x])-QUERY(x,a[x]));
		INSERT(x,a[x]);
	}
}

