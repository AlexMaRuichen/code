#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e6+10;
typedef long long ll;
struct heap
{
	heap *ls,*rs;
	int val,dis,size;
	heap();
	heap(int x);
	void* operator new(size_t);
}*root[maxn],nil,*null=&nil,mem[maxn];
heap :: heap()
{
	ls=rs=this;
	val=size=0;
	dis=-1;
}
heap :: heap(int x)
{
	ls=rs=null;
	val=x;
	dis=0;
	size=1;
}
void* heap :: operator new(size_t)
{
	static heap *p=mem;
	return p++;
}
heap* merge(heap *x,heap *y)
{
	if(x==null)
		return y;
	if(y==null)
		return x;
	if(x->val<y->val)
		swap(x,y);
	x->rs=merge(x->rs,y);
	x->size=x->ls->size+x->rs->size+1;
	if(x->ls->dis<x->rs->dis)
		swap(x->ls,x->rs);
	x->dis=x->rs->dis+1;
	return x;
}
void pop(heap *&x)
{
	x=merge(x->ls,x->rs);
}
int n;
int a[maxn];
int size[maxn];
int cnt;
int l[maxn];
int r[maxn];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),a[i]-=i;
	for(int i=1;i<=n;i++)
	{
		++cnt;
		root[cnt]=new heap(a[i]);
		size[cnt]=1;
		l[cnt]=r[cnt]=i;
		while(cnt>1&&root[cnt-1]->val>root[cnt]->val)
		{
			--cnt;
			root[cnt]=merge(root[cnt],root[cnt+1]);
			size[cnt]+=size[cnt+1];
			r[cnt]=r[cnt+1];
			while((root[cnt]->size<<1)>size[cnt]+1)
				pop(root[cnt]);
		}
	}
	ll ans=0;
	for(int i=1;i<=cnt;i++)
		for(int j=l[i],t=root[i]->val;j<=r[i];j++)
			ans+=abs(a[j]-t);
	printf("%I64d\n",ans);

}