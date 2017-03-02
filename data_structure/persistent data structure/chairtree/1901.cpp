#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=10010;
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
}*root[maxn],Tdata[maxn*50],*null;
void* seg_tree :: operator new(size_t)
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
void add(seg_tree* &x,seg_tree* bak,int v,int l,int r)
{
	x=new seg_tree();
	x->cnt=bak->cnt+1;
	if(l==r)
		return;
	x->ls=bak->ls;
	x->rs=bak->rs;
	int mid=(l+r)>>1;
	if(mid>=v)
		add(x->ls,bak->ls,v,l,mid);
	else
		add(x->rs,bak->rs,v,mid+1,r);
}
void del(seg_tree* &x,seg_tree* bak,int v,int l,int r)
{
	x=new seg_tree();
	x->cnt=bak->cnt-1;
	if(l==r)
		return;
	x->ls=bak->ls;
	x->rs=bak->rs;
	int mid=(l+r)>>1;
	if(mid>=v)
		del(x->ls,bak->ls,v,l,mid);
	else
		del(x->rs,bak->rs,v,mid+1,r);
}
int main()
{
	
}
