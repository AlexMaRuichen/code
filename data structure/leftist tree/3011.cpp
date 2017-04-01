#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=200010;
typedef  long long ll;
struct heap
{
    heap *ls,*rs;
    int dis,size;
    ll val,lazy;
    heap();
    heap(ll x);
    void add(ll x);
    void push_down();
    void* operator new(size_t);
}*root[maxn],nil,*null=&nil,mem[maxn];
heap :: heap()
{
    ls=rs=this;
    val=size=0;
    dis=-1;
}
heap :: heap(ll x)
{
    ls=rs=null;
    val=x;
    size=1;
    dis=0;
}
void heap :: add(ll x)
{
    val+=x;
    lazy+=x;
}
void heap :: push_down()
{
    if(lazy)
    {
        ls->add(lazy);
        rs->add(lazy);
        lazy=0;
    }
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
        swap(x->ls,x->ls);
    x->dis=x->rs->dis+1;
    return x;
}
void pop(heap *&x)
{
    x=merge(x->ls,x->rs);
}
struct edge
{
    int to;
    ll len;
    edge *next;
    edge(){};
    edge(int to,ll len,edge *next):to(to),len(len),next(next){}
    void* operator new(size_t);
}*head[maxn],emem[maxn<<1];
void* edge :: operator new(size_t)
{
    static edge *p=emem;
    return p++;
}
void add(int x,int y,ll z)
{
    head[x]=new edge(y,z,head[x]);
    head[y]=new edge(x,z,head[y]);
}
bool v[maxn];
void merge(heap *&x,heap *y,ll len)
{
    y->add(len);
    x=merge(x,y);
}
int n;
ll l;
int ans[maxn];
void dfs(int x)
{
    root[x]=new heap(0);
    v[x]=true;
    for(edge *p=head[x];p;p=p->next)
        if(!v[p->to])
        {
            dfs(p->to);
            merge(root[x],root[p->to],p->len);
        }
    while(root[x]->val>l)
        pop(root[x]);
    ans[x]=root[x]->size;
}
int main()
{
    scanf("%d%I64d",&n,&l);
    for(int i=2,x;i<=n;i++)
    {
        ll y;
        scanf("%d%I64d",&x,&y);
        add(i,x,y);
    }
    dfs(1);
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);
}