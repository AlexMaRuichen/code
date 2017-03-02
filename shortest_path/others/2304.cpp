#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=1010;
int f[maxn][maxn];
int map[maxn][maxn];
typedef pair<int,int> point;
queue <point> q[2];
void process(int curx, int cury, int x, int y)
{
	if(x>=0&&x<=1001&&y>=0&&y<=1001&&(f[x][y]==0||f[curx][cury]+map[x][y]<f[x][y]))
	{
		f[x][y]=f[curx][cury]+map[x][y];
		if(map[x][y]==0) 
			q[0].push(point(x,y));
		else           
			q[1].push(point(x,y));
	}
}
int n,x,y;
int main()
{
	scanf("%d%d%d",&n,&x,&y);
	f[x][y]=1;
	q[0].push(point(x,y));
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		map[x][y]=1;
	}
	while(!q[0].empty()||!q[1].empty())
	{
		if(q[0].empty())
			while(!q[1].empty())
			{
				q[0].push(q[1].front());
				q[1].pop();
			}
		x=q[0].front().first;
		y=q[0].front().second;
		q[0].pop();
		process(x,y,x-1,y);
		process(x,y,x+1,y);
		process(x,y,x,y-1);
		process(x,y,x,y+1);
	}
	printf("%d\n",f[0][0]-1);
}
