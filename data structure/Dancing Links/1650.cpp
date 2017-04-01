#include <stdio.h>
#include <algorithm>
using namespace std;
const int mark[10][10]=
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    {0, 6, 7, 7, 7, 7, 7, 7, 7, 6},
    {0, 6, 7, 8, 8, 8, 8, 8, 7, 6},
    {0, 6, 7, 8, 9, 9, 9, 8, 7, 6},
    {0, 6, 7, 8, 9,10, 9, 8, 7, 6},
    {0, 6, 7, 8, 9, 9, 9, 8, 7, 6},
    {0, 6, 7, 8, 8, 8, 8, 8, 7, 6},
    {0, 6, 7, 7, 7, 7, 7, 7, 7, 6},
    {0, 6, 6, 6, 6, 6, 6, 6, 6, 6}
};
struct DLX
{
	DLX *l,*r,*u,*d,*bottom;
	int x,y,val;
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
}*head,*c[400],*stack[4000];
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
int ans;
int map[10][10];
int calc()
{
	int t=0;
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			t+=map[i][j]*mark[i][j];
	return t;
}
void output()
{
	for(int i=1;i<=9;i++,puts(""))
	{
		if(i%3==1)
			puts("+-------+-------+-------+");
		putchar('|'),putchar(' ');
		for(int j=1;j<=9;j++)
		{
			putchar(map[i][j]+'0');
			putchar(' ');
			if(j%3==0&&j^9)
				putchar('|'),putchar(' ');
		}
		putchar('|');
	}
	puts("+-------+-------+-------+");
	puts("");
}
void dfs()
{
	if(!head->r)
	{
		ans=max(ans,calc());
		output();
		return;
	}
	DLX *pro;
	int mn=~0u>>1,t=top;
	for(DLX *it=head->r;it;it=it->r)
		if(it->x<mn)
			mn=it->x,pro=it;
	for(DLX *it=pro->u;it;it=it->u)
	{
		int x=it->x,y=it->y,val=it->val;
		map[x][y]=val;
		del_c((x-1)*9+y);
		del_c(81+(x-1)*9+val);
		del_c(162+(y-1)*9+val);
		del_c(243+((x-1)/3*3+(y-1)/3)*9+val);
		dfs();
		while(top^t)
			stack[top--]->recover();
	}
}
void add(int x,int y,int val)
{
	DLX *it,*last=NULL;
	it=c[(x-1)*9+y];
	last=new DLX(last,NULL,it->u,it,x,y,val);
	it=c[81+(x-1)*9+val];
	last=new DLX(last,NULL,it->u,it,x,y,val);
	it=c[162+(y-1)*9+val];
	last=new DLX(last,NULL,it->u,it,x,y,val);
	it=c[243+((x-1)/3*3+(y-1)/3)*9+val];
	last=new DLX(last,NULL,it->u,it,x,y,val);
}
int main()
{
	head=new DLX(NULL,NULL,NULL,NULL,0,0,0);
	DLX *last=head;
	for(int i=1;i<=324;i++)
		last=new DLX(last,NULL,NULL,NULL,0,0,0),c[i]=last;
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
		{
			scanf("%d",&map[i][j]);
			if(map[i][j])
				add(i,j,map[i][j]);
			else
				for(int k=1;k<=9;k++)
					add(i,j,k);
		}
	dfs();
	printf("%d\n",ans?ans:-1);
}
