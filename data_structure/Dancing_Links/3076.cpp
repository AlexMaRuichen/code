#include <stdio.h>
#include <algorithm>
using namespace std;
struct DLX
{
	DLX *l,*r,*u,*d,*bottom;
	int x,y;
	char val;
	DLX(){}
	DLX(DLX *L,DLX *R,DLX *U,DLX *D,int x,int y,char val):l(L),r(R),u(U),d(D),bottom(D),x(x),y(y),val(val)
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
}*head,*c[16*16*4+10],*stack[16*16*4*20+10];
int top;
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
	stack[++top]=this;
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
	for(DLX *it1=c[pos]->u;it1;it1=it1->u)
	{
		for(DLX *it2=it1->l;it2;it2=it2->l)
			it2->del();
		for(DLX *it2=it1->r;it2;it2=it2->r)
			it2->del();
		it1->del();
	}
	c[pos]->del();
}
char ans[20][20];
void output()
{
	for(int i=1;i<=16;i++,puts(""))
		for(int j=1;j<=16;j++)
			putchar(ans[i][j]);
}
bool flag;
void dfs()
{
	if(!head->r)
	{
		output();
		flag=true;
		return;
	}
	int t=top,mn=~0u>>1;
	DLX *pro;
	for(DLX *it=head->r;it;it=it->r)
		if(it->x<mn)
			mn=it->x,pro=it;
	for(DLX *it=pro->u;it;it=it->u)
	{
		int x=it->x,y=it->y,val=it->val-'A'+1;
		ans[x][y]=it->val;
		del_c((x-1)*16+y);
		del_c(256+(x-1)*16+val);
		del_c(512+(y-1)*16+val);
		del_c(768+((x-1)/4*4+(y-1)/4)*16+val);
		dfs();
		if(flag)
			return;
		while(top^t)
			stack[top--]->recover();
	}
}
void add(int x,int y,char val)
{
	DLX *it,*last=NULL;
	it=c[(x-1)*16+y];
	last=new DLX(last,NULL,it->u,it,x,y,val);
	it=c[256+(x-1)*16+val-'A'+1];
	last=new DLX(last,NULL,it->u,it,x,y,val);
	it=c[512+(y-1)*16+val-'A'+1];
	last=new DLX(last,NULL,it->u,it,x,y,val);
	it=c[768+((x-1)/4*4+(y-1)/4)*16+val-'A'+1];
	last=new DLX(last,NULL,it->u,it,x,y,val);
}
int main()
{
	while(~scanf("%s",ans[1]+1))
	{
		flag=false;
		top=0;
		for(int i=2;i<=16;i++)
			scanf("%s",ans[i]+1);
		head=new DLX(NULL,NULL,NULL,NULL,0,0,0);
		DLX *last=head;
		for(int i=1;i<=256*4;i++)
			last=new DLX(last,NULL,NULL,NULL,0,0,i),c[i]=last;
		for(int i=1;i<=16;i++)
			for(int j=1;j<=16;j++)
			{
				if(ans[i][j]=='-')
					for(int k=1;k<=16;k++)
						add(i,j,'A'+k-1);
				else
					add(i,j,ans[i][j]);
			}
		dfs();
		puts("");
	}
}
