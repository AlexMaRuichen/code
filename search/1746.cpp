#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int ans[10][5];
int n;
struct Mayan_puzzle
{
	int map[10][10];
	Mayan_puzzle()
	{
		memset(map,0,sizeof(map));
	}
	bool check()
	{
		for(int i=1;i<=5;i++)
			for(int j=1;j<=7;j++)
				if(map[i][j])
					return false;
		return true;
	}
	void drop()
	{
		for(int i=1;i<=5;i++)
		{
			int T=0,tmp;
			for(int j=1;j<=7;j++)
			{
				tmp=map[i][j];
				map[i][j]=0;
				if(tmp)
					map[i][++T]=tmp;
			}
		}
	}
	bool remove()
	{
		bool flag;
		bool v[10][10];
		flag=false;
		for(int i=1;i<=5;i++)
			memset(v[i],0,sizeof(v[i]));
		for(int i=1;i<=5;i++)
			for(int j=1;j<=7;j++)
			{
				if(i<=3&&map[i][j]&&map[i][j]==map[i+1][j]&&map[i][j]==map[i+2][j])
					v[i][j]=v[i+1][j]=v[i+2][j]=true;
				if(j<=5&&map[i][j]&&map[i][j]==map[i][j+1]&&map[i][j]==map[i][j+2])
					v[i][j]=v[i][j+1]=v[i][j+2]=true;
			}
		for(int i=1;i<=5;i++)
			for(int j=1;j<=7;j++)
				if(v[i][j])
					map[i][j]=0,flag=true;

		return flag;
	}
	Mayan_puzzle left(int x,int y)
	{
		swap(map[x][y],map[x-1][y]);
		drop();
		while(remove())
			drop();
		return *this;
	}
	Mayan_puzzle right(int x,int y)
	{
		swap(map[x][y],map[x+1][y]);
		drop();
		while(remove())
			drop();
		return *this;
	}
	void print()
	{
		puts("***************************");
		for(int i=7;i;i--)
		{
			for(int j=1;j<=5;j++)
				printf("%d ",map[j][i]);
			puts("");
		}
		puts("***************************");
	}
}tmp;
void print()
{
	for(int i=0;i<n;i++)
		printf("%d %d %d\n",ans[i][1],ans[i][2],ans[i][3]);
}
void dfs(int dep,Mayan_puzzle p)
{
//	printf("%d\n",dep);
//	p.print();
	if(dep==n)
	{
		if(p.check())
		{
			print();
			exit(0);
		}
		return;
	}
	for(int i=1;i<5;i++)
		for(int j=1;j<=7;j++)
			if(p.map[i][j])
			{
				ans[dep][1]=i-1;
				ans[dep][2]=j-1;
				ans[dep][3]=1;
				tmp=p;
				dfs(dep+1,tmp.right(i,j));
				ans[dep][1]=0;
				ans[dep][2]=0;
				ans[dep][3]=0;
			}
	for(int i=2;i<=5;i++)
		for(int j=1;j<=7;j++)
			if(p.map[i][j]&&p.map[i][j-1]!=p.map[i][j])
			{
				ans[dep][1]=i-1;
				ans[dep][2]=j-1;
				ans[dep][3]=-1;
				tmp=p;
				dfs(dep+1,tmp.left(i,j));
				ans[dep][1]=0;
				ans[dep][2]=0;
				ans[dep][3]=0;
			}
}
int main()
{
	scanf("%d",&n);
	Mayan_puzzle p;
	for(int i=1;i<=5;i++)
	{
		for(int j=1;;j++)
		{
			scanf("%d",&p.map[i][j]);
			if(!p.map[i][j])
				break;
		}
	}
	dfs(0,p);
	puts("-1");
}
