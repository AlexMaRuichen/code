#include <cstdio>  
#include <cstring>  
#include <iostream>  
#include <algorithm>  
#define M 250100  
#define INF 0x3f3f3f3fll  
using namespace std;  
struct abcd{  
    int to,f,next;  
}table[M<<1];  
int head[M],tot;  
int m,n,a[M];  
int pos[M],dpt[M],fa[M][20],dis[M][20];  
void Add(int x,int y,int z)  
{  
    table[++tot].to=y;  
    table[tot].f=z;  
    table[tot].next=head[x];  
    head[x]=tot;  
}  
void DFS(int x)  
{  
    static int cnt=0;  
    int i;  
    pos[x]=++cnt;  
    dpt[x]=dpt[fa[x][0]]+1;  
    for(i=head[x];i;i=table[i].next)  
        if(table[i].to!=fa[x][0])  
        {  
            fa[table[i].to][0]=x;  
            dis[table[i].to][0]=table[i].f;  
            DFS(table[i].to);  
        }  
}  
bool Compare(int x,int y)  
{  
    return pos[x] < pos[y];  
}  
int LCA(int x,int y)  
{  
    int j;  
    if(dpt[x]<dpt[y])  
        swap(x,y);  
    for(j=19;~j;j--)  
        if(dpt[fa[x][j]]>=dpt[y])  
            x=fa[x][j];  
    if(x==y) return x;  
    for(j=19;~j;j--)  
        if(fa[x][j]!=fa[y][j])  
            x=fa[x][j],y=fa[y][j];  
    return fa[x][0];  
}  
int Distance(int x,int y)  
{  
    int j,re=0x3f3f3f3f;  
    for(j=19;~j;j--)  
        if(dpt[fa[x][j]]>=dpt[y])  
            re=min(re,dis[x][j]),x=fa[x][j];  
    return re;  
}  
int main()  
{  
    int i,j,k,x,y,z;  
    cin>>n;  
    for(i=1;i<n;i++)  
    {  
        scanf("%d%d%d",&x,&y,&z);  
        Add(x,y,z);  
        Add(y,x,z);  
    }  
    DFS(1);  
      
    for(j=1;j<=19;j++)  
        for(i=1;i<=n;i++)  
            fa[i][j]=fa[fa[i][j-1]][j-1],  
            dis[i][j]=min(dis[fa[i][j-1]][j-1],dis[i][j-1]);  
  
    static int g[M],stack[M],top;  
    static long long f[M];  
    cin>>m;  
    for(i=1;i<=m;i++)  
    {  
        scanf("%d",&k);  
        for(j=1;j<=k;j++)  
            scanf("%d",&a[j]);  
        sort(a+1,a+k+1,Compare);  
        stack[++top]=1;  
        f[1]=0;g[1]=0;  
        for(j=1;j<=k;j++)  
        {  
            int lca=LCA(stack[top],a[j]);  
            while(dpt[stack[top]]>dpt[lca])  
            {  
                if(dpt[stack[top-1]]<=dpt[lca])  
                {  
                    int temp=min(g[top]?INF:f[top],(long long)Distance(stack[top],lca) );  
                    stack[top--]=0;  
                    if(lca!=stack[top])  
                    {  
                        stack[++top]=lca;  
                        f[top]=0;g[top]=0;  
                    }  
                    f[top]+=temp;  
                    break;  
                }  
                else  
                {  
                    f[top-1]+=min(g[top]?INF:f[top],(long long)Distance(stack[top],stack[top-1]) );  
                    stack[top--]=0;  
                }  
            }  
            if(stack[top]!=a[j])  
            {  
                stack[++top]=a[j];  
                f[top]=0;  
            }  
            g[top]=1;  
        }  
        while(top>1)  
        {  
            f[top-1]+=min(g[top]?INF:f[top],(long long)Distance(stack[top],stack[top-1]) );  
            stack[top--]=0;  
        }  
        printf("%lld\n",f[top--]);  
    }  
    return 0;  
}  
