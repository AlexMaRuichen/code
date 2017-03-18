#include <stdio.h>
#include <algorithm>
#include <queue>
#define assign(x)  x=++cnt
#define ch(x) (x==0?'L':x==1?'R':x==2?'U':'D')
#define posx(x) (x<1?r:x>r?1:x)
#define posy(x) (x<1?c:x>c?1:x)
using namespace std;
int dx[]={0,0,-1,1};
int dy[]={-1,1,0,0};
const int maxn=500;
const int inf=1e9;
int cnt;
struct edge
{
	int to,from,len,cost;
	edge *next,*rev;
	edge(){}
	edge(int to,int from,int len,int cost,edge *next):to(to),from(from),len(len),cost(cost),next(next){}
	void* operator new(size_t)
	{
		static edge *l,*r;
		if(l==r)
			r=(l=new edge[1<<15])+(1<<15);
		return l++;
	}
}*head[maxn];
void add(int x,int y,int z,int c)
{
	head[x]=new edge(y,x,z,c,head[x]);
	head[y]=new edge(x,y,0,-c,head[y]);
	head[x]->rev=head[y];
	head[y]->rev=head[x];
}
int S,T;
edge *pre[maxn];
bool spfa()
{
	static queue <int> q;
	static int f[maxn];
	static bool v[maxn];
	for(int i=1;i<=cnt;i++)
		f[i]=inf;
	f[S]=0;
	q.push(S);
	v[S]=true;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(edge *p=head[x];p;p=p->next)
			if(p->len&&f[p->to]>f[x]+p->cost)
			{
				f[p->to]=f[x]+p->cost;
				pre[p->to]=p;
				if(!v[p->to])
					v[p->to]=true,q.push(p->to);
			}
		v[x]=false;
	}
	return f[T]^inf;
}
int augment()
{
	int w=inf,ans=0;
	for(edge *p=pre[T];p;p=pre[p->from])
		w=min(w,p->len);
	for(edge *p=pre[T];p;p=pre[p->from])
		p->len-=w,p->rev->len+=w,ans+=p->cost*w;
	return ans;
}
int MCMF()
{
	int ans=0;
	while(spfa())
		ans+=augment();
	return ans;
}
int in[20][20];
int out[20][20];
int main()
{
	int r,c;
	scanf("%d%d",&r,&c);
	assign(S);
	assign(T);
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			assign(in[i][j]),assign(out[i][j]);
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
		{
			static char s[5];
			add(S,in[i][j],1,0);
			add(out[i][j],T,1,0);
			scanf("%1s",s);
			for(int k=0;k<4;k++)
				add(in[i][j],out[posx(i+dx[k])][posy(j+dy[k])],1,bool(s[0]^ch(k)));
		}
	printf("%d\n",MCMF());
}
