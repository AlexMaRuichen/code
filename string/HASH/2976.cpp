#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;
unsigned int BKDRHash(char *str)
{
    const static unsigned int seed=29;
    static unsigned int hash;
	hash=0;
    while(*str)
        hash=hash*seed+(*str++);
    return (hash & 0x7FFFFFFF);
}
char s[1010];
map <int,int> m;
int cnt;
int ans[10010];
int main()
{
	while(~scanf("%s",s))
	{
		unsigned int hash=BKDRHash(s);
		if(!m[hash])
			m[hash]=++cnt;
		++ans[m[hash]];
	}
	for(int i=1;i<=cnt;i++)
		printf("%d\n",ans[i]);
}
