#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
#define assign(x) x=++cnt
using namespace std;
const int maxn=2000;
const int maxm=maxn*100;
const int inf=1e9;
struct size
{
int n,m;

int to[maxm];
int next[maxm];
int len[maxm];
int cost[maxm];
int from[maxm];
int head[maxn];
int tot=1;
void add(int x,int y,int z,int c)
{
	to[++tot]=y;
	next[tot]=head[x];
	len[tot]=z;
	cost[tot]=c;
	from[tot]=x;
	head[x]=tot;
	
	to[++tot]=x;
	next[tot]=head[y];
	len[tot]=0;
	cost[tot]=-c;
	from[tot]=y;
	head[y]=tot;
}

int f[maxn];
bool v[maxn];
int pre[maxn];
int S=maxn-1,T=maxn-2;
queue <int> q;
bool spfa()
{
	for(int i=1;i<maxn;i++)
		f[i]=inf;
	f[S]=0;
	v[S]=true;
	q.push(S);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i])
			if(len[i]&&f[to[i]]>f[x]+cost[i])
			{
				f[to[i]]=f[x]+cost[i];
				pre[to[i]]=i;
				if(!v[to[i]])
					v[to[i]]=true,q.push(to[i]);
			}
		v[x]=false;
	}
	return f[T]^inf;
}
int augment()
{
	int w=inf,ans=0;
	for(int i=pre[T];i;i=pre[from[i]])
		w=min(w,len[i]);
	for(int i=pre[T];i;i=pre[from[i]])
		len[i]-=w,len[i^1]+=w,ans+=cost[i]*w;
	return ans;
}
int MCMF()
{
	int ans=0;
	while(spfa())
		ans+=augment();
	return ans;
}
int cnt;
int cook[110];
int t[110];
int dish[50];
int a[50][110];
bool available()
{
	for(int i=head[S];i;i=next[i])
		if(len[i])
			return true;
	return false;
}
void extend()
{
	for(int j=1;j<=m;j++)
		for(int i=head[cook[j]];i;i=next[i])
			if(!len[i])
			{
				assign(cook[j]);
				++t[j];
				for(int k=1;k<=n;k++)
					add(dish[k],cook[j],1,t[j]*a[k][j]);
				add(cook[j],T,1,0);
			}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		assign(dish[i]);
	for(int i=1;i<=m;i++)
		assign(cook[i]),t[i]=1;
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		add(S,dish[i],x,0);
	}
	for(int i=1;i<=m;i++)
		add(cook[i],T,1,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			add(dish[i],cook[j],1,a[i][j]);
		}
	int ans=0;
	while(available())
	{
		ans+=MCMF();
		extend();
	}
	printf("%d\n",ans);
}
}obj;
int main()
{
	printf("%d\n",sizeof(obj));
}
