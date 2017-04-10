#include<cstdio>
#define m 10007
int n;char c;int main(){while(c<'0')c=getchar();while(c>='0')n=(n*10+c-'0')%m,c=getchar();printf("%d\n",(n+2)*(n+1)%m*(n)%m*1668%m);}