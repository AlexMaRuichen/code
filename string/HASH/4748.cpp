#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;
int hash(char *s)
{
	static const int seed=29;
	int val=0;
	for(int i=0;i<2;i++)
		val=val*seed+s[i]-'A';
	return val;
}
multiset <int> s[760];
int n,ans;
char a[15],b[15];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s%s",a,b);
		int v1=hash(a),v2=hash(b);
		if(v1^v2)
			ans+=s[v1].count(v2);
		s[v2].insert(v1);
	}
	printf("%d\n",ans);
}
