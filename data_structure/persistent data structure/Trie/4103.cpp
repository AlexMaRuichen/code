#include <stdio.h>
#include <algorithm>
#define ls ch[0]
#define rs ch[1]
#define to bool(z[i]&digit)
using namespace std;
void read(int &x)
{
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
}
const int maxn=300010;
struct Trie
{
	Trie *ch[2];
	int cnt;
}*root[maxn],mempool[maxn*40];
inline Trie* new_node(Trie *x,Trie *y,int z)
{
	static Trie *p=mempool;
	p->ls=x;
	p->rs=y;
	p->cnt=z;
	return p++;
}
inline Trie* build(Trie *x,int y,int digit)
{
	if(!digit)
		return new_node(NULL,NULL,x->cnt+1);
	else if(~y&digit)
		return new_node(build(x->ls,y,digit>>1),x->rs,x->cnt+1);
	else
		return new_node(x->ls,build(x->rs,y,digit>>1),x->cnt+1);
}
Trie *x[1010],*y[1010];
int z[1010];
int n,m;
int a[maxn];
int b[maxn];
int tot;
inline int query(int k,int digit)
{
	if(!digit)
		return 0;
	int t=0,i;
	for(i=1;i<=tot;i++)
		t+=y[i]->ch[!to]->cnt-x[i]->ch[!to]->cnt;
	if(k<=t)
	{
		for(i=1;i<=tot;i++)
			x[i]=x[i]->ch[!to],y[i]=y[i]->ch[!to];
		return digit+query(k,digit>>1);
	}
	else
	{
		for(i=1;i<=tot;i++)
			x[i]=x[i]->ch[to],y[i]=y[i]->ch[to];
		return query(k-t,digit>>1);
	}
}
int main()
{
	read(n),read(m);
	root[0]=new_node(mempool,mempool,0);
	for(int i=1;i<=n;i++)
		read(a[i]);
	for(int i=1;i<=m;i++)
		read(b[i]),root[i]=build(root[i-1],b[i],1<<30);
	int q;
	read(q);
	while(q--)
	{
		static int l1,l2,r1,r2,k;
		read(l1);
		read(l2);
		read(r1);
		read(r2);
		read(k);
		tot=0;
		for(int i=l1;i<=l2;i++)
		{
			x[++tot]=root[r1-1];
			y[tot]=root[r2];
			z[tot]=a[i];
		}
		printf("%d\n",query(k,1<<30));
	}
}
