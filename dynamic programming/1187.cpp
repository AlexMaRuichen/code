#include <stdio.h>
#include <algorithm>
#include <set>
#include <string.h>
#define check(x) (x)>100?true:v[x]
using namespace std;
const int maxn=110;
int l;
int n,s,t;
bool v[110];
typedef pair<int,int> point;
int p[maxn];
int f[maxn];
int main()
{
	scanf("%d%d%d%d",&l,&s,&t,&n);
	init();
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]);
	sort(p+1,p+n+1);
	memset(f,0x3f,sizeof(f));
	sets.insert(point(0,0));
	for(int i=1;i<=n;i++)
	{
		for(it=sets.begin();it!=sets.end();it++)
			if(check(p[i]-(*it).second))
			{
				f[i]=(*it).first;
				break;
			}
		++f[i];
		sets.insert(point(f[i],p[i]));
	}
	printf("%d\n",f[n]);
}
