#include <stdio.h>
#include <set>
#include <algorithm>
#define ls ch[0]
#define rs ch[1]
#define to bool(z&digit)
using namespace std;
int n;
const int maxn=50010;
struct Trie
{
	Trie *ch[2];
	int cnt;
}mempool[maxn*32],*root[maxn];
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
inline int query(Trie *x,Trie *y,int z,int digit)
{
	if(!digit)
		return 0;
	else if(y->ch[!to]->cnt-x->ch[!to]->cnt)
		return digit+query(x->ch[!to],y->ch[!to],z,digit>>1);
	else
		return query(x->ch[to],y->ch[to],z,digit>>1);
}
set <int> s;
set <int> :: iterator it;
inline int pre_pre(int x)
{
	it=s.lower_bound(x);
	if(it--==s.begin())
		return 0;
	if(it--==s.begin())
		return 0;
	return *it;	
}
pair <int,int> p[maxn];
inline int suc_suc(int x)
{
	it=s.lower_bound(x);
	if(++it==s.end())
		return n+1;
	if(++it==s.end())
		return n+1;
	return *it;
}
int l[maxn];
int r[maxn];
int a[maxn];
int ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i].first),p[i].second=i,a[i]=p[i].first;
	sort(p+1,p+n+1);
	for(int i=n;i;i--)
	{
		s.insert(p[i].second);
		l[p[i].second]=pre_pre(p[i].second);
		r[p[i].second]=suc_suc(p[i].second);
	}
	root[0]=new_node(mempool,mempool,0);
	for(int i=1;i<=n;i++)
		root[i]=build(root[i-1],a[i],1<<30);
	for(int i=1;i<=n;i++)
		ans=max(ans,query(root[l[i]],root[r[i]-1],a[i],1<<30));
	printf("%d\n",ans);
		
}
