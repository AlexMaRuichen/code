#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=100;
int n;
int a[maxn];
int st;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	if(a[n]==0)
		puts("UP");
	else if(a[n]==15)
		puts("DOWN");
	else if(n==1)
		puts("-1");
	else
		a[n]>a[n-1]?puts("UP"):puts("DOWN");
}
