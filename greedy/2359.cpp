#include <stdio.h>
#include <algorithm>
#include <ctype.h>
using namespace std;char getc(){static const int LEN = 1<<15;static char buf[LEN],*S=buf,*T=buf;if(S == T){T = (S=buf)+fread(buf,1,LEN,stdin);if(S == T)return EOF;}return *S++;}int  read(){static char ch;static int D;while(!isdigit(ch=getc()));for(D=ch-'0'; isdigit(ch=getc());)D=(D<<3)+(D<<1)+(ch-'0');return D;}const int maxn=1e5+10;int a[maxn];int n;long long ans;int main(){int i;n=read();for(i=1;i<=n;i++)a[i]=read();for(i=0;i<=n;i++)ans+=abs(a[i+1]-a[i]);printf("%lld\n",ans>>1);}
