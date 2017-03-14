#include <stdio.h>  
#include <string.h>  

#include <algorithm>

using namespace std;  

typedef long long LL;  

const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;

LL ans;  
char s[maxn];  
int Next[maxn], cnt[maxn];

int KMP()  
{  
    int i ,j = 0;  
    cnt[1] = 1;  
    for (i = 2; s[i]; i++)  
    {  
        while (j && s[j + 1] != s[i])
			j = Next[j];  
        if (s[j + 1] == s[i]) 
			j++;  
        Next[i] = j;  
        cnt[i] = cnt[j] + 1;  
    }  
    j = 0;
	ans = 1;  
    for (i = 2; s[i]; i++)  
    {  
        while (j && s[j + 1] != s[i])  
			j = Next[j];  
        if (s[j + 1] == s[i]) 
			j++;  
        while((j << 1) > i) 
			j = Next[j];  
        ans *= cnt[j] + 1;  
        ans %= mod;  
    }
	return ans;
}  
int main()  
{  
    int T; 
       
    scanf("%d", &T);
	while (T--)
	{
		scanf("%s", s + 1);
		printf("%d\n", KMP());
	}
       
}  