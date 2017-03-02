#include <stdio.h>
#include <algorithm>
#define ls ch[0]
#define rs ch[1]
using namespace std;
const int maxn=300000*2+10;
struct Trie
{
	Trie *ch[2];
	int cnt;
}mempool[maxn*25],*mem[maxn],**root=mem+1;
Trie* new_node(Trie *x,Trie *y,int z)
{
	static Trie *p=mempool;
	p->ls=x;
	p->rs=y;
	p->cnt=z;
	return p++;
}
Trie* build(Trie *x,int y,int digit)
{
	if(!digit)
		return new_node(NULL,NULL,x->cnt+1);
	else if(~y&digit)
		return new_node(build(x->ls,y,digit>>1),x->rs,x->cnt+1);
	else
		return new_node(x->ls,build(x->rs,y,digit>>1),x->cnt+1);
}
int query(Trie *x,Trie *y,int z,int digit)
{
	if(!digit)
		return 0;
	else if(y->ch[!bool(z&digit)]->cnt-x->ch[!bool(z&digit)]->cnt)
		return digit+query(x->ch[!bool(z&digit)],y->ch[!bool(z&digit)],z,digit>>1);
	else
		return query(x->ch[bool(z&digit)],y->ch[bool(z&digit)],z,digit>>1);
}
int a[maxn];
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	root[-1]=new_node(mempool,mempool,0);
	root[0]=build(root[-1],0,1<<24);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),root[i]=build(root[i-1],a[i]^=a[i-1],1<<24);
	while(m--)
	{
		static char s[10];
		static int l,r,x;
		scanf("%s",s);
		if(s[0]=='A')
		{
			scanf("%d",&x);
			a[++n]=x;
			root[n]=build(root[n-1],a[n]^=a[n-1],1<<24);
		}
		else if(s[0]=='Q')
		{
			scanf("%d%d%d",&l,&r,&x);
			x^=a[n];
			--l,--r;
			printf("%d\n",query(root[l-1],root[r],x,1<<24));
		}
	}
}
