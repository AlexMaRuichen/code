#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
struct data{
	int l,r,v,size,rnd,w;
}tr[100005];
int n,size,root,ans;
void update(int k)//更新结点信息
{
	tr[k].size=tr[tr[k].l].size+tr[tr[k].r].size+tr[k].w;
}
void rturn(int &k)
{
	int t=tr[k].l;tr[k].l=tr[t].r;tr[t].r=k;
	tr[t].size=tr[k].size;update(k);k=t;
}
void lturn(int &k)
{
	int t=tr[k].r;tr[k].r=tr[t].l;tr[t].l=k;
	tr[t].size=tr[k].size;update(k);k=t;
}
void insert(int &k,int x)
{
	if(k==0)
	{
		size++;k=size;
		tr[k].size=tr[k].w=1;tr[k].v=x;tr[k].rnd=rand();
		return;
	}
	tr[k].size++;
    if(tr[k].v==x)tr[k].w++;//每个结点顺便记录下与该节点相同值的数的个数
	else if(x>tr[k].v)
	{
		insert(tr[k].r,x);
		if(tr[tr[k].r].rnd<tr[k].rnd)lturn(k);//维护堆性质
	}
	else 
	{
		insert(tr[k].l,x);
		if(tr[tr[k].l].rnd<tr[k].rnd)rturn(k);
	} 
}
void del(int &k,int x)
{
    if(k==0)return; 
	if(tr[k].v==x)
	{
		if(tr[k].w>1)
		{
			tr[k].w--;tr[k].size--;return;//若不止相同值的个数有多个，删去一个
		}
		if(tr[k].l*tr[k].r==0)k=tr[k].l+tr[k].r;//有一个儿子为空
		else if(tr[tr[k].l].rnd<tr[tr[k].r].rnd)
			rturn(k),del(k,x);
		else lturn(k),del(k,x);
	}
	else if(x>tr[k].v)
		tr[k].size--,del(tr[k].r,x);
	else tr[k].size--,del(tr[k].l,x);
}
int query_rank(int k,int x)
{
    if(k==0)return 0;
	if(tr[k].v==x)return tr[tr[k].l].size+1;
	else if(x>tr[k].v)
		return tr[tr[k].l].size+tr[k].w+query_rank(tr[k].r,x);
	else return query_rank(tr[k].l,x);
}
int query_num(int k,int x)
{
    if(k==0)return 0;
	if(x<=tr[tr[k].l].size)
		return query_num(tr[k].l,x);
    else if(x>tr[tr[k].l].size+tr[k].w)
		return query_num(tr[k].r,x-tr[tr[k].l].size-tr[k].w);
    else return tr[k].v;
}
void query_pro(int k,int x)
{
    if(k==0)return;
    if(tr[k].v<x)
	{
		ans=k;query_pro(tr[k].r,x);
	}
    else query_pro(tr[k].l,x);
}
void query_sub(int k,int x)
{
	if(k==0)return;
	if(tr[k].v>x)
	{
		ans=k;query_sub(tr[k].l,x);
	}
	else query_sub(tr[k].r,x);
}
int main()
{
	scanf("%d",&n);
	int opt,x;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&opt,&x);
		switch(opt)
		{
		case 1:insert(root,x);break;
		case 2:del(root,x);break;
		case 3:printf("%d\n",query_rank(root,x));break;
		case 4:printf("%d\n",query_num(root,x));break;
		case 5:ans=0;query_pro(root,x);printf("%d\n",tr[ans].v);break;
		case 6:ans=0;query_sub(root,x);printf("%d\n",tr[ans].v);break;
		}
	}
	return 0;
}
