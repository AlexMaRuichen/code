#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
const int maxn=50010;
char getc()
{
    static const int len=1<<15;
    static char buf[len],*s=buf,*t=buf;
    if(s==t)
    {
        t=(s=buf)+fread(buf,1,len,stdin);
        if(s==t)
            return EOF;
    }
    return *(s++);
}
void read(int &x)
{
    static char ch=getc();
    x=0;
    while(ch<'0'||ch>'9')
        ch=getc();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+ch-'0',ch=getc();
}
struct chairtree
{
	chairtree *ls,*rs;
	int cnt;
	void* operator new(size_t)
	{
		static chairtree *l,*r;
		if(l==r)
			r=(l=new chairtree[1<<15])+(1<<15);
		return l++;
	}
}*root[maxn];
void insert(chairtree *&x,chairtree *y,int p,int l,int r)
{
	x=new chairtree();
	*x=*y;
	++x->cnt;
	if(l==r)
		return;
	int mid=l+r>>1;
	if(mid>=p)
		insert(x->ls,y->ls,p,l,mid);
	else
		insert(x->rs,y->rs,p,mid+1,r);
}
int greater(chairtree *x,chairtree *y,int p,int l,int r)
{
	if(!x->cnt&&!y->cnt)
		return 0;
	if(l==r)
		return 0;
	int mid=l+r>>1;
	if(mid>=p)
		return y->rs->cnt-x->rs->cnt+greater(x->ls,y->ls,p,l,mid);
	else
		return greater(x->rs,y->rs,p,mid+1,r);
}
int less(chairtree *x,chairtree *y,int p,int l,int r)
{
	if(!x->cnt&&!y->cnt)
		return 0;
	if(l==r)
		return 0;
	int mid=l+r>>1;
	if(mid>=p)
		return less(x->ls,y->ls,p,l,mid);
	else
		return  y->ls->cnt-x->ls->cnt+less(x->rs,y->rs,p,mid+1,r);
}
int n,k;
int a[maxn];
int block[240][maxn];
pair <int,int> b[maxn];
int main()
{
	read(n);
	for(int i=1;i<=n;i++)
		read(b[i].first),b[i].second=i;
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		static int tot;
		if(b[i].first^b[i-1].first)
			++tot;
		a[b[i].second]=tot;
	}
	root[0]=new chairtree();
	root[0]->ls=root[0]->rs=root[0];
	for(int i=1;i<=n;i++)
		insert(root[i],root[i-1],a[i],1,n);
	int size=int(sqrt(n));
	for(int i=size+1,tot=2;i<=n;i+=size,++tot)
		for(int j=i+1;j<=n;j++)
			block[tot][j]=block[tot][j-1]+greater(root[i-1],root[j-1],a[j],1,n);
	read(k);
	for(int i=1;i<=k;i++)
	{
		static int x,y,bx,by,lastans;
		read(x),read(y);
		x^=lastans;
		y^=lastans;
		bx=(x-1)/size+2;
		by=(y-1)/size+2;
		if(bx^by)
		{
			lastans=block[bx][y];
			for(int j=(bx-1)*size;j>=x;j--)
				lastans+=less(root[j],root[y],a[j],1,n);
		}
		else
		{
			lastans=0;
			for(int i=x+1;i<=y;i++)
				lastans+=greater(root[x-1],root[i],a[i],1,n);
		}
		printf("%d\n",lastans);	
	}
}
