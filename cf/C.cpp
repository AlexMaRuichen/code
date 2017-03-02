#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;
const int maxn=2e5+10;
set <int> s;
int n,t;
char a[maxn];
int pos;
int main()
{
	register int  i,tail,g;
	scanf("%d%d",&n,&t);
	scanf("%s",a+1);
	for(i=1;i<=n;i++)
		if(a[i]=='.')
		{
			pos=i;
			break;
		}
	a[0]='0';
	bool f;
	tail=n;
	while(t--)
	{
		f=false;
		for(i=pos+1;i<=tail;i++)
			if(a[i]>='5')
			{	
				if(i-1!=pos)
					g=i-1,a[i-1]++;
				else
					g=i-2,a[i-2]++;
				tail=i-1;
				if(tail!=pos)
					f=true;
				while(a[g]==':'&&g>0)
				{
					if(g-1==pos)
					{
						a[g]='0';
						a[g-2]++;
						g-=2;
					}
					else 
					{
						a[g]='0';
						a[g-1]++;
						--g;
					}
				}
				break;
			}
		if(!f)
			break;
	}
	if(a[0]!='0')
		printf("%c",a[0]);
	for(i=1;i<pos;i++)
		printf("%c",a[i]);
	while(a[tail]=='0')
		--tail;
	if(tail!=pos)	
	{
		printf("%c",46);
		for(i=pos+1;i<=tail;i++)
			printf("%c",a[i]);
	}
	puts("");
}
