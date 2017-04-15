#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
using namespace std;
char s[1010];
int ans;
int main()
{
	scanf("%s",s);
	int len=strlen(s);
	int num=0;
	for(int i=0;i<len;i++)
	{
		if(isalpha(s[i]))
		{
			if(s[i-3]!='.')
				ans+=num*100,num=0;
			else
				ans+=num,num=0;
		}
		else if(isdigit(s[i]))
			num=num*10+s[i]-'0';
	}
	if(s[len-3]!='.')
		ans+=num*100,num=0;
	else
		ans+=num,num=0;
	int idx=1;
	while(idx<=ans)
		idx*=10;
	idx/=10;
	if(idx>=100)
	{
		if(ans%100==0)
		{
			ans/=100;
			idx/=100;
			int p=idx/10%3;
			int cnt=0;
			while(idx)
			{
				++cnt;
				if(cnt%3==p&&cnt!=1)
					printf(".");
				printf("%d",ans/idx);
				ans%=idx;
				idx/=10;
			}
		}
		else
		{
			int p=idx/10%3;
			int cnt=0;
			while(idx>10)
			{
				++cnt;
				if(cnt%3==p&&cnt!=1)
					printf(".");
				printf("%d",ans/idx);
				ans%=idx;
				idx/=10;
			}
			printf(".");
			while(idx)
			{
				printf("%d",ans/idx);
				ans%=idx;
				idx/=10;
			}
		}
	}
	else
	{
		idx=10;
		printf("0.");
		while(idx)
		{
			printf("%d",ans/idx);
			ans%=idx;
			idx/=10;
		}
	}
	puts("");
}
