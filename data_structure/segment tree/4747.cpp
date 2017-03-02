#include <stdio.h>
#include <algorithm>
using namespace std;
const int N=1e9;
struct seg_tree
{
	seg_tree *ls,*rs;
	int cnt;
	seg_tree(){ls=rs=NULL,cnt=0;}
}*root;
void insert(seg_tree *&x,int p,int l,int r)
{
	if(!x)
		x=new seg_tree();
	++x->cnt;
	if(l==r)
		return;
	int mid=l+r>>1;
	if(mid>=p)
		insert(x->ls,p,l,mid);
	else
		insert(x->rs,p,mid+1,r);
}
int query(seg_tree *x,int l,int r,int L,int R)
{
	if(!x)
		return 0;
	if(!x->cnt)
		return 0;
	if(L==l&&r==R)
		return x->cnt;
	int mid=L+R>>1;
	if(mid>=r)
		return query(x->ls,l,r,L,mid);
	else if(mid<l)
		return query(x->rs,l,r,mid+1,R);
	else
		return query(x->ls,l,mid,L,mid)+query(x->rs,mid+1,r,mid+1,R);
}
int n,q;
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		insert(root,x,1,N);
	}
	for(int i=1;i<=q;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",query(root,x,y,1,N));
	}
}
