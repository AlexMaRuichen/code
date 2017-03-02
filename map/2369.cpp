#include <stdio.h>
#include <algorithm>
#include <queue>
#define DIR(e) (mark[e.y][e.x]%2?1:-1)
using namespace std;
struct point
{
	int y,x;
	point(){}
	point(int _y,int _x):y(_y),x(_x){}
};
queue <point> q;
const int maxn=510;
char map[maxn][maxn];
int mark[maxn][maxn];
int n,m;
point c,d;
point gravity_change(point p,int dir)
{
	for(;;p.y+=dir)
	{
		if(map[p.y][p.x]=='D')
			break;
		if(p.y+dir<1||p.y+dir>n)
			return point(-1,-1);
		if(map[p.y+dir][p.x]=='#')
			break;
	}
	return p;
}
point move(point p,int k,int dir)
{
	if(k)
	{
		p.x+=k;
		if(p.x<1||p.x>m||map[p.y][p.x]=='#')
			return point(-1,-1);
	}
	else
		dir=-dir;
	return gravity_change(p,dir);
}
bool dfs(point p,int flip)
{
	if(p.y==-1||mark[p.y][p.x])
		return false;
	mark[p.y][p.x]=flip;
	if(p.y==d.y&&p.x==d.x)
		return true;
	q.push(p);
	int dir=DIR(p);
	return dfs(move(p,-1,dir),flip)||dfs(move(p,1,dir),flip);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",map[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(map[i][j]=='C')
				c=gravity_change(point(i,j),1);
			else if(map[i][j]=='D')
				d=point(i,j);
	if(!dfs(c,1))
		while(!q.empty())
		{
			point p=q.front();
			q.pop();
			point g=move(p,0,DIR(p));
			if(dfs(g,mark[p.y][p.x]+1))
				break;
		}
	printf("%d\n",mark[d.y][d.x]-1);
}
