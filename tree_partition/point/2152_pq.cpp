#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
#define M 20200  
using namespace std;  
struct abcd{  
    int to,f,next;  
    bool ban;  
}table[M<<1];  
int head[M],tot=1;  
int n,ans;  
int siz[M];  
void Add(int x,int y,int z)  
{  
    table[++tot].to=y;  
    table[tot].f=z;  
    table[tot].next=head[x];  
    head[x]=tot;  
}  
void Get_Centre_Of_Gravity(int x,int from,int size,int &cg)  
{  
    int i;  
    siz[x]=1;  
    bool flag=1;  
    for(i=head[x];i;i=table[i].next)  
    {  
        if(table[i].ban||table[i].to==from)  
            continue;  
        Get_Centre_Of_Gravity(table[i].to,x,size,cg);  
        if(siz[table[i].to]>size>>1)  
            flag=0;  
        siz[x]+=siz[table[i].to];  
    }  
    if(size-siz[x]>size>>1)  
        flag=0;  
    if(flag)  
        cg=x;  
}  
void DFS(int x,int from,int dis,int cnt[])  
{  
    int i;  
    siz[x]=1;  
    cnt[dis]++;  
    for(i=head[x];i;i=table[i].next)  
    {  
        if(table[i].ban||table[i].to==from)  
            continue;  
        DFS(table[i].to,x,(dis+table[i].f)%3,cnt);  
        siz[x]+=siz[table[i].to];  
    }  
}  
void Calculate(int x)  
{  
    int i;  
    int cnt[3]={1,0,0};  
    for(i=head[x];i;i=table[i].next)  
    {  
        if(table[i].ban)  
            continue;  
        int _cnt[3]={0};  
        DFS(table[i].to,x,table[i].f,_cnt);  
        ans+=cnt[0]*_cnt[0];  
        ans+=cnt[1]*_cnt[2];  
        ans+=cnt[2]*_cnt[1];  
        cnt[0]+=_cnt[0];  
        cnt[1]+=_cnt[1];  
        cnt[2]+=_cnt[2];  
    }  
}  
void Tree_Divide_And_Conquer(int root,int size)  
{  
    int i,cg;  
    if(size==1)  
        return;  
    Get_Centre_Of_Gravity(root,0,size,cg);  
    Calculate(cg);  
    for(i=head[cg];i;i=table[i].next)  
    {  
        if(table[i].ban)  
            continue;  
        table[i].ban=table[i^1].ban=1;  
        Tree_Divide_And_Conquer(table[i].to,siz[table[i].to]);  
    }  
}  
int GCD(int x,int y)  
{  
    return y?GCD(y,x%y):x;  
}  
int main()  
{  
  
    int i,x,y,z;  
    cin>>n;  
    for(i=1;i<n;i++)  
    {  
        scanf("%d%d%d",&x,&y,&z);  
        Add(x,y,z%3);  
        Add(y,x,z%3);  
    }  
    Tree_Divide_And_Conquer(1+n>>1,n);  
    ans=ans*2+n;  
    int gcd=GCD(ans,n*n);  
    cout<<ans/gcd<<'/'<<n*n/gcd<<endl;  
}  
