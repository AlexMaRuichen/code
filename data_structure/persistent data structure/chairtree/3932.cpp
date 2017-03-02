#include <stdio.h>
#include <algorithm>
const int maxn=100010;
const int N=10000000;
using namespace std;
int n,m;
typedef long long ll;
struct seg_tree
{
	seg_tree *ls,*rs;
	ll sum;
	int size;
}*root[maxn],mempool[maxn*100];
inline seg_tree* new_node(seg_tree *a,seg_tree *b,ll c,int d)
{
	static seg_tree *p=mempool;
	p->ls=a;
	p->rs=b;
	p->sum=c;
	p->size=d;
	return p++;
}
inline seg_tree* build(seg_tree *x,int p,ll sum,int size,int l,int r)
{
	if(l==r)
		return new_node(NULL,NULL,x->sum+sum,x->size+size);
	int mid=l+r>>1;
	if(mid>=p)
		return new_node(build(x->ls,p,sum,size,l,mid),x->rs,x->sum+sum,x->size+size);
	else
		return new_node(x->ls,build(x->rs,p,sum,size,mid+1,r),x->sum+sum,x->size+size);
}
inline ll query(seg_tree *x,int k,int l,int r)
{
	if(l==r)
		return l*1ll*min(k,x->size);
	int mid=l+r>>1;
	if(x->ls->size>=k)
		return query(x->ls,k,l,mid);
	else
		return x->ls->sum+query(x->rs,k-x->ls->size,mid+1,r);
}
int head[maxn];
int next[maxn<<1];
int val[maxn<<1];
bool flag[maxn<<1];
int tot;
inline void add(int x,int y,bool z)
{
	val[++tot]=y;
	flag[tot]=z;
	next[tot]=head[x];
	head[x]=tot;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,z,true);
		add(y+1,z,false);
	}
	root[0]=new_node(mempool,mempool,0,0);
	for(int x=1;x<=m;x++)
	{
		root[x]=root[x-1];
		for(int i=head[x];i;i=next[i])
			root[x]=build(root[x],val[i],flag[i]?val[i]:-val[i],flag[i]?1:-1,1,N);
	}
	for(int i=1;i<=m;i++)
	{
		static int x,a,b,c,k;
		static ll pre=1;
		scanf("%d%d%d%d",&x,&a,&b,&c);
		k=(a*pre+b)%c+1;
		printf("%lld\n",pre=query(root[x],k,1,N));
	}
}
