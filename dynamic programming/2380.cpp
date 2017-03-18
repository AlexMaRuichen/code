#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <ctype.h>
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
const int maxn=1010;
typedef pair<int,int> point;
int f[maxn][maxn];
point p[maxn];
int n;
int ans;
char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}

int  read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
int main()
{
    n=read();
	register int i,j;
    int k,val;
    for(i=1;i<=n;++i)
        p[i].first=read(),p[i].second=read(),ans=max(ans,p[i].second);
    sort(p+1,p+n+1);
    for(i=n;i;i--)
    {
        k=n+1;
        val=0;
        for(j=1;j<=i;j++)
        {
            while(k-1>i&&p[k-1].first-p[i].first>=p[i].first-p[j].first)
            {
                --k;
                val=max(val,p[k].second+f[k][i]);
            }
            f[i][j]=val;
        }
        ans=max(ans,p[i].second+val);
    }
    reverse(p+1,p+n+1);
    for(i=1;i<=n;i++)
        p[i].first=-p[i].first;
    for(i=n;i;i--)
    {
        k=n+1;
        val=0;
        for(j=1;j<=i;j++)
        {
            while(k-1>i&&p[k-1].first-p[i].first>=p[i].first-p[j].first)
            {
                --k;
                val=max(val,p[k].second+f[k][i]);
            }
            f[i][j]=val;
        }
        ans=max(ans,p[i].second+val);
    }
    printf("%d\n",ans);
}
