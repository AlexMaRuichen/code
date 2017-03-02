#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=2e3+10;
struct queue 
{
	int a[maxn];
	int l,r;
	queue(){l=1,r=0}
	int front(){return a[l];}
	int back(){return a[r];}
	void push(int x){a[++r]=x;}
	void pop_front(){++l;}
	void pop_back(){--r;}
	bool empty(){return l>r;}
}q;
int n,d,m;
int f[maxn][maxn];
int b[maxn];
int a[maxn];
int main()
{
	scanf("%d%d%d",&n,&d,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=n;i++)
	{
		while(!q.empty()&&)
		for(int j=1;j<=m;j++)
			f[i][j]=max(f[i-1][j],)
	}
}
