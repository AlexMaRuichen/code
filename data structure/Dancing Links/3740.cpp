#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
struct DLX
{
	DLX *l,*r,*u,*d,*bottom;
	int x,y;
	DLX(){memset(this,0,sizeof(DLX));}
	void del();
	void recover();
	void* operator new(size_t);
}*head,*c[510],mempool[500000],*p=mempool;
void* DLX :: operator new(size_t)
{
	return p++;
}
void DLX :: del()
{
	l->r=r;
	r->l=l;
	for(DLX *i=d;i!=this;i=i->d)
		for(DLX *j=i->r;i!=j;j=j->r)  
        {  
            j->u->d=j->d;  
            j->d->u=j->u;  
        }
}
void DLX :: recover()
{
	l->r=this;
	r->l=this;
	for(DLX *i=d;i!=this;i=i->d)
		for(DLX *j=i->r;i!=j;j=j->r)  
        {  
            j->u->d=j;  
            j->d->u=j;  
        }
}
int n,m;
bool flag;
void dfs()
{
	if(head->r==head)
	{
		flag=true;
		return;
	}
	DLX *tmp=head->r;
	for(DLX *i=tmp->u;i!=tmp;i=i->u)
	{
		tmp->del();  
        for(DLX *j=i->r;j!=i;j=j->r)  
            j->bottom->del();  
		dfs();
		if(flag)
			return;
		for(DLX *j=i->r;j!=i;j=j->r)  
            j->bottom->recover(); 
		tmp->recover();  
	}
}
bool map[20][310];

void build()
{
    head=new DLX();  
    for(int i=1;i<=n;i++)  
        c[i]=new DLX();  
    for(int i=1;i<=n;i++)  
    {  
        c[i]->l=c[i-1];
        c[i]->r=c[i+1];  
        c[i]->u=c[i];
        c[i]->d=c[i];  
    }  
    c[1]->l=head;
    c[n]->r=head;  
    head->r=c[1];
    head->l=c[n];  
    for(int i=1;i<=m;i++)  
    {  
        DLX *t=NULL;  
        for(int j=1;j<=n;j++)  
        {  
            if(map[i][j])  
            {  
                DLX *now=new DLX();  
                if(t==NULL)  
                    now->l=now->r=now;  
                else  
                    now->l=t,now->r=t->r,  
                    t->r=now,now->r->l=now;  
                now->bottom=c[j];  
                now->u=c[j]->u;  
                now->d=c[j];  
                c[j]->u->d=now;  
                c[j]->u=now;  
                t=now;  
            }  
        }  
    }  
}
int main()
{
	while(scanf("%d%d",&m,&n)==2)
	{
		p=mempool;
		flag=false;
		for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++)
				scanf("%d",&map[i][j]);
		build();
		dfs();
		if(flag)
			puts("Yes, I found it");
		else
			puts("It is impossible");
	}
}
