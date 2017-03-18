#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
struct queue
{
	int a[maxn];
	int l,r;
	queue(){l=1;r=0;}
	void pop_front(){++l;}
	void pop_back(){--r;}
	int front(){return a[l];}
	int back(){return a[r];}
	bool empty(){return l>r;}
	void push_back(int x){a[++r]=x;}
}q;
int sum[maxn];
int n,p,Q;
int w[maxn];
int f[maxn];
int ans;
int main()
{
	scanf("%d%d%d",&n,&p,&Q);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]),sum[i]=sum[i-1]+w[i];
	for(int i=p;i<=n;i++)
	{
		while(!q.empty()&&sum[q.back()]>=sum[i-p])
			q.pop_back();
		q.push_back(i-p);
		while(q.front()<i-Q)
			q.pop_front();
		f[i]=sum[i]-sum[q.front()];
		ans=max(ans,f[i]);
	}
	printf("%d\n",ans);
}
