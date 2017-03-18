#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e5;
int n,q;
char opt[10];
long long a[maxn+10];
int x,y,z;
struct segment_tree
{
	segment_tree *ls,*rs;
	long long lazy;
	long long sum;
	segment_tree()
	{
		ls=rs=NULL;
		lazy=sum=0;
	}
}*root;
void push_down(segment_tree* &x,int l,int r)
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
void build(segment_tree* &x,int l,int r)
{
	if(l==r)
	{
		x->sum=a[l];
		return;
	}
	int mid=(l+r)>>1;
	x->ls=new segment_tree();
	x->rs=new segment_tree();
	build(x->ls,l,mid);
	build(x->rs,mid+1,r);
	x->sum=x->ls->sum+x->rs->sum;
}
void modify(segment_tree* &x,int l,int r,int v,int L,int R)
{
	if(l==L&&r==R)
	{
		x->lazy+=v;
		x->sum+=v*(R-L+1);
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
long long query(segment_tree* &x,int l,int r,int L,int R)
{
	if(l==L&&R==r)
		return x->sum;
	push_down(x,L,R);
	int mid=(L+R)>>1;
	if(mid>=r)
		return query(x->ls,l,r,L,mid);
	else if(mid<l)
		return query(x->rs,l,r,mid+1,R);
	return query(x->ls,l,mid,L,mid)+query(x->rs,mid+1,r,mid+1,R);
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	root=new segment_tree();
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
