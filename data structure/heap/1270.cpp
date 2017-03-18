#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
priority_queue <int> pq;
int n;
int ans;
int main()
{
	scanf("%d",&n);
	int tmp;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&tmp);
		pq.push(-tmp);
	}
	int x1,x2;
	while(pq.size()>1)
	{
		x1=-pq.top();
		pq.pop();
		x2=-pq.top();
		pq.pop();
		ans+=x1;
		ans+=x2;
		pq.push(-(x1+x2));
	}
	printf("%d",ans);
}
