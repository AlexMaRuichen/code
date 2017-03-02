#include <algorithm>
#include <set>
#include <stack>
#include <stdio.h>
using namespace std;
set   <int> Set;
stack <int> Stack;
int h[1000010];
int n;
int ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int tmpa,tmpb;
		scanf("%d%d",&tmpa,&tmpb);
		while(Stack.size()&&tmpb<Stack.top())
			Stack.pop(),ans++;	
		if(Stack.empty()||Stack.top()<tmpb)
			Stack.push(tmpb);
	}
	while(Stack.size())
		Stack.pop(),ans++;
	printf("%d",ans);
}
