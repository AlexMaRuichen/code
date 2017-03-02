#include <stdio.h>
#include <algorithm>
#include <iostream>
#define lowbit(x) (x)&(-x)
using namespace std;
const int maxn=10010;
const int N=1e9;
struct chairtree
{
	chairtree *ls,*rs;
	int cnt;
	void* operator new(size_t);
}*root[maxn],mempool[2002002];
void* chairtree :: operator new(size_t)
{
	static chairtree *p=mempool;
	return p++;
}
void insert(chairtree *&x,int v,int l,int r)
{
	if(!x)
		x=new chairtree();
	++x->cnt;
	if(l==r)
		return;
	int mid=l+r>>1;
	if(mid>=v)
		insert(x->ls,v,l,mid);
	else
		insert(x->rs,v,mid+1,r);
}
void del(chairtree *x,int v,int l,int r)
{
	--x->cnt;
	if(l==r)
		return;
	int mid=l+r>>1;
	if(mid>=v)
		del(x->ls,v,l,mid);
	else
		del(x->rs,v,mid+1,r);
}
int query(chairtree *x,int p,int L,int R)
{
	if(!x)
		return 0;
	if(!x->cnt)
		return 0;
	if(L==R)
		return x->cnt;
	int mid=L+R>>1;
	if(mid>=p)
		return query(x->ls,p,L,mid);
	else
		return (x->ls?x->ls->cnt:0)+query(x->rs,p,mid+1,R);
}
int n,m;
int a[maxn];
void MODIFY(int x,int y)
{
	for(int i=x;i<=n;i+=lowbit(i))
		del(root[i],a[x],0,N),insert(root[i],y,0,N);
	a[x]=y;
}
int QUERY(int x,int y)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans+=query(root[i],y,0,N);
	return ans;
}
void INSERT(int x,int y)
{
	for(int i=x;i<=n;i+=lowbit(i))
		insert(root[i],y,0,N);
}
int bio(int l,int r,int k)
{
	int L=0,R=N+10,mid;
	while(L<R-1)
	{
		mid=L+R>>1;
		if(QUERY(r,mid)-QUERY(l-1,mid)>=k)
			R=mid;
		else
			L=mid;
	}
    if(QUERY(r,L)-QUERY(l-1,L)>=k)
        return L;
    return R;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),INSERT(i,a[i]);;		
	for(int i=1;i<=m;i++)
	{
		static char s[10];
		static int x,y,z;
		scanf("%s",s);
		if(s[0]=='Q')
			scanf("%d%d%d",&x,&y,&z),printf("%d\n",bio(x,y,z));
		else if(s[0]=='C')
			scanf("%d%d",&x,&y),MODIFY(x,y);
	}
}
