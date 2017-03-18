#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn=100010;
int n,q;
ll a[maxn];
char opt[10];
int x,y,z;
struct seg_tree
{
	seg_tree *ls,*rs;
	ll sum,lazy;
	seg_tree()
	{
		ls=rs=NULL;
		sum=lazy=0;
	}
}*root;
inline void push_down(seg_tree* &x,int l,int r)
{
	if(x->lazy&&x->ls!=NULL)
	{
		int mid=(l+r)>>1;
		x->ls->lazy+=x->lazy;
		x->rs->lazy+=x->lazy;
		x->ls->sum+=x->lazy*(mid-l+1);
		x->rs->sum+=x->lazy*(r-mid);
		x->lazy=0;
	}
}
inline void build(seg_tree* &x,int l,int r)
{
	if(l==r)
	{
		x->sum=a[l];
		return;
	}
	int mid=(l+r)>>1;
	x->ls=new seg_tree();
	x->rs=new seg_tree();
	build(x->ls,l,mid);
	build(x->rs,mid+1,r);
	x->sum=x->ls->sum+x->rs->sum;
}
inline void modify(seg_tree* &x,int l,int r,int v,int L,int R)
{
	if(l==L&&r==R)
	{
		x->sum+=v*(R-L+1);
		x->lazy+=v;
		return;
	}
	push_down(x,L,R);
	int mid=(L+R)>>1;
	if(mid>=r)
		modify(x->ls,l,r,v,L,mid);
	else if(mid<l)
		modify(x->rs,l,r,v,mid+1,R);
	else
	{
		modify(x->ls,l,mid,v,L,mid);
		modify(x->rs,mid+1,r,v,mid+1,R);
	}
	x->sum=x->ls->sum+x->rs->sum;
}
inline ll query(seg_tree* &x,int l,int r,int L,int R)
{
	if(l==L&&r==R)
		return x->sum;
	push_down(x,L,R);
	int mid=(L+R)>>1;
	if(mid>=r)
		return query(x->ls,l,r,L,mid);
	if(mid<l)
		return query(x->rs,l,r,mid+1,R);
	return query(x->ls,l,mid,L,mid)+query(x->rs,mid+1,r,mid+1,R);
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	root=new seg_tree();
	build(root,1,n);
	while(q--)
	{
		scanf("%s",opt);
		if(opt[0]=='C')
		{
			scanf("%d%d%d",&x,&y,&z);
			modify(root,x,y,z,1,n);
		}
		else if(opt[0]=='Q')
		{
			scanf("%d%d",&x,&y);
			printf("%lld\n",query(root,x,y,1,n));
		}
	}
}
