#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=2010;
class CircularBarn
{
	int n;
	int a[maxn];
	int q[maxn];
	int h,t;
	long long ans;
public:
	long long solve()
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),a[i+n]=a[i];
		int last=0,sum=0,pos=0,fpos;
		for(int i=1;i<=n<<1;i++)
		{
			if(last<0)
				last=0,pos=i;
			last+=a[i]-1;
			if(last>sum)
				sum=last,fpos=pos;
		}
		h=1,t=ans=0;
		for(int i=fpos;i<fpos+n;i++)
		{
			while(a[i]--)
				q[++t]=i;
			ans+=(q[h]-i)*1ll*(q[h]-i);
			++h;
		}
		return ans;
	}
}cls;
int main()
{
	printf("%lld\n",cls.solve());
}
