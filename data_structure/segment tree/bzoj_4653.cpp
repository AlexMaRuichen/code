#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=500010;
int a[maxn];
int n,m;
int ans=~0u>>1;
struct seg
{
	int l,r,len;
}s[maxn];
bool cmp(seg a,seg b)
{
	return a.len>b.len;
}
struct segment_tree
{
	segment_tree *ls,*rs;
	int sum=0,num=0;
	segment_tree()
	{
		ls=rs=NULL;
		sum=num=0;
	}
}*root;
inline void build(segment_tree* &x,int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	x->ls=new segment_tree();
	x->rs=new segment_tree();
	build(x->ls,l,mid);
	build(x->rs,mid+1,r);
}
int main()
{
	root=new segment_tree();
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&s[i].l,&s[i].r);
		s[i].len=s[i].r-s[i].l;
	}
}
