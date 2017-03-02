#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=200000;
const int inf=1e9;
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
    return *s++;
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
struct edge
{
	int to,len;
	edge *next,*rev;
	edge(){}
	edge(int to,int len,edge *next):to(to),len(len),next(next){}
	void* operator new(size_t)
	{
		static edge mem[1001001],*p=mem;
		return p++;
	}
}*head[maxn];
void add(int x,int y,int z)
{
	head[x]=new edge(y,z,head[x]);
	head[y]=new edge(x,0,head[y]);
	head[x]->rev=head[y];
	head[y]->rev=head[x];
}
int dep[maxn];
int S,T;
int cnt;
queue <int> q;
bool bfs()
{
	for(int i=1;i<=cnt;i++)
		dep[i]=-1;
	dep[S]=1;
	q.push(S);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(edge *p=head[x];p;p=p->next)
			if(p->len&&dep[p->to]<0)
				dep[p->to]=dep[x]+1,q.push(p->to);
	}
	return dep[T]^-1;
}
int dfs(int x,int f)
{
	if(x==T)
		return f;
	int w,used=0;
	for(edge *p=head[x];p;p=p->next)
		if(p->len&&dep[p->to]==dep[x]+1)
		{
			w=dfs(p->to,min(p->len,f-used));
			p->len-=w;
			p->rev->len+=w;
			used+=w;
			if(used==f)
				return f;
		}
	if(used^f)
		dep[x]=-1;
	return used;
}
int dinic()
{
	int ans=0;
	while(bfs())
		ans+=dfs(S,inf);
	return ans;
}
struct chairtree
{
	chairtree *ls,*rs;
	int id,val;
	void* operator new(size_t)
	{
		static chairtree mem[maxn],*p=mem;
		return p++;
	}
}*root[5010];
void insert(chairtree *&x,chairtree *y,int v,int p,int l,int r)
{
	x=new chairtree();
	*x=*y;
	x->id=++cnt;
	++x->val;
	if(l==r)
	{
		add(x->id,p,inf);
		add(x->id,y->id,inf);
		return;
	}
	int mid=l+r>>1;
	if(mid>=v)
		insert(x->ls,y->ls,v,p,l,mid);
	else
		insert(x->rs,y->rs,v,p,mid+1,r);
	add(x->id,x->ls->id,inf);
	add(x->id,x->rs->id,inf);
}
void query(chairtree *x,int p,int l,int r,int L,int R)
{
	if(l==L&&r==R)
	{
		add(p,x->id,inf);
		return;
	}
	if(!x->val)
		return;
	int mid=L+R>>1;
	if(mid>=r)
		query(x->ls,p,l,r,L,mid);
	else if(mid<l)
		query(x->rs,p,l,r,mid+1,R);
	else
		query(x->ls,p,l,mid,L,mid),
		query(x->rs,p,mid+1,r,mid+1,R);
}
int a[5010];
int b[5010];
int w[5010];
int l[5010];
int r[5010];
int p[5010];
int main()
{
	root[0]=new chairtree();
	root[0]->ls=root[0]->rs=root[0];
	int n;
	read(n);
	cnt=n;
	S=++cnt;
	T=++cnt;
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		read(b[i]);
		read(w[i]);
		read(l[i]);
		read(r[i]);
		read(p[i]);
		add(S,i,b[i]);
		add(i,T,w[i]);
		sum+=b[i];
		sum+=w[i];
	}
	for(int i=1;i<=n;i++)
	{
		add(i,++cnt,p[i]);
		query(root[i-1],cnt,l[i],r[i],0,inf);
		insert(root[i],root[i-1],a[i],i,0,inf);
	}
	printf("%d\n",sum-dinic());	
}

