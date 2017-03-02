#include <stdio.h>
#include <string.h>
int main(){int dep,ans;char s[100010];scanf("%s",s);int len=strlen(s);for(int i=0;i<len;i++){if(s[i]=='(')++dep;else--dep;if(dep<0)++ans,dep+=2;}ans+=dep/2;printf("%d\n",ans);}
