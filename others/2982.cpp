#include <stdio.h>
#include <algorithm>
using namespace std;
int n;int a;int ans=-(~0u>>2),last;char getc(){static const int LEN = 1<<15;static char buf[LEN],*S=buf,*T=buf;if(S == T){T=(S=buf)+fread(buf,1,LEN,stdin);if(S == T)return EOF;}return *S++;}inline int read(){char ch;bool flag=false;int a=0;while(!((((ch=getc())>='0')&&(ch<='9'))||(ch=='-')));if(ch != '-'){a=(a<<1)+(a<<3);a+=ch-'0';}  else{flag = true;}  while(((ch = getc()) >= '0') && (ch <= '9')){a =(a<<1)+(a<<3);a+=ch-'0';}if(flag)return -a;return a;}int main(){n=read();for(int i=1;i<=n;i++){a=read();last+=a;ans=max(ans,last);last=(last>=0?last:0);}printf("%d\n",ans);}
