#include <stdio.h>
#include <functional>
#include <algorithm>
using namespace std;
const int maxn=10010;
int n;
int d[maxn];
int t[maxn];
double ans;
double dis;
int v=1;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		static char s[5];
		static int x;
		scanf("%s%d",s,&x);
		if(s[0]=='T')
			t[++t[0]]=x;
		else if(s[0]=='D')
			d[++d[0]]=x;
	}
	make_heap(d+1,d+d[0]+1,greater<int>());
	make_heap(t+1,t+t[0]+1,greater<int>());
	while(d[0]||t[0])
	{
		if(!d[0])
		{
			dis+=(t[1]-ans)/v;
			ans=t[1];
			++v;
			pop_heap(t+1,t+t[0]--+1,greater<int>());
		}
		else if(!t[0])
		{
			ans+=(d[1]-dis)*v;
			++v;
			dis=d[1];
			pop_heap(d+1,d+d[0]--+1,greater<int>());
		}
		else if((d[1]-dis)*v-(t[1]-ans)<=1e-8&&(d[1]-dis)-(t[1]-ans)*v>0)
		{
			dis+=(t[1]-ans)/v;
			ans=t[1];
			++v;
			pop_heap(t+1,t+t[0]--+1,greater<int>());
			pop_heap(d+1,d+d[0]--+1,greater<int>());
		}
		else if((d[1]-dis)*v<(t[1]-ans))
		{
			ans+=(d[1]-dis)*v;
			++v;
			dis=d[1];
			pop_heap(d+1,d+d[0]--+1,greater<int>());
		}
		else if((d[1]-dis)*v>(t[1]-ans))
		{
			dis+=(t[1]-ans)/v;
			ans=t[1];
			++v;
			pop_heap(t+1,t+t[0]--+1,greater<int>());
		}
	}
	ans+=(1000-dis)*v;
	printf("%d\n",int(ans+0.5));
}
