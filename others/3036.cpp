#include <stdio.h>
#include <bitset>
using namespace std;
const int maxn=2048;
class BuildGates
{
	bitset <maxn> vis[maxn],up[maxn],right[maxn];
	int n,x,y,ans;
	char ch[maxn];
public:
	int solve()
	{
		scanf("%d",&n);
		scanf("%s",ch+1);
		x=y=1024;
		for(int i=1;i<=n;i++)
		{
			vis[x][y]=1;
			if(ch[i]=='N')
			{
				++y;
				if(!up[x][y-1]&&vis[x][y])
					++ans;
				up[x][y-1]=1;
			}
			if(ch[i]=='S')
			{
				--y;
				if(!up[x][y]&&vis[x][y])
					++ans;
				up[x][y]=1;
			}
			if(ch[i]=='W')
			{
				--x;
				if(!right[x][y]&&vis[x][y])
					++ans;
				right[x][y]=1;
			}
			if(ch[i]=='E')
			{
				++x;
				if(!right[x-1][y]&&vis[x][y])
					++ans;
				right[x-1][y]=1;
			}
		}
		return ans;
	}
}cls;
int main()
{
	printf("%d\n",cls.solve());
}
