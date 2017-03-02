#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
#define dis(a,b) (abs(posx[a]-posx[b])+abs(posy[a]-posy[b])+abs(posz[a]-posz[b]))*y
using namespace std;
const int maxn=1010;
const int maxm=2e6+10;
const int inf=0x3f3f3f3f;
int n,x,y,z;

struct edge
{
	int x,y,val;
	edge *next;
	edge(){}
	edge(int x,int y,int z);
	void* operator new(size_t);
}*root,mempool[maxm],*p;
void* edge:: operator new(size_t)
{
	return p++;
}
edge::edge(int x,int y,int z)
{
	this->x=x;
	this->y=y;
	this->val=z;
	this->next=root;
}
int vis[maxn];
int mark[maxn];
int in[maxn];
int pre[maxn];

int process(int x)
{
	int ans=0;
	while(true)
	{
		for(int i=1;i<=n;i++)
			in[i]=inf;
		for(edge *p=root;p;p=p->next)
			if(p->val<in[p->y]&&p->x^p->y)
				in[p->y]=p->val,pre[p->y]=p->x;
		for(int i=1;i<=n;i++)
			if(i^x&&in[i]==inf)
				return -1;
		memset(mark,-1,sizeof(mark));
		memset(vis,-1,sizeof(vis));
		in[x]=0;
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			ans+=in[i];
			int v=i;
			while(v^x&&vis[v]^i&&mark[v]<0)
				vis[v]=i,v=pre[v];
			if(v^x&&mark[v]<0)
			{
				++cnt;
				for(int u=pre[v];u^v;u=pre[u])
					mark[u]=cnt;
				mark[v]=cnt;
			}
		}
		if(!cnt)
			break;
		for(int i=1;i<=n;i++)
			if(mark[i]<0)
				mark[i]=++cnt;
		for(edge *p=root;p;p=p->next)
		{
			static int x,y;
			x=p->x;
			y=p->y;
			p->x=mark[x];
			p->y=mark[y];
			if(mark[x]^mark[y])
				p->val-=in[y];
		}
		n=cnt,x=mark[x];
	}
	return ans;
}
int posx[maxn];
int posy[maxn];
int posz[maxn];
int main()
{
	while(scanf("%d%d%d%d",&n,&x,&y,&z)&&(n|x|y|z))
	{
		++n;
		root=NULL;
		p=mempool;
		for(int i=2;i<=n;i++)
			scanf("%d%d%d",&posx[i],&posy[i],&posz[i]);
		for(int i=2;i<=n;i++)
		{
			static int k;
			scanf("%d",&k);
			while(k--)
			{
				static int to;
				scanf("%d",&to);
				++to;
				if(to^i)
				{
					if(posz[i]<posz[to])
						root=new edge(i,to,dis(i,to)+z);
					else 
						root=new edge(i,to,dis(i,to));
				}
			}
		}
		for(int i=2;i<=n;i++)
			root=new edge(1,i,posz[i]*x);
		int ans=process(1);
		if(ans^-1)
			printf("%d\n",ans);
		else
			puts("poor XiaoA");
	}
}
