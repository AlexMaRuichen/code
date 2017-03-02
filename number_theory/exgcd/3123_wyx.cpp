#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
long long a,b,c,k,mod;
long long exe_gcd(long long a, long long b, long long &x,long long &y)
{
    if(b==0)
    {
        x = 1,y = 0;return a;
    }
    long long G = exe_gcd(b,a%b,x,y);
    long long tmp = x ;
    x = y;
    y = tmp - (a/b) * y;
    return G;
}
int main()
{
    long long x,y;
    while(~scanf("%lld%lld%lld%lld",&a,&b,&c,&k) && (a|b|c|k))
    {
        mod = 1ll << k;
        long long gcd = exe_gcd(c,mod,x,y);
        x%=mod;
        (x += mod)%=mod;
        long long tmp = ((b-a)%mod+mod)%mod;
        mod/=gcd;
        tmp/=gcd;
        if((b-a)%gcd!=0)puts("FOREVER");
        else printf("%lld\n",((x*tmp)%mod+mod)%(mod));
    }
}
