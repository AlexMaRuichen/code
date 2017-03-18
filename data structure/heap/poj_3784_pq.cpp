#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
int minh[10010];
int maxh[10010];
int sizemax;
int sizemin;
int P;
int sn,n;
int cnt;
int main()
{
	scanf("%d",&P);
	int tmp;
	while(P--)
	{
		memset(minh,0,sizeof(minh));
		memset(maxh,0,sizeof(maxh));
		sizemin=sizemax=0;
		cnt=0;
		scanf("%d%d",&sn,&n);
		printf("%d %d\n",sn,n/2+1);
		make_heap(maxh+1,maxh+sizemax+1);
		make_heap(minh+1,minh+sizemin+1,greater<int>());
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&tmp);
			if(!sizemax)
			{
				maxh[++sizemax]=tmp;
				push_heap(maxh+1,maxh+sizemax+1);
			}
			else
			{
				if(tmp>maxh[1])
				{
					minh[++sizemin]=tmp;
					push_heap(minh+1,minh+sizemin+1,greater <int>());
				}
				else
				{
					maxh[++sizemax]=tmp;
					push_heap(maxh+1,maxh+sizemax+1);
				}
			}
			while(sizemax<sizemin)
			{
				maxh[++sizemax]=minh[1];
				push_heap(maxh+1,maxh+sizemax+1);
				pop_heap(minh+1,minh+sizemin+1,greater <int>());
				sizemin--;
			}
			while(sizemin<sizemax-1)
			{
				minh[++sizemin]=maxh[1];
				push_heap(minh+1,minh+sizemin+1,greater <int>());
				pop_heap(maxh+1,maxh+sizemax+1);
				sizemax--;
			}
			if(i%2)
			{
				++cnt;
				if(cnt==1)
					printf("%d",maxh[1]);
				else
					printf(" %d",maxh[1]);
			}
			if(cnt==10)
				puts(""),cnt=0;
		}
		if(cnt)
			puts("");
	}
}
