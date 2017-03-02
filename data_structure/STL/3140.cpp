#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=7.2e6+10;
int n,m,q,u,v,t;
struct queue
{
	int a[maxn];
	int l,r;
	queue()
	{
		l=1,r=0;
	}
	int front()
	{
		return a[l];
	}
	void pop()
	{
		++l;
	}
	void push(int x)
	{
		return a[++r]=x;
	}
	int size()
	{
		return r-l+1;
	}
}q[3];
int b[maxn];
int main()
{
	scanf("%d%d%d%d%d%d",&n,&m,&q,&u,&v,&t);
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		q[0].push(x);
	}
	for(int i=1;i<=n;i++)
	{
		int x=0;
		for(int j=0;j<3;j++)
			if(q[j].size>0&&q[j].front()>q[x].front())
				x=j;
		if(i%t==0)
			printf("%d ",q[x].first);
		q[1].push(q[x].front()*1ll*u/v);
		q[2].push(q[x].front()-q[x].front()*1ll*u/v);
		q[x].pop();
	}
	puts("");
	for(int i=0;i<3;i++)
		while(q[i].size()>0)
			b[++b[0]]=q[i].front(),q[i].pop();
	sort(b+1,b+b[0]+1);
	for(int i=1;i<)
}
