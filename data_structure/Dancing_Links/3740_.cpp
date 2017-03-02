#include<stdio.h>  
#include<string.h>  
#include<algorithm>  
#define N 20  
#define M 310  
using namespace std;  
struct node  
{  
    node *l,*r,*u,*d;  
    int belong;  
}buf[N*M],*head,*c[M];  
int tot,cnt[M];  
bool map[N][M];  
node *newnode()  
{  
    return &buf[++tot];  
}  
void Build(int n,int m)  
{  
    tot=0;  
    head=newnode();  
    for(int i=1;i<=m;i++)  
        c[i]=newnode();  
    for(int i=1;i<=m;i++)  
    {  
        c[i]->l=c[i-1],c[i]->r=c[i+1];  
        c[i]->u=c[i],c[i]->d=c[i];  
    }  
    c[1]->l=head,c[m]->r=head;  
    head->r=c[1],head->l=c[m];  
    for(int i=1;i<=n;i++)  
    {  
        node *t=NULL;  
        for(int j=1;j<=m;j++)  
        {  
            if(map[i][j])  
            {  
                node *now=newnode();  
                if(t==NULL)  
                    now->l=now->r=now;  
                else  
                    now->l=t,now->r=t->r,  
                    t->r=now,now->r->l=now;  
                now->belong=j;  
                now->u=c[j]->u;  
                now->d=c[j];  
                c[j]->u->d=now;  
                c[j]->u=now;  
                t=now;  
            }  
        }  
    }  
}  
void remove(node *x)  
{  
    x->l->r=x->r;  
    x->r->l=x->l;  
    for(node *t=x->d;t!=x;t=t->d)  
    {  
        for(node *k=t->r;k!=t;k=k->r)  
        {  
            k->u->d=k->d;  
            k->d->u=k->u;  
        }  
    }  
}  
void resume(node *x)  
{  
    x->l->r=x;  
    x->r->l=x;  
    for(node *t=x->d;t!=x;t=t->d)  
    {  
        for(node *k=t->r;k!=t;k=k->r)  
        {  
            k->u->d=k;  
            k->d->u=k;  
        }  
    }  
}  
bool dfs()  
{  
    node *t=head->r;  
    if(t==head) return 1;  
    for(node *i=t->d;i!=t;i=i->d)  
    {  
        remove(t);  
        for(node *j=i->r;j!=i;j=j->r)  
        {  
            remove(c[j->belong]);  
        }  
        if(dfs())  
            return 1;  
        for(node *j=i->r;j!=i;j=j->r)  
        {  
            resume(c[j->belong]);  
        }  
        resume(t);  
    }  
    return 0;  
}  
int main()  
{  
    int n,m,i,j,k;  
    while(scanf("%d%d",&n,&m)!=EOF)  
    {  
        for(i=1;i<=n;i++)  
        {  
            for(j=1;j<=m;j++)  
            {  
                scanf("%d",&map[i][j]);  
            }  
        }  
        Build(n,m);  
        if(dfs())  
            puts("Yes, I found it");  
        else  
            puts("It is impossible");  
    }  
    return 0;  
}  


