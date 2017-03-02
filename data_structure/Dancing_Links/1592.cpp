#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
struct DLX
{
	DLX *l,*r,*u,*d,*bottom;
	int x,y,val;
	DLX(){}
	DLX(DLX *L,DLX *R,DLX *U,DLX *D,int x,int y,int val):l(L),r(R),u(U),d(D),bottom(D),x(x),y(y),val(val)
	{
		if(L)
			L->r=this;
		if(R)
			R->l=this;
		if(U)
			U->d=this;
		if(D)
			D->u=this;
		if(bottom)
			++bottom->x;
	}
	void del();
	void recover();
	
}*head,*c[340],*stack[3500],**top=stack;
void DLX :: del()
{
	if(l)
		l->r=r;
	if(r)
		r->l=l;
	if(u)
		u->d=d;
	if(d)
		d->u=u;
	if(bottom)
		--bottom->x;
	*(++top)=this;
}
void DLX :: recover()
{
	if(l)
		l->r=this;
	if(r)
		r->l=this;
	if(u)
		u->d=this;
	if(d)
		d->u=this;
	if(bottom)
		++bottom->x;
}
void del_c(int pos)
{
	for(DLX *i=c[pos]->u;i!=c[pos];i=i->u)
	{
		for(DLX *j=i->r;j!=i;j=j->r)
			j->del();
		i->del();
	}
	c[pos]->del();
}
int ans[10][10];
void output()
{
	for(int i=1;i<=9;i++,putchar('\n'))
		for(int j=1;j<=9;j++)
			putchar(ans[i][j]+'0');
}
void dfs()
{
	if(head==head->r)
	{
		output();
		exit(0);
	}
	DLX *pro,**t=top;
	int mn=~0u>>1;
	for(DLX *i=head->r;i!=head;i=i->r)
		if(i->x<mn)
			mn=i->x,pro=i;
	for(DLX *i=pro->u;i!=pro;i=i->u)
	{
		int x=i->x,y=i->y,val=i->val;
		ans[x][y]=val;
		del_c((x-1)*9+y);
		del_c(81+(x-1)*9+val);
		del_c(162+(y-1)*9+val);
		del_c(243+((x-1)/3*3+(y-1)/3)*9+val);
		dfs();
		while(t!=top)
			(*(top--))->recover();
	}
}
void add(int x,int y,int val)
{
	DLX *it,*last=NULL;
	it=c[(x-1)*9+y];
	last=new DLX(last,NULL,it->u,it,x,y,val);
	if(!it->d)
		it->d=it->u,it->u->u=it;
	it=c[81+(x-1)*9+val];
	last=new DLX(last,NULL,it->u,it,x,y,val);
	if(!it->d)
		it->d=it->u,it->u->u=it;
	it=c[162+(y-1)*9+val];
	last=new DLX(last,NULL,it->u,it,x,y,val);
	if(!it->d)
		it->d=it->u,it->u->u=it;
	it=c[243+((x-1)/3*3+(y-1)/3)*9+val];
	last=new DLX(last,NULL,it->u,it,x,y,val);
	if(!it->d)
		it->d=it->u,it->u->u=it;
	c[243+((x-1)/3*3+(y-1)/3)*9+val]->u->r=c[(x-1)*9+y]->u;
	c[(x-1)*9+y]->u->l=c[243+((x-1)/3*3+(y-1)/3)*9+val]->u;
}

int main()
{
	head=new DLX(NULL,NULL,NULL,NULL,0,0,0);
	DLX *last=head;
	for(int i=1;i<=324;i++)
		last=new DLX(last,NULL,NULL,NULL,0,0,i),c[i]=last;
	c[324]->r=head;
	head->l=c[324];
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
		{
			scanf("%1d",&ans[i][j]);
			if(ans[i][j])
				add(i,j,ans[i][j]);
			else
				for(int k=1;k<=9;k++)
					add(i,j,k);
		}
	dfs();	
}	
