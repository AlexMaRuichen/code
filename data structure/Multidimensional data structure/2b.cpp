#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#define update(x) size[x]=size[s[x][0]]+size[s[x][1]]+cnt[x]
using namespace std;
const int inf=100000001;
const int maxn=262145;
const int maxm=2000000;
int n,m,ans,idx;
int a[50001],root[maxn];
int s[maxm][2],cnt[maxm],size[maxm],val[maxm],key[maxm];
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
int read()
{
	static char ch;
	static int D,F;
	F=1;
	while(!isdigit(ch=getc()))if(ch=='-')F=-1;
	for(D=ch-'0'; isdigit(ch=getc());)
		D=(D<<3)+(D<<1)+(ch-'0');
	return D*F;
}
void ltrans(int &x)
{
	int t=s[x][0];
	s[x][0]=s[t][1];
	s[t][1]=x;
	size[t]=size[x];
	update(x);
	x=t;
	return ;
}
void rtrans(int &x)
{
	int t=s[x][1];
	s[x][1]=s[t][0];
	s[t][0]=x;
	size[t]=size[x];
	update(x);
	x=t;
	return ;
}
void insert(int &k,int x)
{
	if(!k)
	{
		k=++idx;
		size[k]=cnt[k]=1;
		val[k]=x;
		key[k]=rand();
		return ;
	}
	++size[k];
	if(val[k]==x)
		++cnt[k];
	else if(val[k]>x)
	{
		insert(s[k][0],x);
		if(key[s[k][0]]<key[k])
			ltrans(k);
	}
	else
	{
		insert(s[k][1],x);
		if(key[s[k][1]]<key[k])
			rtrans(k);
	}
	return ;
}
void del(int &k,int x)
{
	if(val[k]==x)
	{
		if(cnt[k]>1)
		{
			--cnt[k];
			--size[k];
			return ;
		}
		if(s[k][0]*s[k][1]==0)
			k=s[k][0]+s[k][1];
		else if(key[s[k][0]]<key[s[k][1]])
			ltrans(k),del(k,x);
		else
			rtrans(k),del(k,x);
	}
	else if(val[k]>x)
		--size[k],del(s[k][0],x);
	else
		--size[k],del(s[k][1],x);
}
void build(int l,int r,int x,int y,int now)
{
	insert(root[now],y);
	if(l==r-1)
		return ;
	int mid=l+((r-l)>>1);
	int ls=(now<<1),rs=(now<<1|1);
	if(x<mid)
		build(l,mid,x,y,ls);
	else
		build(mid,r,x,y,rs);
	return ;
}
void modify(int l,int r,int x,int y,int z,int now)
{
	del(root[now],y);
	insert(root[now],z);
	if(l==r-1)
		return ;
	int mid=l+((r-l)>>1);
	int ls=(now<<1),rs=(now<<1|1);
	if(x<mid)
		modify(l,mid,x,y,z,ls);
	else
		modify(mid,r,x,y,z,rs);
	return ;
}
void change(int pos,int x)
{
	modify(1,n+1,pos,a[pos],x,1);
	a[pos]=x;
	return ;
}
void get_rank(int k,int x)
{
	while(k)
	{
		if(val[k]==x)
			{ans+=size[s[k][0]];break;}
		else if(val[k]<x)
			ans+=size[s[k][0]]+cnt[k],
			k=s[k][1];
		else
			k=s[k][0];
	}
	return ;
}
void ask_rank(int l,int r,int x,int y,int z,int now)
{
	if(l==x&&r==y)
	{
		get_rank(root[now],z);
		return ;
	}
	int mid=l+((r-l)>>1);
	int ls=(now<<1),rs=(now<<1|1);
	if(x>=mid)
		{ask_rank(mid,r,x,y,z,rs);return ;}
	if(y<=mid)
		{ask_rank(l,mid,x,y,z,ls);return ;}
	ask_rank(l,mid,x,mid,z,ls);
	ask_rank(mid,r,mid,y,z,rs);
	return ;
}
void ask_num(int l,int r,int x)
{
	int L=-1,R=inf,mid;
	while(L<R-1)
	{
		mid=L+((R-L)>>1);
		ans=1;ask_rank(1,n+1,l,r,mid,1);
		if(ans<=x)
			L=mid;
		else
			R=mid;
	}
	printf("%d\n",L);
	return ;
}
void get_before(int k,int x)
{
	while(k)
	{
		if(val[k]>=x)
			k=s[k][0];
		else
			ans=max(ans,val[k]),
			k=s[k][1];
	}
	return ;
}
void ask_before(int l,int r,int x,int y,int z,int now)
{
	if(l==x&&r==y)
	{
		get_before(root[now],z);
		return ;
	}
	int mid=l+((r-l)>>1);
	int ls=(now<<1),rs=(now<<1|1);
	if(x>=mid)
		{ask_before(mid,r,x,y,z,rs);return ;}
	if(y<=mid)
		{ask_before(l,mid,x,y,z,ls);return ;}
	ask_before(l,mid,x,mid,z,ls);
	ask_before(mid,r,mid,y,z,rs);
	return ;
}
void get_after(int k,int x)
{
	while(k)
	{
		if(val[k]<=x)
			k=s[k][1];
		else
			ans=min(ans,val[k]),
			k=s[k][0];
	}
	return ;
}
void ask_after(int l,int r,int x,int y,int z,int now)
{
	if(l==x&&r==y)
	{
		get_after(root[now],z);
		return ;
	}
	int mid=l+((r-l)>>1);
	int ls=(now<<1),rs=(now<<1|1);
	if(x>=mid)
		{ask_after(mid,r,x,y,z,rs);return ;}
	if(y<=mid)
		{ask_after(l,mid,x,y,z,ls);return ;}
	ask_after(l,mid,x,mid,z,ls);
	ask_after(mid,r,mid,y,z,rs);
	return ;
}
int main()
{
	srand(20150226);rand();
	n=read();m=read();
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
		build(1,n+1,i,a[i],1);
	}
	int opt,x,y,z;
	for(int i=1;i<=m;++i)
	{
		opt=read();x=read();y=read();
		if(opt==1)
		{
			z=read();
			ans=1;
			ask_rank(1,n+1,x,y+1,z,1);
			printf("%d\n",ans);
		}
		else if(opt==2)
		{
			z=read();
			ask_num(x,y+1,z);
		}
		else if(opt==3)
			change(x,y);
		else if(opt==4)
		{
			z=read();
			ans=0;
			ask_before(1,n+1,x,y+1,z,1);
			printf("%d\n",ans);
		}
		else
		{
			z=read();
			ans=inf;
			ask_after(1,n+1,x,y+1,z,1);
			printf("%d\n",ans);
		}
	}
	return 0;
}
