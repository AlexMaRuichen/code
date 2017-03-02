#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=5010;
int n,k;
struct atable
{
	int to,next,len;
}t[2*maxn];
int head[maxn],tot;
void add(int x,int y,int z)
{
	t[++tot].to=y;
	t[tot].len=z;
	t[tot].next=head[x];
	head[x]=tot;
}
int main()
{
	scanf("%d%d",&n,&k);
}
