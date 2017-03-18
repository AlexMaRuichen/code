#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn=100010;
int n,p,m,opt;
ll a[maxn];
struct seg_tree
{
	seg_tree *ls,*rs;
	ll alazy,mlazy,sum;
	seg_tree()
	{
		ls=rs=NULL;
		alazy=sum=0;
		mlazy=1;
	}
}*root;
inline void push_down(seg_tree* &x,int l,int r)
{
	if(x->alazy&&x->ls!=NULL)
	{
		int mid=(l+r)>>1;
		x->ls->alazy=(x->ls->alazy*x->mlazy+x->alazy)%p;
		x->rs->alazy=(x->rs->alazy*x->mlazy+x->alazy)%p;
		(x->ls->mlazy*=x->mlazy)%=p;
		(x->rs->mlazy*=x->mlazy)%=p;
		(x->ls->sum*=x->mlazy)%=p;
		(x->ls->sum+=x->alazy*(mid-l+1))%=p;
		(x->rs->sum*=x->mlazy)%=p;
		(x->rs->sum*=x->alazy*(r-mid))%=p;
		x->alazy=0;
		x->mlazy=1;
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
	x->sum=(x->ls->sum+x->rs->sum)%p;
}
inline void modify(seg_tree* &x,int l,int r,ll va,ll vm,int L,int R)
{
	push_down(x,L,R);
	if(l==L&&r==R)
	{
		(x->alazy+=va)%=p;
		(x->mlazy*=vm)%=p;
		(x->sum*=vm)%=p;
		(x->sum+=va*(R-L+1))%=p;
		return;
	}
	int mid=(L+R)>>1;
	if(mid>=r)
		modify(x->ls,l,r,va,vm,L,mid);
	else if(mid<l)
		modify(x->rs,l,r,va,vm,mid+1,R);
	else
	{
		modify(x->ls,l,mid,va,vm,L,mid);
		modify(x->rs,mid+1,r,va,vm,mid+1,R);
	}
	x->sum=(x->ls->sum+x->rs->sum)%p;
}
inline ll query(seg_tree* &x,int l,int r,int L,int R)
{
	push_down(x,L,R);
	if(l==L&&r==R)
		return x->sum%p;
	int mid=(L+R)>>1;
	if(mid>=r)
		return query(x->ls,l,r,L,mid)%p;
	if(mid<l)
		return query(x->rs,l,r,mid+1,R)%p;
	return (query(x->ls,l,mid,L,mid)+query(x->rs,mid+1,r,mid+1,R))%p;
}
int main()
{
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	root=new seg_tree();
	build(root,1,n);
	scanf("%d",&m);
	while(m--)
	{
		static ll x,y,z;
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%lld%lld%lld",&x,&y,&z);
			modify(root,x,y,0,z,1,n);
		}
		else if(opt==2)
		{
			scanf("%lld%lld%lld",&x,&y,&z);
			modify(root,x,y,z,1,1,n);
		}
		else if(opt==3)
		{
			scanf("%lld%lld",&x,&y);
			printf("%lld\n",query(root,x,y,1,n));
		}
	}
}
