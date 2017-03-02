#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
const int maxn=(1<<19)+10;
char s[maxn];
char t[maxn];
int ans;
int main()
{
	int n,m,k;
	scanf("%d%d%d%s%s",&n,&m,&k,s+1,t+1);
	for(int i=1;i<=n-m+1;i++)
		for(int j=1;j<=m;j++)
		{
			for(int l=max(i+j-1-k,1);l<=min(i+j-1+k,n);l++)
				if(s[l]==t[j])
					goto lableA;
			break;
			lableA:
			if(j==m)
				++ans;
		}
	printf("%d\n",ans);
}
