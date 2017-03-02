#include <stdio.h>
#include <stack>
#include <algorithm>
using namespace std;
const int maxn=5e4+10;
int g,d,n,b;
struct gasoline
{
	int pos,cost;
	gasoline(){}
	gasoline(int _pos,int _cost):pos(_pos),cost(_cost){}
	bool operator < (const gasoline &s) const 
	{
		return pos<s.pos;
	}
}sta[maxn];
stack <int> s;
int next[maxn];
int main()
{
	scanf("%d%d%d%d",&n,&g,&b,&d);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&sta[i].pos,&sta[i].cost);
	sort(sta+1,sta+n+1);
	for(int i=n;i;i--)
	{
		while(!s.empty()&&sta[s.top()].cost>=sta[i].cost)
			s.pop();
		next[i]=s.empty()?-1:s.top();
		s.push(i);
	}
	b-=sta[1].pos;
	long long cost=0;
	for(int i=1;i<=n;i++)
	{
		if(b<0)
		{
			puts("-1");
			return 0;
		}
		int need=min(g,(next[i]==-1?d:sta[next[i]].pos)-sta[i].pos);
		if(need>b)
		{
			cost+=(long long)(need-b)*sta[i].cost;
			b=need;
		}
		b-=(i==n?d:sta[i+1].pos)-sta[i].pos;
	}
	if(b<0)
		puts("-1");
	else 
		printf("%lld\n",cost);	
}
