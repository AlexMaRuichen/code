#include <stdio.h>
#include <algorithm>
#include <ctype.h>
using namespace std;
typedef long long ll;
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
    static int   D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
const int maxn=2000010;
int n,d;
ll p;
int w[maxn];
ll sum[maxn];
ll f[maxn];
ll q[maxn];
int ans;
int h,t;
int main()
{
	scanf("%d%lld%d",&n,&p,&d);
	for(int i=1;i<=n;i++)
	{
		w[i]=read();
		sum[i]=sum[i-1]+w[i];
	}
	for(int i=1;i<=n;i++)
		f[i]=sum[i+d-1]-sum[i-1];
	for(int i=d,j=h=1;i<=n;i++)
	{
		while(h<=t&&f[q[t]]<=f[i-d+1])
			t--;
		q[++t]=i-d+1;
		while(sum[i]-sum[j-1]-f[q[h]]>p)
		{
			++j;
			while(q[h]<j)
				++h;
		}
		if(i-j+1>ans)
			ans=i-j+1;
	}
	printf("%d\n",ans);
}
