#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=12010;
int n,m;
struct Trie
{
	Trie *ch[2];
	int cnt;
}*trie[maxn],**root=trie+1,mempool[maxn*40],*p=mempool;
inline Trie* new_node(Trie *x,Trie *y,int z)
{
	p->ch[0]=x;
	p->ch[1]=y;
	p->cnt=z;
	return p++;
}
Trie* build(Trie *x,int y,int pos)
{
	if(!pos)
		return new_node(NULL,NULL,x->cnt+1);
	if(~y&pos)
		return new_node(build(x->ch[0],y,pos>>1),x->ch[1],x->cnt+1);
	else
		return new_node(x->ch[0],build(x->ch[1],y,pos>>1),x->cnt+1);
}
int query(Trie *l,Trie *r,int x,int pos)
{
	if(!pos)
		return 0;
	int to=((x&pos)?1:0);
	if(r->ch[!to]->cnt-l->ch[!to]->cnt)
		return pos+query(l->ch[!to],r->ch[!to],x,pos>>1);
	else
		return query(l->ch[to],r->ch[to],x,pos>>1);
}
int a[maxn];
int s[120][maxn];
int sqrt(int x)
{
	int l=1,r=x+1,mid;
	while(r-l>1)
	{
		mid=l+r>>1;
		if(mid*mid<x)
			l=mid;
		else
			r=mid;
	}	
	return l;
}
int main()
{
	scanf("%d%d",&n,&m);
	root[-1]=new_node(p,p,0);
	root[0]=build(root[-1],0,1<<30);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),root[i]=build(root[i-1],a[i]^=a[i-1],1<<30);
	int block=sqrt(n+1);
	 for(int i=0;i*block<=n;i++)  
        for(int j=i*block;j<=n;j++)  
            s[i][j]=max(query(root[i*block-1],root[j],a[j],1<<30),j?s[i][j-1]:0);  
	while(m--)
	{
		static int l,r,x,y,lastans,b;
		scanf("%d%d",&l,&r);
		l=((long long)l+lastans)%n+1;
		r=((long long)r+lastans)%n+1;
		if(l>r)
			swap(l,r);
		--l;
		b=l/block+1;
		lastans=s[b][r];
		for(int i=min(b*block-1,r);i>=l;i--)
			lastans=max(lastans,query(root[l-1],root[r],a[i],1<<30));
		printf("%d\n",lastans);
	}
}
