#include <stdio.h>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
queue <int> q;
map <int,int> pre;
int a,b;
int main()
{
	scanf("%d%d",&a,&b);
	q.push(b);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		if(x==0)
			break;
		if(x==a)
			break;
		if(x%10==1)
			q.push(x/10),pre[x/10]=x;
		if(x%2==0)
			q.push(x/2),pre[x/2]=x;
	}
	if(pre[a])
	{
		puts("YES");
		int cnt=0;
		for(int i=a;i!=b;i=pre[i])
			++cnt;
		++cnt;
		printf("%d\n",cnt);
		for(int i=a;i!=b;i=pre[i])
			printf("%d ",i);
		printf("%d\n",b);
	}
	else
		puts("NO");
}
