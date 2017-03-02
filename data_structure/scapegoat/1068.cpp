#include <stdio.h>
#include <algorithm>
#define push(x) q[++r&mask]=x
#define front() q[l++&mask]
#define empty() (l==r+1)
#define update(x) x->size=x->ls->size+x->rs->size+1
using namespace std;
const int mask=(1<<20)-1;
const int maxn=200010;
typedef struct scapegoat
{
	scapegoat *fa,*ls,*rs;
	int val,size;
	scapegoat(){}
	scapegoat(const int &x);
	void* operator new(size_t);
}tree;
tree *q[mask+10];
int l=1,r=0;
tree mempool[maxn],*mark,*null=new tree(0),*root=null;
scapegoat :: scapegoat(const int &x)
{
	fa=ls=rs=null;
	val=x;
	size=x?1:0;
}
void* tree :: operator new(size_t)
{
	static tree *p=mempool,*g;
	if(!empty())
		g=front();
	else
		g=p++;
	return g;
}
int a[maxn];
tree* build(int l,int r)
{
	if(l>r)
		return null;
	int mid=l+r>>1;
	tree *x=new tree(a[mid]);
	x->ls=build(l,mid-1);
	x->rs=build(mid+1,r);
	x->ls->fa=x->rs->fa=x;
	update(x);
	return x;
}
void travel(tree *x)
{
	if(x->ls!=null)
		travel(x->ls);
	a[++a[0]]=x->val;
	if(x->rs!=null)
		travel(x->rs);
	push(x);
}
void insert(tree *&x,const int &y,tree *z)
{
	if(x==null)
	{
		x=new tree(y);
		x->fa=z;
		return ;
	}
	if(x->val>=y)
		insert(x->ls,y,x);
	else
		insert(x->rs,y,x);
	update(x);
	if(max(x->ls->size,x->rs->size)>x->size*8/10)
		mark=x;
}
tree *rebuild(tree *x)
{
	travel(x);
	return build(1,a[0]);
}
int n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		static int x;
		mark=NULL;
		scanf("%d",&x);
		insert(root,x,null);
		if(mark)
		{
			a[0]=0;
			if(mark==root)
			{
				root=rebuild(mark);
				root->fa=null;
			}
			else
			{
				tree *fa=mark->fa;
				if(mark==fa->ls)
					fa->ls=rebuild(mark),fa->ls->fa=fa;
				else
					fa->rs=rebuild(mark),fa->rs->fa=fa;
			}
		}
	}
	a[0]=0;
	travel(root);
	for(int i=1;i<=n;i++)
		printf("%d\n",a[i]);
}
