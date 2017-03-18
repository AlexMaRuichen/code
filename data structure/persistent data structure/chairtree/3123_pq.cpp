#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
#define M 80100  
using namespace std;  
struct Tree{  
    Tree *ls,*rs;  
    int num;  
}*tree[M],mempool[20002000],*C=mempool;  
struct abcd{  
    int to,next;  
}table[M<<1];  
int head[M],tot;  
int n,m,q,ans;  
int a[M],fa[M][20],dpt[M],root[M],siz[M],stack[M],top;  
int Find(int x)  
{  
    if(!root[x])  
        siz[x]=1,root[x]=x;  
    if(root[x]==x)  
        return x;  
    return root[x]=Find(root[x]);  
}  
inline void Unite(int x,int y)  
{  
    int fx=Find(x);  
    int fy=Find(y);  
    root[fy]=fx;  
    siz[fx]+=siz[fy];  
}  
inline void Add(int x,int y)  
{  
    table[++tot].to=y;  
    table[tot].next=head[x];  
    head[x]=tot; 
    printf("%d\n",tot); 
}  
inline Tree* New_Node(Tree* _,Tree* __,int ___)  
{  
    C->ls=_;  
    C->rs=__;  
    C->num=___;  
    return C++;  
}  
Tree* Build_Tree(Tree *p,int x,int y,int num)  
{  
    int mid=x+y>>1;  
    if(x==y)  
        return New_Node(0x0,0x0,p->num+1);  
    if(num<=mid)  
        return New_Node(Build_Tree(p->ls,x,mid,num),p->rs,p->num+1);  
    else  
        return New_Node(p->ls,Build_Tree(p->rs,mid+1,y,num),p->num+1);  
}  
int Get_Kth(Tree *p1,Tree *p2,Tree *p3,Tree *p4,int x,int y,int k)  
{  
    int mid=x+y>>1;  
    if(x==y)  
        return mid;  
    int temp = p1->ls->num + p2->ls->num - p3->ls->num - p4->ls->num;  
    if(k<=temp)  
        return Get_Kth(p1->ls,p2->ls,p3->ls,p4->ls,x,mid,k);  
    else  
        return Get_Kth(p1->rs,p2->rs,p3->rs,p4->rs,mid+1,y,k-temp);  
}  
void DFS1(int x)  
{  
    int i;  
    dpt[x]=dpt[fa[x][0]]+1;  
    tree[x]=Build_Tree(tree[fa[x][0]],0,1000000000,a[x]);  
    for(i=head[x];i;i=table[i].next)  
    {  
        if(table[i].to==fa[x][0])  
            continue;  
        fa[table[i].to][0]=x;  
        DFS1(table[i].to);  
    }  
}  
void DFS2(int x,int from)  
{  
    int i;  
    fa[x][0]=from;  
    dpt[x]=dpt[fa[x][0]]+1;  
    tree[x]=Build_Tree(tree[fa[x][0]],0,1000000000,a[x]);  
    stack[++top]=x;  
    for(i=head[x];i;i=table[i].next)  
    {  
        if(table[i].to==from)  
            continue;  
        DFS2(table[i].to,x);  
    }  
}  
inline int LCA(int x,int y)  
{  
    int j;  
    if(dpt[x]<dpt[y])  
        swap(x,y);  
    for(j=19;~j;j--)  
        if(dpt[fa[x][j]]>=dpt[y])  
            x=fa[x][j];  
    if(x==y)  
        return x;  
    for(j=19;~j;j--)  
        if(fa[x][j]!=fa[y][j])  
            x=fa[x][j],y=fa[y][j];  
    return fa[x][0];  
}  
int main()  
{  
    int T,i,j,x,y,k;  
    char p[10];  
    cin>>T;  
    cin>>n>>m>>q;  
    for(i=1;i<=n;i++)  
        scanf("%d",&a[i]);  
    for(i=1;i<=m;i++)  
        scanf("%d%d",&x,&y),Add(x,y),Add(y,x),Unite(x,y);  
    tree[0]=New_Node(C,C,0);  
    for(i=1;i<=n;i++)  
        if(!fa[i][0])  
            DFS1(i);  
    for(j=1;j<=19;j++)  
        for(i=1;i<=n;i++)  
            fa[i][j]=fa[ fa[i][j-1] ][j-1];  
    for(i=1;i<=q;i++)  
    {  
        scanf("%s%d%d",p,&x,&y);  
        x^=ans;y^=ans;  
        if(p[0]=='Q')  
        {  
            scanf("%d",&k);k^=ans;  
            int lca=LCA(x,y);  
            printf("%d\n", ans=Get_Kth(tree[x],tree[y],tree[lca],tree[fa[lca][0]],0,1000000000,k) );  
        }  
        else  
        {  
            if(siz[Find(x)]>siz[Find(y)])  
                swap(x,y);  
            top=0;  
            DFS2(x,y);  
            Unite(x,y);  
            Add(x,y),Add(y,x);  
            for(j=1;j<=19;j++)  
                for(k=1;k<=top;k++)  
                    fa[ stack[k] ][j]=fa[ fa[ stack[k] ][j-1] ][j-1];  
        }
        printf("%d %d %d\n",x,y,tot);  
    }  
}  
