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
	g=pos;
	for(i=pos;i<=n;i++)
		if(a[i]>='5')
		{
			g=i;
			break;
		}
	a[0]='0';
	bool f;
	tail=n;
	while(t--&&(g>pos&&a[g]>='5'))
	{
		a[g]='0';
		tail=g;
		if(g!=pos+1)
		{
			a[g-1]++;
			f=true;
			g=g-1;
		}
		else
		{
			a[g-2]++;
			g=g-2;
		}
		while(g>=0&&a[g]==':')
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
