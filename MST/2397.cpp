#include <stdio.h>
#include <cmath>
#include <queue>

#define MAX 501

using namespace std;

const int dy[]={-1,0,1,0},dx[]={0,-1,0,1};
int m,n,mat[MAX][MAX],wp[MAX][MAX],mark[MAX][MAX],wy,wx;

// floodfill with BFS within elevation difference d
void floodfill(int d)
{
	queue<pair<int,int> > q;

	q.push(make_pair(wy,wx));
	mark[wy][wx]=1;

	while (!q.empty())
	{
		pair<int,int> p=q.front();
		q.pop();

		for (int i=0; i<4; i++)
		{
			int ny=p.first+dy[i],nx=p.second+dx[i];
			if (ny>=0 && ny<m && nx>=0 && nx<n)
				// if the target cell is not visited before
				//    and the elevation difference is within D
				//    push the cell into the queue
				if (!mark[ny][nx] && abs(mat[p.first][p.second]-mat[ny][nx])<=d)
				{
					q.push(make_pair(ny,nx));
					mark[ny][nx]=1;
				}
		}
	}
}

// check if all waypoints are reachable with elevation difference D
bool reachable(int d)
{
	// reset the grid that keeps the reachable points
	for (int i=0; i<m; i++)
		for (int j=0; j<n; j++) mark[i][j]=0;

	floodfill(d);

	// check if there is any unreachable waypoints
	for (int i=0; i<m; i++)
		for (int j=0; j<n; j++)
			if (wp[i][j] && !mark[i][j]) return false;
	return true;
}

int main()
{

	scanf("%d%d",&m,&n);
	for (int i=0; i<m; i++)
		for (int j=0; j<n; j++)
			scanf("%d",&mat[i][j]);
	for (int i=0; i<m; i++)
		for (int j=0; j<n; j++)
		{
			scanf("%d",&wp[i][j]);
			// keep one of the waypoints as the starting point
			if (wp[i][j]) wy=i,wx=j;
		}

	// binary search
	int dmin=0,dmax=1000000000;
	while (dmin<dmax)
	{
		int d=(dmin+dmax)/2;
		if (reachable(d)) dmax=d;
		else dmin=d+1;
	}

	printf("%d\n",dmin) ;
}
