#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
int p(int x,int y)
{
    int c=y-x;
    if(c<0)
        c+=3;
    return c;
}
int recursion(int x,int y,int a,int b,int c)
{
	if(x<=0||y<=0)
		return 0;
	if(x==y)
		return c;
	else if(x>y)
		return recursion(y,x-y,b,c,a)+p(a,c);
	else 
		return recursion(x,y-x,a,c,b)+p(b,c);
}
int n,m;
queue <int> q[4];
int ans;
int main()
{
	while(scanf("%d%d",&n,&m)==2&&n!=-1&&m!=-1)
	{
		ans=0;
		int g=n%3;
		int x,y;
		if(g==0)
            x=1,y=2,g=3;
        else if(g==2)
            x=1,y=3;
        else 
        	x=2,y=3;
		for(int i=1;i<m;i++)
			if(recursion(i,m-i,x,y,g)==n)
				ans++,q[x].push(i),q[y].push(m-i),q[g].push(m);		
		printf("%d\n",ans);
		for(int i=1;i<=ans;i++)
		{
			printf("%d %d %d\n",q[1].front(),q[2].front(),q[3].front());
			q[1].pop();
			q[2].pop();
			q[3].pop();
		}
	}
}
