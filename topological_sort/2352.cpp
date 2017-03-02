#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=10010;
long long t[maxn];
vector <int> att[maxn];
long long f[maxn];
long long mdfs(int i)
{
	if(f[i]==-1)
	{
		long long s=0;
		for (int j=0;j<att[i].size();j++) 
			s=max(s,mdfs(att[i][j]));
		f[i]=s+t[i];
	}
	return f[i];
}

int main() 
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&t[i]);
		f[i]=-1;
	}
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		att[b].push_back(a);
	}
	long long ans = 0;
	for(int i=1;i<=n;i++) 
		ans=max(ans,mdfs(i));
	printf("%lld\n", ans);
}
