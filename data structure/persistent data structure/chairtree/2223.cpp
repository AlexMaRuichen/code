#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=500010;
int lim;
struct seg_tree
{
    seg_tree *ls,*rs;
    int cnt;
    seg_tree()
    {
        ls=rs=NULL;
        cnt=0;
    }
    void* operator new(size_t);
}*root[maxn],Tdata[maxn*25];
void* seg_tree :: operator new(size_t)
{
    static seg_tree *p=Tdata;
    return p++;
}
void build(seg_tree* &x,int l,int r)
{
    x=new seg_tree();
    if(l==r)    
        return;
    int mid=(l+r)>>1;
    build(x->ls,l,mid);
    build(x->rs,mid+1,r);
}
void insert(seg_tree* &x,seg_tree* bak,int v,int l,int r)
{
    x=new seg_tree();
    x->cnt=bak->cnt+1;
    if(l==r)
        return;
    x->ls=bak->ls;
    x->rs=bak->rs;
    int mid=(l+r)>>1;
    if(mid>=v)
        insert(x->ls,bak->ls,v,l,mid);
    else
        insert(x->rs,bak->rs,v,mid+1,r);
}
int query(seg_tree *x,seg_tree *y,int k,int l,int r)
{
    if(l==r)
        return l;
    if(y->cnt-x->cnt<=k)
        return 0;
    int mid=(l+r)>>1;
    if(y->ls->cnt-x->ls->cnt>k)
        return query(x->ls,y->ls,k,l,mid);
    else if(y->rs->cnt-x->rs->cnt>k)
        return query(x->rs,y->rs,k,mid+1,r);
    else
        return 0;
}
int a[maxn];
int main()
{
    int n,m;
    scanf("%d%d",&n,&lim);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    scanf("%d",&m);
    build(root[0],1,lim);
    for(int i=1;i<=n;i++)
        insert(root[i],root[i-1],a[i],1,lim);
    for(int i=1;i<=m;i++)
    {
        static int x,y;
        scanf("%d%d",&x,&y);
        int ans=query(root[x-1],root[y],(y-x+1)>>1,1,lim);
        if(ans)
        	printf("yes %d\n",ans);
		else
			puts("no");
    }
}
