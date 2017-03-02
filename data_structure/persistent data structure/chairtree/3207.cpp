#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=200010;
const int key=29;
typedef unsigned long long ull;
struct seg_tree
{
	seg_tree *ls,*rs;
	int cnt;
}*root[maxn],mempool[maxn*50];
inline seg_tree* new_node(seg_tree *x,seg_tree *y,int z)
{
	static seg_tree *p=mempool;
	p->ls=x;
	p->rs=y;
	p->cnt=z;
	return p++;
}
inline seg_tree* build(seg_tree *x,ull hash,ull l,ull r)
{
	if(l==r)
		return new_node(NULL,NULL,x->cnt+1);
	ull mid=(l>>1)+(r>>1)+(l&r&1);
	if(mid>=hash)
		return new_node(build(x->ls,hash,l,mid),x->rs,x->cnt+1);
	else
		return new_node(x->ls,build(x->rs,hash,mid+1,r),x->cnt+1);
}
inline bool query(seg_tree *x,seg_tree *y,ull hash,ull l,ull r)
{
	if(y->cnt-x->cnt==0)
		return false;
	else if(l==r)
		return true;
	ull mid=(l>>1)+(r>>1)+(l&r&1);
	if(mid>=hash)
		return query(x->ls,y->ls,hash,l,mid);
	else
		return query(x->rs,y->rs,hash,mid+1,r);
}
ull sum[maxn];
ull ex=1;
int a[maxn];
int n,m,k;
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]*key+a[i];
	}
	for(int i=1;i<=k;i++)
		ex*=key;
	root[k-1]=new_node(mempool,mempool,0);
	for(int i=k;i<=n;i++)
		root[i]=build(root[i-1],sum[i]-sum[i-k]*ex,0,~0ull);
	for(int i=1;i<=m;i++)
	{
		static int x,y,z;
		static ull hash_val;
		hash_val=0;
		scanf("%d%d",&x,&y);
		for(int i=1;i<=k;i++)
			scanf("%d",&z),hash_val=hash_val*key+z;
		if(y-x+1<k)
			puts("Yes");
		else
			query(root[x+k-2],root[y],hash_val,0,~0ull)?puts("No"):puts("Yes");
	}
}
