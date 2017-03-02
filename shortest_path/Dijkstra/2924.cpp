#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
using namespace std;

char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}

int  read()
{
    static char ch;
    static int   D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}

const int maxn=1010;
typedef long long ll;
ll map[maxn][maxn];
int dis[maxn][maxn];
int s,t,m;
int id[maxn];
int to[maxn];
int cnt;

ll f[maxn];
int d[maxn];
bool v[maxn];
void dijkstra()
{
	memset(f,0x3f,sizeof(f));
	memset(d,0x3f,sizeof(d));
	f[s]=0;
	d[s]=0;
	for(int a=1;a<cnt;a++)
	{
		int x=0;
		for(int i=1;i<=cnt;i++)
			if(!v[i]&&(f[x]>f[i]||(f[x]==f[i]&&d[x]>d[i])))
				x=i;
		v[x]=true;
		for(int i=1;i<=cnt;i++)
			if(!v[i])
			{
				if(f[i]==f[x]+map[x][i]&&d[i]>d[x]+dis[x][i])
					d[i]=d[x]+dis[x][i];
				if(f[i]>f[x]+map[x][i])
					f[i]=f[x]+map[x][i],d[i]=d[x]+dis[x][i];
			}
	}
}

int main()
{
	
	memset(map,0x3f,sizeof(map));
	memset(dis,0x3f,sizeof(dis));
	s=read();
	t=read();
	m=read();
	if(s==t)
		return puts("0 1"),0;
	s=id[s]=++cnt;
	t=id[t]=++cnt;
	for(int i=1;i<=m;i++)
	{
		static int c,l;
		c=read();
		l=read();
		for(int j=1;j<=l;j++)
		{
			to[j]=read();
			if(!id[to[j]])
				id[to[j]]=++cnt;
			to[j]=id[to[j]];
		}
		for(int j=1;j<=l;j++)
			for(int k=j+1;k<=l;k++)
			{
				if(map[to[j]][to[k]]==c)
					if(dis[to[j]][to[k]]>k-j)
						dis[to[j]][to[k]]=k-j;
				if(map[to[j]][to[k]]>c)
					map[to[j]][to[k]]=c,dis[to[j]][to[k]]=k-j;
			}
	}
	for(int i=1;i<=cnt;i++)
		map[i][i]=dis[i][i]=0;

	dijkstra();

	if(f[t]==0x3f3f3f3f3f3f3f3fll)
		puts("-1 -1");
	else
		printf("%lld %d\n",f[t],d[t]);
}
