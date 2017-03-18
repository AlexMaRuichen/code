#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
const int maxm=2e6+10;
int n,m;
struct node{int b,c,l;}e[maxn];
struct edge
{
	int to;
	edge *next;
	edge(){}
	edge(int to,edge *next):to(to),next(next){}
	void* operator new(size_t);
}*head[maxn],Tdata[maxn];
void* edge :: operator new(size_t)
{
	static edge *p=Tdata;
	return p++;
}
void add(int x,int y){head[x]=new edge(y,head[x]);}
struct leftist_tree
{
	leftist_tree *ls,*rs;
	int dis,val;
	leftist_tree(){}
	leftist_tree(int x):val(x){}
	void* operator new(size_t);
}*root[maxn],mempool[maxm];
void* leftist_tree :: operator new(size_t)
{
	static leftist_tree *cur=mempool;
	return cur++;
}
leftist_tree* merge(leftist_tree *x,leftist_tree *y)
{
	if(!x)	return y;
	if(!y)	return x;
	if(x->val<y->val)
		swap(x,y);
	x->rs=merge(x->rs,y);
	if(!x->ls||x->rs->dis>x->ls->dis)
		swap(x->ls,x->rs);
	x->dis=x->rs?x->rs->dis+1:0;
	return x;
}
leftist_tree* del(leftist_tree *x){return merge(x->ls,x->rs);}
int r;
int size[maxn],cost[maxn];
ll ans;
void dfs(int x)
{
	size[x]=1,cost[x]=e[x].c;
	root[x]=new leftist_tree(e[x].c);
	for(edge *p=head[x];p;p=p->next)
	{
		dfs(p->to);
		root[x]=merge(root[x],root[p->to]);
		size[x]+=size[p->to],cost[x]+=cost[p->to];
		while(cost[x]>m)
		{
			size[x]--;
			cost[x]-=root[x]->val;
			root[x]=del(root[x]);
		}
	}
	
	ans=max(ans,(ll)e[x].l*size[x]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d%d",&e[i].b,&e[i].c,&e[i].l);
		if(!e[i].b)
			r=i;
		else
			add(e[i].b,i);
	}
	dfs(r);
	printf("%lld\n",ans);
}
