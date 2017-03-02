#include <stdio.h>
#include <algorithm>
#define inv(x) (x&1?x+1:x-1)
using namespace std;
const int maxn=8010<<1;
const int maxm=20010<<1;
int n,m;
char ch;
#define read(x) ch=getchar(); \
	x=0; \
	while(ch<'0'||ch>'9') \
		ch=getchar(); \
	while(ch>='0'&&ch<='9') \
		x=(x<<1)+(x<<3)+ch-'0',ch=getchar();

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

int color[maxn];
int s[maxn];
bool dfs(int x)
{
	if(color[x]==1)
		return true;
	else if(color[x]==2)
		return false;
	color[x]=1;
	color[inv(x)]=2;
	s[++s[0]]=x;
	for(int i=head[x];i;i=next[i])
		if(!dfs(to[i]))
			return false;
	return true;
}
bool two_sat()
{
	for(int i=n;i;i--)
	{
		if(color[i])
			continue;
		s[0]=0;
		if(!dfs(i))
		{
			for(int j=1;j<=s[0];j++)
				color[s[j]]=color[inv(s[j])]=0;
			if(!dfs(inv(i)))
				return false;
		}
	}
	return true;
}
int main()
{
	read(n);
	read(m);
	n<<=1;
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		read(x);
		read(y);
		add(x,inv(y));
		add(y,inv(x));
	}
	if(!two_sat())
		return puts("NIE"),0;
	else
		for(int i=n;i;i--)
			if(color[i]==1)
				printf("%d\n",i);
}
