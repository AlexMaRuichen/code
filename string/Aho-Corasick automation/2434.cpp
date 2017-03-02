#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
#include <vector>
#define lowbit(x) (x)&(-(x))
using namespace std;
const int maxn=1e5+10;
int n,m;
char s[maxn];
int b[maxn];
int e[maxn];
struct edge
{
	int to,id;
	edge *next;
	edge(){}
	edge(int to,int id,edge *next):to(to),id(id),next(next){}
}*head[maxn];
int ans[maxn];
void add(int x,int y,int z)
{
	head[x]=new edge(y,z,head[x]);
}

int bit[maxn];
int cnt;
int query(int x)
{
	int ans=0;
	for(;x;x-=lowbit(x))
		ans+=bit[x];
	return ans;
}
void modify(int x,int y)
{
	for(;x<=cnt;x+=lowbit(x))
		bit[x]+=y;
}
struct Trie
{
	Trie *ch[26],*fail;
	int id,pos;
	vector <Trie*> v;
	Trie(){memset(this,0,sizeof(Trie));}
	void insert()
	{
		static Trie* stack[maxn];
		static int top=0,cnt=0;
		stack[++top]=this;
		for(int i=1;s[i];i++)
			if(s[i]=='P')
				stack[top]->id=++cnt;
			else if(s[i]=='B')
				top--;
			else 
			{
				if(!stack[top]->ch[s[i]-'a'])
					stack[top]->ch[s[i]-'a']=new Trie();
				stack[top+1]=stack[top]->ch[s[i]-'a'];
				++top;
			}
	}
	void build()
	{
		queue <Trie*> q;
		for(int i=0;i<26;i++)
			if(ch[i])
				ch[i]->fail=this,q.push(ch[i]),v.push_back(ch[i]);
			else
				ch[i]=this;
		while(!q.empty())
		{
			Trie *x=q.front();
			q.pop();
			for(int i=0;i<26;i++)
				if(x->ch[i])
				{
					x->ch[i]->fail=x->fail->ch[i];
					x->fail->ch[i]->v.push_back(x->ch[i]);
					q.push(x->ch[i]);
				}
				else
					x->ch[i]=x->fail->ch[i];
		}
	}
	void dfs()
	{
		pos=++cnt;
		if(id)
			b[id]=cnt;
		for(vector <Trie*> :: iterator it=v.begin();it!=v.end();it++)
			(*it)->dfs();
		if(id)
			e[id]=cnt;
	}
	void solve()
	{
		static Trie* stack[maxn];
		static int top=0;
		stack[++top]=this;
		for(int i=1;s[i];i++)
		{
			if(s[i]=='B')
				modify(stack[top]->pos,-1),
				stack[top--]=NULL;
			else if(s[i]=='P')
				for(edge *p=head[stack[top]->id];p;p=p->next)
					ans[p->id]=query(e[p->to])-query(b[p->to]-1);
			else
				stack[top+1]=stack[top]->ch[s[i]-'a'],
				modify(stack[++top]->pos,1);
		}
	}
}*root=new Trie();
int main()
{
	scanf("%s",s+1);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(y,x,i);
	}
	root->insert();
	root->build();
	root->dfs();
	root->solve();
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
}
