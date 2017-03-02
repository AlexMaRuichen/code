#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=50010;
class HighCardWins
{
	int n;
	int a[maxn];
	int b[maxn];
	int ans;
	int ptra,ptrb;
public:
	HighCardWins()
	{
		ans=0;
		ptra=ptrb=0;
	}
	int solve()
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		a[n+1]=(n<<1)+1;
		for(int i=1;i<=n;i++)
			if(a[i+1]-a[i]!=1)
				for(int j=a[i]+1;j<a[i+1];j++)
					b[++ptrb]=j;
		ptra=ptrb=1;
		while(ptra<=n)
		{
			if(a[ptra]>b[ptrb])
				--n,++ptrb;
			else
				++ans,++ptra,++ptrb;
		}
		return ans;
	}
}cls;
int main()
{
	printf("%d\n",cls.solve());
}
