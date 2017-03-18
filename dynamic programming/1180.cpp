#include <algorithm>
#include <set>
#include <stack>
#include <stdio.h>
#include <string>
using namespace std;
int n;
const int mod=12345;
int f[2000];
int main()
{
	scanf("%d",&n);
	f[0]=f[1]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=0;j<=i;j++)
			(f[i]+=f[j]*f[i-j-2])%=mod;
		(f[i]+=f[i-1])%=mod;
	}
	printf("%d",f[n]);
}

