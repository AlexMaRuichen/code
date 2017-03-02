#include <stdio.h>
#define min(i,j) (i)<(j)?(i):(j)
char s[10000010];
char r[5000010];
int p[10000010];
int len;
int main()
{
	fread(r,1,5000000,stdin);
	register int i;
	for(i=0;r[i]=='0'||r[i]=='1';i++);
	len=i;
	r[++len]=0;
	s[0]='&',s[1]='^';
	for(i=1;i<=len;i++)
		s[i<<1]=r[i-1],s[i<<1|1]='^';
	++len;
	len<<=1;
	int ans=0,pos,mx=0,id=0;
	for(i=1;i<len;i++)
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
			ans=p[i],pos=((i-p[i])>>1)+1;
	}
	printf("%d\n%d\n",pos,ans-1);
}	
