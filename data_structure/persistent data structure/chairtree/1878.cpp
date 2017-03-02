#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1000010;
const int N=1000000;
struct chairtree
{
	chairtree *ls,*rs;
	int cnt;
	chairtree(){}
	chairtree(chairtree *ls,chairtree *rs,int cnt):ls(ls),rs(rs),cnt(cnt){}
	void* operator new(size_t)
	{
		static chairtree *l,*r;
		if(l==r)
			r=(l=new chairtree[1<<15])+(1<<15);
		return l++;
	}
}*root[maxn];
chairtree* build(chairtree *x,int v,int l,int r)
{
	if(l==r)
		return new chairtree(NULL,NULL,x->cnt+1);
	int mid=l+r>>1;
	if(mid>=v)
		return new chairtree(build(x->ls,v,l,mid),x->rs,x->cnt+1);
	else
		return new chairtree(x->ls,build(x->rs,v,mid+1,r),x->cnt+1);
}
int query(chairtree *x,chairtree *y,int l,int r,int L,int R)
{
	if(!(y->cnt-x->cnt))
		return 0;
	if(l==L&&r==R)
		return y->cnt-x->cnt;
	int mid=L+R>>1;
	if(mid>=r)
		return query(x->ls,y->ls,l,r,L,mid);
	else if(mid<=l)
		return query(x->rs,y->rs,l,r,mid+1,R);
	else
		return query(x->ls,y->ls,l,mid,L,mid)+
			   query(x->rs,y->rs,mid+1,r,mid+1,R);	
}
int last[maxn];
int main()
{
	root[0]=new chairtree();
	root[0]->ls=root[0]->rs=root[0];
	root[0]->cnt=0;
	int n,m;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		root[i]=build(root[i-1],last[x],0,N);
		last[x]=i;
	}	
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",query(root[x-1],root[y],0,x-1,0,N));
	}
}
