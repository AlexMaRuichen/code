#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <set>
#include <algorithm>
using namespace std;
bool v[10][10];
char s[2];
char back[10][10];
int ans;
struct Trie
{
	Trie *ch[26];
	bool flag;
	Trie()
	{
		memset(ch,0,sizeof(ch));
		flag=false;
	}
}*root,*p;
void dfs(int x,int y,Trie *p)
{
	if(v[x][y])
		return;
	if(p->flag)
		++ans,p->flag=false;
	v[x][y]=true;
	if(back[x-1][y-1]-'A'>=0&&p->ch[back[x-1][y-1]-'A'])
		dfs(x-1,y-1,p->ch[back[x-1][y-1]-'A']);
	if(back[x-1][y]-'A'>=0&&p->ch[back[x-1][y]-'A'])
		dfs(x-1,y,p->ch[back[x-1][y]-'A']);
	if(back[x-1][y+1]-'A'>=0&&p->ch[back[x-1][y+1]-'A'])
		dfs(x-1,y+1,p->ch[back[x-1][y+1]-'A']);
	if(back[x][y-1]-'A'>=0&&p->ch[back[x][y-1]-'A'])
		dfs(x,y-1,p->ch[back[x][y-1]-'A']);
	if(back[x][y+1]-'A'>=0&&p->ch[back[x][y+1]-'A'])
		dfs(x,y+1,p->ch[back[x][y+1]-'A']);
	if(back[x+1][y-1]-'A'>=0&&p->ch[back[x+1][y-1]-'A'])
		dfs(x+1,y-1,p->ch[back[x+1][y-1]-'A']);
	if(back[x+1][y]-'A'>=0&&p->ch[back[x+1][y]-'A'])
		dfs(x+1,y,p->ch[back[x+1][y]-'A']);
	if(back[x+1][y+1]-'A'>=0&&p->ch[back[x+1][y+1]-'A'])
		dfs(x+1,y+1,p->ch[back[x+1][y+1]-'A']);
	v[x][y]=false;
}
int main()
{
	fstream fs("coggle.dic", fstream::in | fstream::out);
	root=new Trie();
	for(int i=1;i<=24830;i++)
	{
		static string dic;
		fs>>dic;
		p=root;
		for(int j=0;j<dic.length();j++)
		{
			if(!p->ch[dic[j]-'A'])
				p->ch[dic[j]-'A']=new Trie();
			p=p->ch[dic[j]-'A'];
		}
		p->flag=true;
	}
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++)
		{
			scanf("%s",s);
			back[i][j]=s[0];
		}
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++)
			dfs(i,j,root->ch[back[i][j]-'A']);
	printf("%d\n",ans);
}
