#include <stdio.h>
#include <algorithm>
using namespace std;
int n,m;
const int maxn=20010;
struct sequence
{
	int lmx,rmx,sum;
	sequence(int x=0)  
    {  
        lmx=rmx=max(x,0);  
        sum=x;  
    }  
};
inline sequence operator + (const sequence &x,const sequence &y)
{
	sequence z;
	z.sum=x.sum+y.sum;
	z.lmx=max(x.lmx,x.sum+y.lmx);
	z.rmx=max(y.rmx,y.sum+x.rmx);
	return z;
} 
struct seg_tree
{
	seg_tree *ls,*rs;
	sequence s;
}*root[maxn],mempool[maxn*20];
inline seg_tree* new_node(seg_tree *x,seg_tree *y,const sequence &z)
{
	static seg_tree *p=mempool;
	p->ls=x;
	p->rs=y;
	p->s=z;
	return p++;
}
inline seg_tree* build(int l,int r)
{
	if(l==r)
		return new_node(NULL,NULL,sequence(1));
	int mid=l+r>>1;
	seg_tree *ls=build(l,mid);
	seg_tree *rs=build(mid+1,r);
	return new_node(ls,rs,ls->s+rs->s);
}
inline seg_tree* modify(seg_tree *x,int p,int l,int r)
{
	if(l==r)
		return new_node(NULL,NULL,sequence(-1));
	int mid=l+r>>1;
	if(mid>=p)
	{
		seg_tree *ls=modify(x->ls,p,l,mid);
		return new_node(ls,x->rs,ls->s+x->rs->s);
	}
	else
	{
		seg_tree *rs=modify(x->rs,p,mid+1,r);
		return new_node(x->ls,rs,x->ls->s+rs->s);
	}
}
inline sequence query(seg_tree *x,int l,int r,int L,int R)
{
	if(l==L&&r==R)
		return x->s;
	int mid=L+R>>1;
	if(mid>=r)
		return query(x->ls,l,r,L,mid);
	else if(mid<l)
		return query(x->rs,l,r,mid+1,R);
	else
		return query(x->ls,l,mid,L,mid)+query(x->rs,mid+1,r,mid+1,R);
}
inline int check(int a,int b,int c,int d,int x)
{
	int ans=0;
	ans+=query(root[x],b,c,1,n).sum;
	ans+=query(root[x],a,b-1,1,n).rmx;
	ans+=query(root[x],c+1,d,1,n).lmx;
	return ans>=0;
}
pair <int,int> p[maxn];

int main()
{
	scanf("%d",&n);
	root[1]=build(1,n);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i].first),p[i].second=i;
	sort(p+1,p+n+1);
	for(int i=2;i<=n;i++)
		root[i]=modify(root[i-1],p[i-1].second,1,n);
	scanf("%d",&m);
	while(m--)
	{
		static int q[4],l,r,mid,lastans;
		for(int i=0;i<4;i++)
			scanf("%d",&q[i]),q[i]=(q[i]+lastans)%n+1;
		sort(q,q+4);
		l=1,r=n+1;
		while(l+1<r)
		{
			mid=l+r>>1;
			if(check(q[0],q[1],q[2],q[3],mid))
				l=mid;
			else
				r=mid;
		}
		printf("%d\n",lastans=p[l].first);
	}
}
