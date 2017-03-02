#include <string>
#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;
const int maxn=1000010;
int w,n;
string s;
string in[1000010];
char p[1000010];
map <string,int> m;
int main()
{
   scanf("%d%d",&w,&n);
   for(int i=1;i<=w;i++)
   {
	   scanf("%s",p);
	   in[i]=p;
	   m[in[i]]=i;
   }
   sort(in+1,in+w+1);
   for(int i=1;i<=n;i++)
   {
	   static int x,pos;
	   scanf("%d%s",&x,p);
	   s=p;
	   pos=lower_bound(in+1,in+w+1,s)-in;
	   pos+=x-1;
	   if(pos>w||in[pos].substr(0,s.size())!=s)
		  puts("-1");
	   else
		  printf("%d\n",m[in[pos]]);
   }
}
