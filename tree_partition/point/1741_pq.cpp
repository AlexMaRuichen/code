#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
#define M 10100  
using namespace std;  
struct abcd{  
    int to,f,next;  
    bool ban;  
}table[M<<1];  
int head[M],tot=1;  
int n,k,ans;  
int siz[M],fa[M],dist[M];  
int stack[M],top;  
void Initialize()  
{  
    memset(head,0,sizeof head);  
    tot=1;ans=0;  
}  
void Add(int x,int y,int z)  
{  
    table[++tot].to=y;  
    table[tot].f=z;  
    table[tot].next=head[x];  
    head[x]=tot;  
    table[tot].ban=0;  
}  
void Get_Centre_Of_Gravity(int x,int size,int &cg)  
{  
    int i;  
    bool flag=1;  
    siz[x]=1;  
    for(i=head[x];i;i=table[i].next)  
        if(!table[i].ban)  
            if(table[i].to!=fa[x])  
            {  
                fa[table[i].to]=x;  
                Get_Centre_Of_Gravity(table[i].to,size,cg);  
                if(siz[table[i].to]>size>>1)  
                    flag=0;  
                siz[x]+=siz[table[i].to];  
            }  
    if(size-siz[x]>size>>1)  
        flag=0;  
    if(flag)  
        cg=x;  
}  
void DFS1(int x,int dis)  
{  
    int i;  
    dist[x]=dis;  
    for(i=head[x];i;i=table[i].next)  
    {  
        if(table[i].ban)  
            continue;  
        if(table[i].to==fa[x])  
            continue;  
        fa[table[i].to]=x;  
        DFS1(table[i].to,dis+table[i].f);  
    }  
}  
void DFS2(int x)  
{  
    int i;  
    stack[++top]=dist[x];  
    for(i=head[x];i;i=table[i].next)  
    {  
        if(table[i].ban)  
            continue;  
        if(table[i].to==fa[x])  
            continue;  
        DFS2(table[i].to);  
    }  
}  
int Calculate(int root)  
{  
    int i,j,re=0;  
    top=0;  
    DFS2(root);  
    sort(stack+1,stack+top+1);  
    for(i=1,j=top;i<=top;i++)  
    {  
        for(;j&&stack[j]+stack[i]>k;j--);  
        re+=j;  
    }  
    return re;  
}  
void Tree_Divide_And_Conquer(int root,int size)  
{  
    int i,cg;  
    fa[root]=0;  
    Get_Centre_Of_Gravity(root,size,cg);  
    siz[fa[cg]]=size-siz[cg];  
    fa[cg]=0;  
    DFS1(cg,0);  
    ans+=Calculate(cg);  
    for(i=head[cg];i;i=table[i].next)  
        if(!table[i].ban)  
            ans-=Calculate(table[i].to);  
    for(i=head[cg];i;i=table[i].next)  
        if(!table[i].ban)  
            table[i].ban=table[i^1].ban=1,Tree_Divide_And_Conquer(table[i].to,siz[table[i].to]);  
}  
int main()  
{  
    int i,x,y,z;  
    while(cin>>n>>k,n&&k)  
    {  
        Initialize();  
        for(i=1;i<n;i++)  
            scanf("%d%d%d",&x,&y,&z),Add(x,y,z),Add(y,x,z);  
        Tree_Divide_And_Conquer(1,n);  
        cout<<(ans-n>>1)<<endl;  
    }  
}  

