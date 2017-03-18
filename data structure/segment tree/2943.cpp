#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=100010;
int n,q;
struct seg_tree
{
	seg_tree *ls,*rs;
	int mx;
	seg_tree()
	{
		ls=rs=NULL;
		mx=0;
	}
	void* operator new(size_t);
}*root,Tdata[262150];
void* seg_tree::operator new(size_t)
{
	static seg_tree *p=Tdata;
	return p++;
}
int a[maxn];
void build(seg_tree* &x,int l,int r)
{
	if(l==r)
	{
		x->mx=a[l];
		return;
	}
	int mid=(l+r)>>1;
	x->ls=new seg_tree();
	x->rs=new seg_tree();
	build(x->ls,l,mid);
	build(x->rs,mid+1,r);
	x->mx=max(x->ls->mx,x->rs->mx);
}
int query(seg_tree* &x,int l,int r,int L,int R)
{
	if(l==L&&r==R)
		return x->mx;
	int mid=(L+R)>>1;
	if(mid>=r)
		return query(x->ls,l,r,L,mid);
	else if(mid<l)
		return query(x->rs,l,r,mid+1,R);
	else 
		return max(query(x->ls,l,mid,L,mid),query(x->rs,mid+1,r,mid+1,R));
}
void modify(seg_tree* &x,int p,int v,int L,int R)
{
	if(p==L&&L==R)
	{
		x->mx=v; 
		return;
	}
	int mid=(L+R)>>1;
	if(mid>=p)
		modify(x->ls,p,v,L,mid);
	else 
		modify(x->rs,p,v,mid+1,R);
	x->mx=max(x->ls->mx,x->rs->mx);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	root=new seg_tree();
	build(root,1,n);
	scanf("%d",&q);
	int opt,rx,ry,x,y,last_ans=0;
	while(q--)	
	{

		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1)
		{
			rx=min((x+last_ans)%n+1,(y+last_ans)%n+1);
			ry=max((x+last_ans)%n+1,(y+last_ans)%n+1);
			last_ans=query(root,rx,ry,1,n);
			printf("%d\n",last_ans);
		}
		else 
		{
			rx=(x+last_ans)%n+1;
			ry=(y+last_ans)%n+1;
			modify(root,rx,ry,1,n);
		}
	}
}
