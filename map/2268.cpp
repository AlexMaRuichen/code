#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
queue <int> qx,qy,tx,ty;
int map[60][60];
bool v[60][60];
int g[60][60];
char s[60];
int n,m;
int tot=1;
bool c[5];
int f=~0u>>1;
int ans=~0u>>1;
int k;
int cnt=0;
int tmp;
int get[5][5];
void bfs_spot()
{
	int x,y;
	while(!qx.empty())
	{
		x=qx.front();
		y=qy.front();
		qx.pop();
		qy.pop();
		map[x][y]=tot;
		if(map[x-1][y]==-1&&!v[x-1][y])
		{
			v[x-1][y]=true;
			qx.push(x-1),qy.push(y);
		}
		if(map[x+1][y]==-1&&!v[x+1][y])
		{
			v[x+1][y]=true;
			qx.push(x+1),qy.push(y);
		}
		if(map[x][y-1]==-1&&!v[x][y-1])
		{
			v[x][y-1]=true;
			qx.push(x),qy.push(y-1);
		}
		if(map[x][y+1]==-1&&!v[x][y+1])
		{
			v[x][y+1]=true;
			qx.push(x),qy.push(y+1);
		}
	}
	++tot;
}
int main()
{
	memset(get,0x3f,sizeof(get));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		for(int j=0;j<m;j++)
			if(s[j]=='X')
				map[i][j+1]=-1;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(map[i][j]==-1)
			{
				qx.push(i);
				qy.push(j);
				v[i][j]=true;
				bfs_spot();
			}
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=m;j++)
//			printf("%d ",map[i][j]);
//		puts("");
//	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(map[i][j]==0)
			{
				int tmp1=~0u>>1;
				int tmp2=~0u>>1;
				int tmp3=~0u>>1;
				for(int k=1;k<=n;k++)
					for(int l=1;l<=m;l++)
						if(map[k][l]==1)
							tmp1=min(tmp1,(abs(k-i)+abs(l-j))-1);
						else if(map[k][l]==2)
							tmp2=min(tmp2,(abs(k-i)+abs(l-j))-1);
						else if(map[k][l]==3)
							tmp3=min(tmp3,(abs(k-i)+abs(l-j))-1);
				ans=min(ans,tmp1+tmp2+tmp3+1);
			}
	for(int t=1;t<=3;t++)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(map[i][j]==t)
				{
					int x=~0u>>1;
					int y=~0u>>1;
					for(int k=1;k<=n;k++)
						for(int l=1;l<=m;l++)
							if(map[k][l]&&map[k][l]!=t)
								get[map[i][j]][map[k][l]]=get[map[k][l]][map[i][j]]=min(get[map[i][j]][map[k][l]],(abs(k-i)+abs(l-j))-1);
				}
	}
	printf("%d\n",min(ans,min(get[1][2]+get[2][3],min(get[1][3]+get[2][3],get[1][2]+get[1][3]))));
}	
