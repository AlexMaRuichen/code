#include <stdio.h>
#include <algorithm>
#include <set>
#include <queue>
#include <vector>
using namespace std;
const int maxn=1000010;
int n,g;
int ans;
set <int> s[2001];
queue <int> q;
vector <int> idx[maxn];
bool v[maxn];
int main()
{
	scanf("%d%d",&n,&g);
	q.push(1);
	for(int i=1;i<=g;i++)
	{
		static int cnt,x;
		scanf("%d",&cnt);
		for(int j=1;j<=cnt;j++)
		{
			scanf("%d",&x);
			s[i].insert(x);
			idx[x].push_back(i);
		}
	}
	while(q.size())
	{
		static int x;
		++ans;
		x=q.front();
		q.pop();
		v[x]=true;
		for(int i=0;i<idx[x].size();i++)
		{
			s[idx[x][i]].erase(s[idx[x][i]].find(x));
			if(s[idx[x][i]].size()==1&&!v[*s[idx[x][i]].begin()])
				q.push(*s[idx[x][i]].begin()),v[*s[idx[x][i]].begin()]=true;
		}
	}
	printf("%d\n",ans);
}
