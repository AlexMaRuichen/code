#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
int n,m;
int a[maxn];
int b[maxn];
struct seg_tree
{
	seg_tree *ls,*rs;
	int cnt;
	seg_tree()
	{
		ls=rs=NULL;
		cnt=0;
	}
	void* operator new(size_t);
}*root[maxn],Tdata[maxn*20];
void* seg_tree :: operator new (size_t)
{
	static seg_tree *p=Tdata;
	return p++;
}
void build(seg_tree* &x,int l,int r)
{
	x=new seg_tree();
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(x->ls,l,mid);
	build(x->rs,mid+1,r);
}
void insert(seg_tree *&x,seg_tree *bak,int v,int l,int r)
{
	x=new seg_tree();
	x->cnt=bak->cnt+1;
	if(l==r)
		return;
	x->ls=bak->ls;
	x->rs=bak->rs;
	int mid=(l+r)>>1;
	if(mid>=v)
		insert(x->ls,bak->ls,v,l,mid);
	else
		insert(x->rs,bak->rs,v,mid+1,r);
}
int query(seg_tree *x,seg_tree *y,int k,int l,int r)
{
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	if(y->ls->cnt-x->ls->cnt>=k)
		return query(x->ls,y->ls,k,l,mid);
	else 
		return query(x->rs,y->rs,k-(y->ls->cnt-x->ls->cnt),mid+1,r);
}
void print(seg_tree *x,int l,int r)
{
	if(!x)
		return;
	if(l==r&&x->cnt)
		printf("%d\n",l);
	int mid=(l+r)>>1;
	print(x->ls,l,mid);
	print(x->rs,mid+1,r);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(b+1,b+n+1,a[i])-b;
	build(root[0],1,n);
	for(int i=1;i<=n;i++)
		insert(root[i],root[i-1],a[i],1,n);
	for(int i=1;i<=m;i++)
	{
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		printf("%d\n",b[query(root[x-1],root[y],z,1,n)]);
	}
}
