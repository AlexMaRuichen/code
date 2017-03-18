#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=200010;
struct edge
{
	int to,len;
	edge *next,*rev;
	bool ban;
	edge(){}
	edge(int to,int len,edge *next):to(to),len(len),next(next),ban(false){}
	void* operator new(size_t)
	{
		static edge *l,*r;
		if(l==r)
			r=(l=new edge[1<<15])+(1<<15);
		return l++;
	}
}*head[maxn];
void add(int x,int y,int z)
{
	head[x]=new edge(y,z,head[x]);
	head[y]=new edge(x,z,head[y]);
	head[x]->rev=head[y];
	head[y]->rev=head[x];
}
int f[1000010];
int size[maxn];
int n,k;
int get(int x,int fa,int s)
{
	size[x]=1;
	int ans=0;
	bool flag=true;
	for(edge *p=head[x];p;p=p->next)
		if(!p->ban&&p->to^fa)
		{
			ans=max(ans,get(p->to,x,s));
			size[x]+=size[p->to];
			if(size[p->to]>s>>1)
				flag=false;
		}
	if(s-size[x]>s>>1)
		flag=false;
	return flag?x:ans;
}
int ans=0x3f3f3f3f;
void dfs(int x,int t,int d,int fa)
{
	size[x]=1;
	if(t<=k)
		ans=min(ans,f[k-t]+d);
	for(edge *p=head[x];p;p=p->next)
		if(!p->ban&&p->to^fa)
			dfs(p->to,t+p->len,d+1,x),size[x]+=size[p->to];
}
void merge(int x,int t,int d,int fa)
{
	if(t<=k)
		f[t]=min(f[t],d);
	for(edge *p=head[x];p;p=p->next)
		if(!p->ban&&p->to^fa)
			merge(p->to,t+p->len,d+1,x);
}
void clear(int x,int t,int d,int fa)
{
	if(t<=k)
		f[t]=1e9;
	for(edge *p=head[x];p;p=p->next)
		if(!p->ban&&p->to^fa)
			clear(p->to,t+p->len,d+1,x);
}
void partition(int x,int s)
{
	f[0]=0;
	x=get(x,0,s);
	for(edge *p=head[x];p;p=p->next)
		if(!p->ban)
			dfs(p->to,p->len,1,x),
			merge(p->to,p->len,1,x);
	for(edge *p=head[x];p;p=p->next)
		if(!p->ban)
			clear(p->to,p->len,1,x);
	for(edge *p=head[x];p;p=p->next)
		if(!p->ban)
			p->ban=p->rev->ban=true,partition(p->to,size[p->to]);
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++)
		f[i]=1e9;
	for(int i=1;i<n;i++)
	{
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(++x,++y,z);
	}
	partition(1,n);
	printf("%d\n",ans<n?ans:-1);
}
