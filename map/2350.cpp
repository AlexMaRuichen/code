#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
map <int,map<int,int> > m;
int n;
int sx,sy;
int x,y;
int dx[]={};
int dy[]={};
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		m[x][y]=1;
		if(x<sx||(x==sx&&y>sy))
			sx=x,y=sy;
	}
	x=sx,y=sy;
}
