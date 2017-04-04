#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

const int maxn = 1e4 + 10;
const int mod = 1e4 + 7;

int n;
int prime[maxn];
bool v[maxn];
int tot;
int a[maxn];

int calc()
{ 
   
  int res=0; 
   
  for(int i=1;i<=n;i++) 
     
    for(int j=1;j<=n;j++) 
     
    { 
       
      res+=__gcd(a[i],a[j])*(__gcd(a[i],a[j])-1); 
       
      res%=10007; 
     
    } 
   
  return res; 

}

__attribute__((optimize(2))) int main()
{
	while (scanf("%d", &n) == 1)
	{
		memset(a, 0 ,sizeof(a));
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
 		printf("%d\n", calc());
	}
}