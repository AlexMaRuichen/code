#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=2e5+10;
int n,m,opt;
struct seg_tree
{
    seg_tree *ls,*rs;
    int val;
}*fa[maxn],*size[maxn],mempool[maxn*40],*p=mempool;
int v[maxn],cur,tot;
inline seg_tree* new_node(seg_tree *x,seg_tree *y,int z)
{
    p->ls=x;
    p->rs=y;
    p->val=z;
    return p++;
}
inline seg_tree* modify(seg_tree *x,int p,int v,int l,int r)
{
    if(l==r)
        return new_node(NULL,NULL,v);
    int mid=l+r>>1;
    if(mid>=p)
        return new_node(modify(x->ls,p,v,l,mid),x->rs,0);
    else
        return new_node(x->ls,modify(x->rs,p,v,mid+1,r),0);
}
inline int access(seg_tree *x,int p,int l,int r)
{
    if(l==r)
        return x->val;
    int mid=l+r>>1;
    if(mid>=p)
        return access(x->ls,p,l,mid);
    else
        return access(x->rs,p,mid+1,r);
}
inline int getfa(int x)
{
    int y;
    while(x)
        x=access(fa[cur],y=x,1,n);
    return y;
}
inline void merge(int x,int y)
{
    x=getfa(x);
    y=getfa(y);
    if(x==y)
        return;
    ++tot;
    int sx=access(size[cur],x,1,n);
    int sy=access(size[cur],y,1,n);
    if(sx<sy)
        swap(x,y),swap(sx,sy);
    fa[tot]=modify(fa[cur],y,x,1,n);
    size[tot]=modify(size[cur],x,sx+sy,1,n);
    cur=tot;
}
inline bool query(int x,int y)
{
    return getfa(x)==getfa(y);
}
int main()
{
    scanf("%d%d",&n,&m);
    fa[0]=new_node(p,p,0);
    size[0]=new_node(p,p,1);
    for(int i=1;i<=m;i++)
    {
        static int a,b,lastans;
        scanf("%d",&opt);
        if(opt==1)
        {
            scanf("%d%d",&a,&b);
            a^=lastans;
            b^=lastans;
            merge(a,b);
        }
        else if(opt==2)
        {
            scanf("%d",&a);
            a^=lastans;
            cur=v[a];
        }
        else if(opt==3)
        {
            scanf("%d%d",&a,&b);
            a^=lastans;
            b^=lastans;
            printf("%d\n",lastans=query(a,b));
        }
        v[i]=cur;
    }
}

