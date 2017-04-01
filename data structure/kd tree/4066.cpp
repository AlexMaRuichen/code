#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=200010;
struct point
{
    int x,y,val;
}p[maxn];
int tot;
bool oflag;
bool cmpx(const point &a,const point &b)
{
    return a.x<b.x;
}
bool cmpy(const point &a,const point &b)
{
    return a.y<b.y;
}
struct kdt
{
    kdt *ls,*rs;
    point p;
    int xmn,xmx,ymn,ymx,size,sum;
    kdt(){}
    kdt(const point &p):p(p)
    {
        ls=rs=NULL;
        xmn=xmx=p.x;
        ymn=ymx=p.y;
        sum=p.val;
        size=1;
    }
    void update()
    {
        sum=p.val;
        size=1;
        if(ls)
        {
            xmn=min(xmn,ls->xmn);
            xmx=max(xmx,ls->xmx);
            ymn=min(ymn,ls->ymn);
            ymx=max(ymx,ls->ymx);
            sum+=ls->sum;
            size+=ls->size;
        }
        if(rs)
        {
            xmn=min(xmn,rs->xmn);
            xmx=max(xmx,rs->xmx);
            ymn=min(ymn,rs->ymn);
            ymx=max(ymx,rs->ymx);
            sum+=rs->sum;
            size+=rs->size;
        }
    }
    void* operator new(size_t);
}*root,**mark,**fa;
queue <kdt*> q;
void* kdt :: operator new(size_t)
{
    static kdt *l,*r,*g;
    if(!q.empty())
    {
        g=q.front();
        q.pop();
        return g;
    }
    else if(l==r)
        r=(l=new kdt[1<<15])+(1<<15);
    return l++;
}
void insert(kdt *&x,const point &p,bool flag)
{
    if(!x)
    {
        x=new kdt(p);
        return;
    }
    else if(p.x==x->p.x&&p.y==x->p.y)
        x->p.val+=p.val;
    else if((flag?cmpy:cmpx)(p,x->p))
        insert(x->ls,p,flag^1);
    else
        insert(x->rs,p,flag^1);
    x->update();
    if(max(x->ls?x->ls->size:0,x->rs?x->rs->size:0)>x->size*4/5)
        mark=&x,oflag=flag;
}
int query(kdt *x,int xmn,int ymn,int xmx,int ymx)
{
    if(!x||x->xmx<xmn||x->ymx<ymn||x->xmn>xmx||x->ymn>ymx)
        return 0;
    else if(x->xmn>=xmn&&x->ymn>=ymn&&x->xmx<=xmx&&x->ymx<=ymx)
        return x->sum;
    else
        return  query(x->ls,xmn,ymn,xmx,ymx)+
                query(x->rs,xmn,ymn,xmx,ymx)+
                ((x->p.x>=xmn&&x->p.x<=xmx&&x->p.y>=ymn&&x->p.y<=ymx)?x->p.val:0);
}
void travel(kdt *x)
{
    if(!x)
        return;
    travel(x->ls);
    travel(x->rs);
    p[++tot]=x->p;
    q.push(x);
}
void build(kdt *&x,int l,int r,bool flag)
{
    if(l>r)
        return;
    int mid=l+r>>1;
    nth_element(p+l,p+mid,p+r+1,flag?cmpy:cmpx);
    x=new kdt(p[mid]);
    build(x->ls,l,mid-1,flag^1);
    build(x->rs,mid+1,r,flag^1);
    x->update();
}
int main()
{
    scanf("%*d");
    int opt;
    while(scanf("%d",&opt)&&opt^3)
    {
        static int lastans,xmn,xmx,ymn,ymx;
        static point p;
        if(opt==1)
        {
            mark=NULL;
            scanf("%d%d%d",&p.x,&p.y,&p.val);
            p.x^=lastans;
            p.y^=lastans;
            p.val^=lastans;
            insert(root,p,false);
            if(mark)
            {
                tot=0;
                travel(*mark);
                build(*mark,1,tot,oflag);
            }
        }
        else if(opt==2)
        {
            scanf("%d%d%d%d",&xmn,&ymn,&xmx,&ymx);
            xmn^=lastans;
            xmx^=lastans;
            ymn^=lastans;
            ymx^=lastans;
            printf("%d\n",lastans=query(root,xmn,ymn,xmx,ymx));
        }
    }   
}
