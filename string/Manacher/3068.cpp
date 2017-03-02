#include <stdio.h>
#include <string.h>
#define min(a,b) (a)<(b)?(a):(b)
#define max(a,b) (a)>(b)?(a):(b)
char s[220010];
char r[110010];
int p[220010];
int manacher()
{
	int len=strlen(r);
	s[0]='&';
	s[1]='^';
	for(int i=1;i<=len;i++)
		s[i<<1]=r[i-1],s[i<<1|1]='^';
	int ans=0,mx=0,id=0;
	++len;
	len<<=1;
	for(int i=1;i<len;i++)
	{
		if(mx>i)
			p[i]=min(p[(id<<1)-i],mx-i);
		else
			p[i]=1;
		while(s[i-p[i]]==s[i+p[i]])
			++p[i];
		if(mx<p[i]+i)
			mx=p[i]+i,id=i;
		if(ans<p[i])	
			ans=p[i];
	}
	return ans-1;
}
int main()
{
	while(scanf("%s",r)!=EOF)
		printf("%d\n",manacher());
}
