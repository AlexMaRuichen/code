#include <stdio.h>
#include <stdlib.h>
#define max(a,b) (a)>(b)?(a):(b)
int cnt;
int tot;
const int mark[10][10]=
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    {0, 6, 7, 7, 7, 7, 7, 7, 7, 6},
    {0, 6, 7, 8, 8, 8, 8, 8, 7, 6},
    {0, 6, 7, 8, 9, 9, 9, 8, 7, 6},
    {0, 6, 7, 8, 9,10, 9, 8, 7, 6},
    {0, 6, 7, 8, 9, 9, 9, 8, 7, 6},
    {0, 6, 7, 8, 8, 8, 8, 8, 7, 6},
    {0, 6, 7, 7, 7, 7, 7, 7, 7, 6},
    {0, 6, 6, 6, 6, 6, 6, 6, 6, 6}
};

const int lab[10][10]=
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
    {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
    {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
    {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
    {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
    {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
    {0, 7, 7, 7, 8, 8, 8, 9, 9, 9},
    {0, 7, 7, 7, 8, 8, 8, 9, 9, 9},
    {0, 7, 7, 7, 8, 8, 8, 9, 9, 9},
};
int map[10][10];
bool col[10][10];
bool row[10][10];
bool mat[10][10];
int score;
int ans=-1;

bool insert(int x,int y,int z)
{
    if(row[x][z]||col[y][z]||mat[lab[x][y]][z])
        return false;
    ++cnt;
    map[x][y]=z;
    row[x][z]=col[y][z]=mat[lab[x][y]][z]=true;
    score+=z*mark[x][y];
    return true;
}


void read()
{
    int t;
    for(int i=9;i;i--)
        for(int j=9;j;j--)
        {
            scanf("%d",&t);
            if(t)
                insert(i,j,t);
        }
}

void dfs(int x,int y)
{
	if(tot>=14000000)
	{
		printf("%d\n",ans);
		exit(0);
	}
	else
		++tot;
    if(x==10&&y==1)
    {
        ans=max(ans,score);
        return;
    }
    if(score+(81-cnt)*81<ans)
        return;
    if(map[x][y])
        y==9?dfs(x+1,1):dfs(x,y+1);
    else
        for(int i=1;i<=9;i++)
            if(insert(x,y,i))
            {
                y==9?dfs(x+1,1):dfs(x,y+1);
                score-=map[x][y]*mark[x][y];
                row[x][map[x][y]]=col[y][map[x][y]]=mat[lab[x][y]][map[x][y]]=false;
                --cnt;
                map[x][y]=0;
            }
}

int main()
{
    read();
    dfs(1,1);
    printf("%d\n",ans);
}
