#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
queue <int> qx,qy;
int n,m;
int x,y;
bool map[50][50];
void bfs();
bool v[100];
int ans;
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%d%d",&x,&y);
	map[x][y]=true;
	if(x+2<=n&&y+1<=m)
		map[x+2][y+1]=true;
	if(x+1<=n&&y+2<=m)
		map[x+1][y+2]=true;
	if(x-2>=0&&y+1<=m)
		map[x-2][y+1]=true;
	if(x-1>=0&&y+2<=m)
		map[x-1][y+2]=true;
	if(x+2<=n&&y-1>=0)
		map[x+2][y-1]=true;
	if(x+1<=n&&y-2>=0)
		map[x+1][y-2]=true;
	if(x-2>=0&&y-1>=0)
		map[x-2][y-1]=true;
	if(x-1>=0&&y-2>=0)
		map[x-1][y-2]=true;
	bfs();
	printf("%d\n",ans);
}
void bfs()
{
	qx.push(0);
	qy.push(0);
	while(!qx.empty()&&!qy.empty())
	{
		int tx=qx.front();
		int ty=qy.front();
		qx.pop();
		qy.pop();
		if(tx==n&&ty==m)
		{
			ans++;
			continue;
		}
		if(map[tx][ty])
			continue;
		if(tx+1<=n&&map[tx+1][ty]==false)
			qx.push(tx+1),qy.push(ty);
		if(ty+1<=m&&map[tx][ty+1]==false)
			qx.push(tx),qy.push(ty+1);
	}
}


