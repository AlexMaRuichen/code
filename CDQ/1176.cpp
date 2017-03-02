#include <stdio.h>
#include <algorithm>
#define lowbit(x) (x)&(-x)
using namespace std;
const int maxn=2000010;
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
void read(register int &x)
{
    static char ch=getc();
    x=0;
    while(ch<'0'||ch>'9')
        ch=getc();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+ch-'0',ch=getc();
}
struct data
{
	int x,y,pos,ans,flag,val;
}d[maxn];
bool cmpp(const data &a,const data &b)
{
	return a.pos^b.pos?a.pos<b.pos:a.x^b.x?a.x<b.x:a.y<b.y;
}
bool cmpx(const data &a,const data &b)
{
	return a.x^b.x?a.x<b.x:a.y<b.y;
}
int bit[maxn];
int w;
void insert(int x,int y)
{
	for(int i=x;i<=w;i+=lowbit(i))
		bit[i]+=y;
}
int query(int x)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans+=bit[i];
	return ans;
}
void del(int x)
{
	for(int i=x;i<=w;i+=lowbit(i))
		bit[i]=0;
}
void CDQ(int l,int r)
{
	if(l==r)
		return;
	int mid=l+r>>1;
	CDQ(l,mid);
	CDQ(mid+1,r);
	sort(d+l,d+mid+1,cmpx);
	sort(d+mid+1,d+r+1,cmpx);
	int i=l,j=mid+1;
	while(j<=r)
	{
		while((d[i].x<d[j].x||(d[i].x==d[j].x&&d[i].y<=d[j].y))&&i<=mid)
			insert(d[i].y,d[i].val),++i;
		if(d[j].flag^1)
			d[j].ans+=query(d[j].y);
		++j;
	}
	for(i=l;i<=mid;i++)
		del(d[i].y);
}
int f[maxn];
bool v[maxn];
int main()
{
	read(w);
	read(w);
	++w;
	int cnt=0,tot=0,opt,h,i,j,k;
	while(true)
	{
		read(opt);
		if(opt==3)
			break;
		++cnt;
		if(opt==2)
		{
			read(h);
			read(i);
			read(j);
			read(k);
			++h,++i,++j,++k;
			v[cnt]=true;
			d[++tot].x=j,d[tot].y=k,d[tot].pos=cnt,d[tot].flag=3;
			d[++tot].x=h-1,d[tot].y=i-1,d[tot].pos=cnt,d[tot].flag=3;
			d[++tot].x=j,d[tot].y=i-1,d[tot].pos=cnt,d[tot].flag=2;
			d[++tot].x=h-1,d[tot].y=k,d[tot].pos=cnt,d[tot].flag=2;
		}
		else if(opt==1)
		{
			read(h);
			read(i);
			read(j);
			++h,++i;
			d[++tot].x=h,d[tot].y=i,d[tot].pos=cnt,d[tot].flag=1,d[tot].val=j;
		}
	}
	sort(d+1,d+tot+1,cmpp);
	CDQ(1,tot);
	for(int i=1;i<=tot;i++)
		if(d[i].flag^2)
			f[d[i].pos]+=d[i].ans;
		else
			f[d[i].pos]-=d[i].ans;
	for(int i=1;i<=cnt;i++)
		if(v[i])
			printf("%d\n",f[i]);
}
