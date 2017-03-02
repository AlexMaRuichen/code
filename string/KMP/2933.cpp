#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=1e6+10;
int next[maxn];
char s[maxn],t[maxn];
int pos[maxn];
int f[maxn];
int main()
{
	scanf("%s%s",s+1,t+1);
	int len1=strlen(s+1),len2=strlen(t+1);
	for(int i=2,j=0;i<=len2;i++)
	{
		while(j&&t[j+1]!=t[i])
			j=next[j];
		if(t[j+1]==t[i])
			++j;
		next[i]=j;
	}
	for(int i=1,j;i<=len1;i++)
	{
		j=f[pos[pos[0]]];
		while(j&&t[j+1]!=s[i])
			j=next[j];
		if(t[j+1]==s[i])
			++j;
		if(j==len2)
			pos[0]-=len2-1;
		else
			f[i]=j,pos[++pos[0]]=i;
	}
	for(int i=1;i<=pos[0];i++)
		printf("%c",s[pos[i]]);
	puts("");
}
