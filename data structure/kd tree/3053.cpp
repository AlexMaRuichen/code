#include <stdio.h>
#include <algorithm>
#define min(x, y) (x)<(y) ? (x) : (y)
#define max(x, y) (x)>(y) ? (x) : (y)
using namespace std;

const int maxn = 5e4 + 10;

const int inf = 1e9;
int k, s;

struct point
{
    int x[5];
}p[maxn];

bool cmp(const point &a, const point &b)
{
    return a.x[s]<b.x[s];
}

inline int dis(const point &a, const point &b)
{
    int ans = 0;
    for (int i = 0; i < k; i++)
        ans += (a.x[i] - b.x[i]) * (a.x[i] - b.x[i]);
    return ans;
}
struct kdt
{
    kdt *ls, *rs;
    point p;
    int mn[5], mx[5];
    kdt(){}
    kdt(const point &p):p(p)
    {
        ls = rs = NULL;
        for (int i = 0; i < k; i++)
            mn[i] = mx[i] = p.x[i];
    }
    void update()
    {
        if(ls)
            for(int i = 0; i < k; i++)
                mn[i] = min(mn[i], ls->mn[i]),
                mx[i] = max(mx[i], ls->mx[i]);
        if(rs)
            for(int i = 0; i < k; i++)
                mn[i] = min(mn[i], rs->mn[i]),
                mx[i] = max(mx[i], rs->mx[i]);
    }
    int mndis(const point &p)
    {
        int ans = 0;
        for(int i=0;i<k;i++)
        {
            if(p.x[i]<mn[i])
                ans+=(mn[i]-p.x[i])*(mn[i]-p.x[i]);
            if(p.x[i]>mx[i])
                ans+=(p.x[i]-mx[i])*(p.x[i]-mx[i]);
        }
        return ans;
    }
    void* operator new(size_t);
}*root,mem[maxn],*g=mem;
void* kdt :: operator new(size_t)
{
    return g++;
}
void build(kdt *&x,int l,int r,int flag)
{
    if(l>r)
        return;
    int mid=l+r>>1;
    s=flag;
    nth_element(p+l,p+mid,p+r+1,cmp);
    x=new kdt(p[mid]);
    build(x->ls,l,mid-1,(flag+1)%k);
    build(x->rs,mid+1,r,(flag+1)%k);
    x->update();
}
struct pa
{
    int dis;
    point p;
    pa(){}
    pa(int dis,const point &p):dis(dis),p(p){}
};
bool CMP(const pa &a,const pa &b)
{
    return a.dis<b.dis;
}
pa heap[15];
int m;
void query(kdt *x,const point &p)
{
    int dist=dis(p,x->p);
    if(dist<heap[1].dis)
    {
        pop_heap(heap+1,heap+m+1,CMP);
        heap[m]=pa(dist,x->p);
        push_heap(heap+1,heap+m+1,CMP);
    }
    int l=x->ls?x->ls->mndis(p):inf;
    int r=x->rs?x->rs->mndis(p):inf;
    if(l<r)
    {
        if(x->ls&&l<heap[1].dis)
            query(x->ls,p);
        if(x->rs&&r<heap[1].dis)
            query(x->rs,p);
    }
    else
    {
        if(x->rs&&r<heap[1].dis)
            query(x->rs,p);
        if(x->ls&&l<heap[1].dis)
            query(x->ls,p);  
    }
}
int main()
{
    int n;
    while(scanf("%d%d",&n,&k)==2)
    {
        g=mem;
        for(int i=1;i<=n;i++)
            for(int j=0;j<k;j++)
                scanf("%d",&p[i].x[j]);
        build(root,1,n,0);
        int q;
        scanf("%d",&q);
        while(q--)
        {
            point t;
            for(int i=0;i<k;i++)
                scanf("%d",&t.x[i]);
            scanf("%d",&m);
            for(int i=1;i<=m;i++)
                heap[i].dis=inf;
            query(root,t);
            printf("the closest %d points are:\n",m);
            sort_heap(heap+1,heap+m+1,CMP);
            for(int i=1;i<=m;i++)
                for(int j=0;j<k;j++)
                    printf("%d%c",heap[i].p.x[j],j+1==k?'\n':' ');
        }
    }
}