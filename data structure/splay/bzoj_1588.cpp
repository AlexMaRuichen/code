#include <stdio.h>
#include <algorithm>
using namespace std;
const int inf=~0u>>2;
const int maxn=33000;
int fa[maxn+10];
int ch[maxn+10][2];
int root;
int k[maxn+10];
int cnt=1;
int n;
int t;
int ans;
inline void rotate(int p)
{
	int q=fa[p];
	int y=fa[q];
	int x=(ch[q][1]==p);
	ch[q][x]=ch[p][x^1];
	fa[ch[q][x]]=q;
	ch[p][x^1]=q;
	fa[q]=p;
	fa[p]=y;
	if(y)
	{
		if(ch[y][0]==q)
			ch[y][0]=p;
		else if(ch[y][1]==q)
			ch[y][1]=p;
	}
}
inline void splay(int x)
{
	for(int y;y=fa[x];rotate(x))
		if(fa[y])
			rotate((x==ch[y][0])==(y==ch[fa[y]][0])?y:x);
	root=x;
}
inline void insert(int x,int v)
{
	int y;
	while(true)
	{
		y=ch[x][k[x]<v];
		if(y==0)
		{
			y=++cnt;
			k[y]=v;
			ch[y][0]=ch[y][1]=0;
			fa[y]=x;
			ch[x][k[x]<v]=y;
            break;
		}
		x=y;
	}
	splay(y);
}
inline int pre(int x)
{
	int tmp=ch[x][0];
	while(ch[tmp][1])
		tmp=ch[tmp][1];
	return k[tmp];
}
inline int suc(int x)
{
	int tmp=ch[x][1];
	while(ch[tmp][0])
		tmp=ch[tmp][0];
	return k[tmp];
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		if(scanf("%d",&t)==-1)
			t=0;
		if(i==1)
		{
			root=1;k[root]=t;
			ch[root][0]=ch[root][1]=0;
			fa[root]=0;
			ans=t;
			insert(root,inf);
			insert(root,-inf);
   		}
   		else
   		{
   			insert(root,t);
		    int a=pre(root),b=suc(root);
		    ans+=min(t-a,b-t);
   		}
	}
	printf("%d",ans);
}
