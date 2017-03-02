#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int N=70000;
const int maxn=70010;
char getc()
{
    static const int len=1<<20;
    static char buf[len],*s=buf,*t=buf;
    if(s==t)
    {
        t=(s=buf)+fread(buf,1,len,stdin);
        if(s==t)
            return EOF;
    }
    return *(s++);
}

void read(register int &x)
{
	static char ch;
    x=0;
    while(ch<'0'||ch>'9')
        ch=getc();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+ch-'0',ch=getc();
} 
void read(register char *s)
{
	static char ch;
    while(ch<'A'||ch>'Z')
        ch=getc();
    while(ch>='A'&&ch<='Z')
        *s++=ch,ch=getc();
    *s=0;
}
struct seg_tree
{
    seg_tree *ls,*rs;
    int cnt;
    seg_tree(){ls=rs=NULL,cnt=0;}
    void* operator new(size_t);
};
queue <seg_tree*> q0;
void* seg_tree :: operator new(size_t)
{
    #define len (1<<10)
    static seg_tree *l,*r,*p;
    if(!q0.empty())
    {
        p=q0.front();
        q0.pop();
        return p;
    }
    else if(l==r)
        r=(l=new seg_tree[len])+len;
    return l++;
}
void insert(seg_tree *&x,int p,int l,int r)
{
    if(!x)
        x=new seg_tree();
    ++x->cnt;
    if(l==r)
        return;
    int mid=l+r>>1;
    if(mid>=p)
        insert(x->ls,p,l,mid);
    else
        insert(x->rs,p,mid+1,r);
}
void del(seg_tree *x,int p,int l,int r)
{
    --x->cnt;
    if(l==r)
        return;
    int mid=l+r>>1;
    if(mid>=p)
        del(x->ls,p,l,mid);
    else
        del(x->rs,p,mid+1,r);
}
int query(seg_tree *x,int p,int l,int r)
{
    if(!x)
        return 0;
    if(!x->cnt)
        return 0;
    if(l==r)
        return x->cnt;
    int mid=l+r>>1;
    if(mid>=p)
        return query(x->ls,p,l,mid);
    else
        return (x->ls?x->ls->cnt:0)+query(x->rs,p,mid+1,r);
}
struct scapegoat
{
    scapegoat *ls,*rs;
    seg_tree *t;
    int val,size;
    scapegoat();
    scapegoat(int x);
    void update()
    {
        size=ls->size+rs->size+1;
    }
    void* operator new(size_t);
}*null=new scapegoat(),*root=null,**mark=NULL;
queue <scapegoat*> q1;
void* scapegoat :: operator new(size_t)
{
    #define len (1<<10)
    static scapegoat *l,*r,*p;
    if(!q1.empty())
    {   
        p=q1.front();
        q1.pop();
        return p;
    }
    else if(l==r)
        r=(l=new scapegoat[len])+len;
    return l++;
}
scapegoat :: scapegoat()
{
    ls=rs=this;
    val=size=0;
    t=NULL;
}
scapegoat :: scapegoat(int x)
{
    ls=rs=null;
    t=NULL;
    val=x;
    size=1;
}
int a[maxn];
void get(scapegoat *x)
{
    if(x==null)
        return;
    get(x->ls);
    a[++a[0]]=x->val;
    get(x->rs);
}
scapegoat* build(int l,int r)
{
    if(l>r)
        return null;
    int mid=l+r>>1;
    scapegoat* x=new scapegoat(a[mid]);
    for(int i=l;i<=r;i++)
        insert(x->t,a[i],0,N);
    x->ls=build(l,mid-1);
    x->rs=build(mid+1,r);
    x->update();
    return x;
}
void free(seg_tree *x)
{
    if(!x)
        return;
    free(x->ls);
    free(x->rs);
    q0.push(x);
}
void free(scapegoat *x)
{
    if(x==null)
        return;
    free(x->ls);
    free(x->rs);
    free(x->t);
    q1.push(x);
}
void rebuild(scapegoat *&x)
{
    a[0]=0;
    get(x);
    free(x);
    x=build(1,a[0]);
}
void INSERT(scapegoat *&x,int y,int z)
{
    if(x==null)
    {
        x=new scapegoat(z);
        insert(x->t,z,0,N);
        return;
    }
    insert(x->t,z,0,N);
    if(y<=x->ls->size)
        INSERT(x->ls,y,z);
    else
        INSERT(x->rs,y-x->ls->size-1,z);
    x->update();
    if(max(x->ls->size,x->rs->size)>x->size*4/5)
        mark=&x;
}
int scape_query(scapegoat *x,int p,int v)
{
    if(!p)
        return 0;
    if(p<=x->ls->size)
        return scape_query(x->ls,p,v);
    else
        return query(x->ls->t,v,0,N)+(x->val<=v)+scape_query(x->rs,p-x->ls->size-1,v);
}
int QUERY(int x,int y,int k)
{
    int l=0,r=N,mid;
    while(l<r)
    {
        mid=l+r>>1;
        if(scape_query(root,y,mid)-scape_query(root,x-1,mid)>=k)
            r=mid;
        else
            l=mid+1;
    }
    return l;
}
int o;
void modify(scapegoat *x,int p,int v)
{
    insert(x->t,v,0,N);
    if(p<=x->ls->size)
        modify(x->ls,p,v);
    else if(p==x->ls->size+1)
        o=x->val,x->val=v;
    else
        modify(x->rs,p-x->ls->size-1,v);
    del(x->t,o,0,N);
}
int n,g;
int main()
{
    read(n);
    for(int i=1;i<=n;i++)
        read(a[i]);
    root=build(1,n);
    read(g);
    while(g--)
    {
        static int lastans,x,y,z;
        static char s[10];
        read(s);
        if(s[0]=='I')
        {
            mark=NULL;
            read(x);
            read(y);
            x^=lastans;
            y^=lastans;
            INSERT(root,x-1,y);
			if(mark)
				rebuild(*mark);
        }
        else if(s[0]=='M')
        {
            read(x);
            read(y);
            x^=lastans;
            y^=lastans;
            modify(root,x,y);
        }
        else
        {
            read(x);
            read(y);
            read(z);
            x^=lastans;
            y^=lastans;
            z^=lastans;
            printf("%d\n",lastans=QUERY(x,y,z));
        }
    }
}
