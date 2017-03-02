#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn=1e5;
const int mod=1e4;
struct hpc
{
    int len;
    int x[maxn];
    bool flag;
    hpc()
    {
        len=1;
        flag=0;
        memset(x,0,sizeof(x));
    }
    void read()
    {
        char s[maxn];
        scanf("%s",s+1);
        int l=strlen(s+1);
        int i=1;
        int cnt=0;
        if(s[1]=='-')
            flag=true,++i,len=(l+2)/4;
        else
            len=(l+3)/4;
        int num=0;
        int rem=l%4;
        for(;i<=l;i++)
        {
            num=(num<<3)+(num<<1);
            num+=s[i]-'0';
            if((i-rem)%4==0)
            {
                x[len-cnt++]=num;
                num=0;
            }
        }
    }
    void print()
    {
        if(flag)
            printf("-");
        printf("%d",x[len]);
        for(int i=len-1;i;i--)
            printf("%04d",x[i]);
        puts("");
    }
    void operator *= (const hpc &s)
    {
        hpc res;
        res.flag=flag^s.flag;
        res.len=len+s.len;
        for(int i=1;i<=len;i++)
        {
            int num=0,t;
            for(int j=1;j<=s.len;j++)
            {
                t=x[i]*s.x[j]+res.x[i+j-1]+num;
                res.x[i+j-1]=t%mod;
                num=t/mod;
            }
            if(num)
                res.x[i+s.len]=num;
        }
        *this=res;
        while(!x[len]&&len>1)
            --len;
        if(len==1&&!x[1])
            flag=false;
    }
}A,B;
int main()
{
    A.read();
    B.read();
    A*=B;
    A.print();
}
 
