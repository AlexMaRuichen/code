#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=4e5+10;
struct Trie
{
	Trie *ch[2];
	int cnt;
}mempool[maxn*32],*mem[maxn],**root=mem+1;
inline Trie* new_node(Trie *x,Trie *y,int z)
{
	static Trie *p=mempool;
	p->ch[0]=x;
	p->ch[1]=y;
	p->cnt=z;
	return p++;
}
inline Trie* build(Trie *x,int y,int digit)
{
	#define ls ch[0]
	#define rs ch[1]
	if(!digit)
		return new_node(NULL,NULL,x->cnt+1);
	else if(!bool(y&digit))
		return new_node(build(x->ls,y,digit>>1),x->rs,x->cnt+1);
	else
		return new_node(x->ls,build(x->rs,y,digit>>1),x->cnt+1);
}
inline int query(Trie *x,Trie *y,int z,int digit)
{
	if(!digit)
		return 0;
	if(y->ch[!bool(z&digit)]->cnt-x->ch[!bool(z&digit)]->cnt)
		return digit+query(x->ch[!bool(z&digit)],y->ch[!bool(z&digit)],z,digit>>1);
	else
		return query(x->ch[bool(z&digit)],y->ch[bool(z&digit)],z,digit>>1);
}
int n,mx,ans;
int a[maxn];
int main()
{
	scanf("%d",&n);
	root[-1]=new_node(mempool,mempool,0);
	root[0]=build(root[-1],0,1<<30);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),root[i]=build(root[i-1],a[i]^=a[i-1],1<<30);
	for(int i=n-1;i;i--)
	{
		mx=max(mx,query(root[i],root[n],a[i],1<<30));
		ans=max(ans,mx+query(root[-1],root[i],a[i],1<<30));
	}
	printf("%d\n",ans);
}
