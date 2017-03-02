#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e3+10;
int n;
int p[maxn];
bool v[maxn];
int cnt;
int ans;
int f[maxn][maxn];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]);
	p[++n]=0;
	sort(p+1,p+n+1);
	int pos=0,tpos;
	while(cnt<n)
	{
		tpos=1;
		for(int i=1;i<=n;i++)
			if(!v[i]&&abs(p[i]-p[pos])<abs(p[tpos]-p[pos]))
				tpos=i;
		ans+=(n-cnt)*abs(p[tpos]-p[pos]);
		pos=tpos;
		++cnt;
		v[pos]=true;
	}
	printf("%d\n",ans);
}
