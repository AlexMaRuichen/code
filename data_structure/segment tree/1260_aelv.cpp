#include <cstdio>
#include <algorithm>
using namespace std;
int n,m;
struct tree
{
    int l,r;
    int lm,rm,m,sum;
}data[1048576],inf;
void build(int l,int r,int now)
{
    data[now].l=l;
    data[now].r=r;
    if(l==r-1)
    {
        scanf("%d",&data[now].sum);
        data[now].lm=data[now].rm=data[now].m=data[now].sum;
        return ;
    }
    int ls=(now<<1),rs=(now<<1|1);
    int mid=l+((r-l)>>1);
    build(l,mid,ls);
    build(mid,r,rs);
    data[now].sum=data[ls].sum+data[rs].sum;
    data[now].lm=max(data[ls].lm,data[ls].sum+data[rs].lm);
    data[now].rm=max(data[rs].rm,data[ls].rm+data[rs].sum);
    data[now].m=max(max(data[ls].m,data[rs].m),
                    max(max(data[ls].rm,data[rs].lm),
                        data[ls].rm+data[rs].lm));
    return ;
}
void change(int l,int c,int now)
{
    if(data[now].r<=l||l+1<=data[now].l)
        return ;
    if(l==data[now].l&&data[now].r==l+1)
    {
        data[now].lm=data[now].rm=data[now].m=data[now].sum=c;
        return ;
    }
    int ls=(now<<1),rs=(now<<1|1);
    change(l,c,ls);
    change(l,c,rs);
    data[now].sum=data[ls].sum+data[rs].sum;
    data[now].lm=max(data[ls].lm,data[ls].sum+data[rs].lm);
    data[now].rm=max(data[rs].rm,data[ls].rm+data[rs].sum);
    data[now].m=max(max(data[ls].m,data[rs].m),
                    max(max(data[ls].rm,data[rs].lm),
                        data[ls].rm+data[rs].lm));
    return ;
}
tree ask(int l,int r,int now)
{
    if(data[now].r<=l||r<=data[now].l)
        return inf;
    if(l<=data[now].l&&data[now].r<=r)
        return data[now];
    tree ls=ask(l,r,(now<<1)),rs=ask(l,r,(now<<1|1));
    /************************************
    			絲柏錯誤開始
    data[now].lm=max(ls.lm,ls.sum+rs.lm);
    data[now].rm=max(rs.rm,rs.sum+ls.rm);
    data[now].m=max(max(ls.m,rs.m),
                    max(max(ls.rm,rs.lm),
                        ls.rm+rs.lm));
    			絲柏錯誤結束
    ************************************/
    tree ans;
    ans.sum=ls.sum+rs.sum;
    ans.lm=max(ls.lm,ls.sum+rs.lm);
	ans.rm=max(rs.rm,rs.sum+ls.rm);
    ans.m=max(max(ls.m,rs.m),max(max(ls.rm,rs.lm),ls.rm+rs.lm)); 
    return ans;
}
int main()
{
    inf.lm=inf.rm=inf.m=-500000010;inf.sum=0;
    scanf("%d%d",&n,&m);
    build(1,n+1,1);
    for(int i=1;i<=m;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        if(a==1)
        {
            if(b>c)
                swap(b,c);
            printf("%d\n",ask(b,c+1,1).m);
        }
        else
            change(b,c,1);
    }
    return 0;
}
