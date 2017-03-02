#include <stdio.h>
#include <string.h>
int main()
{
	char s[4],ch[260],s2[260],s3[260];
	int i,len,j,k,m;
	gets(s);
	gets(ch);
	len=strlen(ch);
	if(ch[0]>='A'&&ch[0]<='Z')
		ch[0]+=32;
	printf("%s",s);
	for(i=0;i<=len;i++)
	{
		if(ch[i]=='s'&&ch[i-1]=='i'&&ch[i+1]==' ')
		{
			for(j=i+1;j<=len-2;j++)
				printf("%c",ch[j]);
			printf(" ");
			for(j=0;j<=i;j++)
				printf("%c",ch[j]);
			printf("!");
		}
	}
	return 0;
}
