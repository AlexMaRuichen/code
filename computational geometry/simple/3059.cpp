#include <stdio.h>
#include <functional>
#include <algorithm>
using namespace std;
const int maxn=50010;
class FieldReduction
{
	int n;
	int x[maxn];
	int y[maxn];

	int minx[10];
	int miny[10];
	int maxx[10];
	int maxy[10];

public:
	int solve()
	{
		int ans=~0u>>1;

		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&x[i],&y[i]);

			minx[++minx[0]]=x[i];
			push_heap(minx+1,minx+minx[0]+1);
			if(minx[0]>4)
				pop_heap(minx+1,minx+minx[0]--+1);

			miny[++miny[0]]=y[i];
			push_heap(miny+1,miny+miny[0]+1);
			if(miny[0]>4)
				pop_heap(miny+1,miny+miny[0]--+1);

			maxx[++maxx[0]]=x[i];
			push_heap(maxx+1,maxx+maxx[0]+1,greater<int>());
			if(maxx[0]>4)
				pop_heap(maxx+1,maxx+maxx[0]--+1,greater<int>());

			maxy[++maxy[0]]=y[i];
			push_heap(maxy+1,maxy+maxy[0]+1,greater<int>());
			if(maxy[0]>4)
				pop_heap(maxy+1,maxy+maxy[0]--+1,greater<int>());
		}

		int cnt=0;
		for(int a=1;a<=4;a++)
			for(int b=1;b<=4;b++)
				for(int c=1;c<=4;c++)
					for(int d=1;d<=4;d++)
					{
						cnt=0;
						for(int i=1;i<=n;i++)
							if(x[i]>maxx[a]||x[i]<minx[b]||y[i]>maxy[c]||y[i]<miny[d])
								++cnt;
						if(cnt<=3)
							ans=min(ans,(maxx[a]-minx[b])*(maxy[c]-miny[d]));
					}

		return ans;
	}
}cls;
int main()
{
	printf("%d\n",cls.solve());
}
