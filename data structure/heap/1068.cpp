#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
int a[200010];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int t=n;
	make_heap(a+1,a+n+1,greater <int>());
	for(int i=1;i<=n;i++)
	{
		printf("%d\n",a[1]);
		pop_heap(a+1,a+t+1,greater <int>());
		t--;
	}
}
