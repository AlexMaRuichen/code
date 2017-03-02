#include <stdio.h>
#include <string.h>
#include <algorithm>
#define in(i) (i<<1)
#define out(i) (i<<1|1)
#define inv(i) (i&1?i^1:i|1)
using namespace std;
const int maxn=2010;
const int maxm=8010;
int n,m;

int to[maxm];
int next[maxm];
int head[maxn];
int tot;
void add(int x,int y)
{
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
}

bool col[maxn];
int fin[maxn];
void dye(int x)
{
	col[x]=true;
	for(int i=head[x];i;i=next[i])
		if(!col[to[i]])
			dye(to[i]);
}
bool check(int x)
{
	memset(col,0,sizeof(col));
	dye(x);
	for(int i=1;i<=n;i++)
		if(col[in(i)]&&col[out(i)])
			return false;
	return true;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		static char a[5],b[5];
		scanf("%d%s%d%s",&x,a,&y,b);
		x=a[0]=='Y'?in(x):out(x);
		y=b[0]=='Y'?in(y):out(y);
		add(inv(x),y);
		add(inv(y),x);
	}
	for(int i=1;i<=n;i++)
	{
		static bool x,y;
		x=check(in(i));
		y=check(out(i));
		if(!x&&!y)
			return puts("IMPOSSIBLE"),0;
		else if(!(x&&y))
			fin[i]+=x?1:2;
	}
	for(int i=1;i<=n;i++)
	{
		static char s[10]="?YN";
		printf("%c",s[fin[i]]);
	}
	puts("");
}
