#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef pair<int,int> point;
int next[15];
int ans;
int n;
point p[15];
bool v[15];
bool c[15];
bool check(int x)
{
	c[x]=true;
	int go=0;
	for(int i=1;i<=n;i++)
		if(i!=x&&p[i].second==p[x].second&&p[x].first<p[i].first)
			if(go==0||p[go].first>p[i].first)
				go=i;
	if(go)
		if(c[next[go]]||check(next[go]))
			return true;
}

void dfs(int dep)
{
	if(dep>n>>1)
	{
		for(int i=1;i<=n;i++)
		{
			memset(c,0,sizeof(c));
			if(check(i))
			{
				++ans;
				break;
			}
		}
		return;
	}
	for(int i=1;i<=n;i++)
		if(!v[i])
		{
			v[i]=true;
			for(int j=1;j<=n;j++)
				if(!v[j])
				{
					next[i]=j;
					next[j]=i;
					v[j]=true;
					dfs(dep+1);
					v[j]=false;
					next[i]=next[j]=0;
				}
			v[i]=false;
		}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].first,&p[i].second);
	dfs(1);
	printf("%d\n",ans);
}
