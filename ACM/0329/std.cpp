#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
#include<iostream>  
#include<algorithm>  
#include<vector>  
#include<queue>  
#include<map>  
#include<math.h>  
#include<deque>  
using namespace std;  
#define maxn 1010  
#define maxm 20020  
#define LL long long  
#define INF (LL)99999999999999  
struct listt  
{  
    int u,v;  
    LL w;  
    int next;  
}edge[maxm*2];  
int head[maxn];  
int nums;  
void init()  
{  
    memset(head,-1,sizeof(head));  
    nums=1;  
}  
void add(int u,int v,LL w)  
{  
   // cout<<"add"<<u<<" "<<v<<" "<<w<<endl;  
    edge[nums].u=u;  
    edge[nums].v=v;  
    edge[nums].w=w;  
    edge[nums].next=head[u];  
    head[u]=nums++;  
}  
LL mp[maxn][maxn];  
LL val[maxn];  
deque<int>que;  
LL dist[maxn];  
int vis[maxn];  
int n;  
void spfa(int st)  
{  
    for(int i=1;i<=n;i++)dist[i]=INF;  
    memset(vis,0,sizeof(vis));  
    dist[st]=0;  
    que.push_back(st);  
    vis[st]=1;  
    while(!que.empty())  
    {  
        int x=que.front();  
        que.pop_front();  
        vis[x]=0;  
       // cout<<x<<"-"<<endl;;  
        for(int i=head[x];i!=-1;i=edge[i].next)  
        {  
            int y=edge[i].v;  
          //  cout<<i<<" "<<y<<" "<<val[y]<<" "<<val[x]<<endl;  
            if(val[y]>val[st])continue;  
            if(dist[y]>dist[x]+edge[i].w)  
            {  
                dist[y]=dist[x]+edge[i].w;  
                if(!vis[y])  
                {  
                    if(!que.empty())  
                    {  
                        if(dist[y]>dist[que.front()])que.push_back(y);  
                        else que.push_front(y);  
                    }  
                    else que.push_back(y);  
                    vis[y]=1;  
                }  
            }  
        }  
    }  
   // printf("_________________%d\n",st);  
    for(int i=1;i<=n;i++)  
    {  
        mp[st][i]=dist[i];  
   //     printf("%lld ",mp[st][i]);  
    }  
 //   cout<<endl;  
}  
struct lisq  
{  
    int st;  
    int ed;  
    LL minn;  
}Q[maxm];  
int main()  
{  
    int m,q;  
    while(~scanf("%d%d",&n,&m)&&(n||m))  
    {  
        init();  
        while(!que.empty())que.pop_back();  
        for(int i=1;i<=n;i++)  
        {  
            for(int j=1;j<=n;j++)  
            {  
                mp[i][j]=INF;  
            }  
            mp[i][i]=0;  
        }  
        for(int i=1;i<=n;i++)  
            scanf("%lld",&val[i]);  
        int u,v;  
        LL w;  
        for(int i=1;i<=m;i++)  
        {  
            scanf("%d%d%lld",&u,&v,&w);  
            add(u,v,w);  
            add(v,u,w);  
        }  
        scanf("%d",&q);  
        int st,ed;  
        for(int i=1;i<=q;i++)  
        {  
            scanf("%d%d",&Q[i].st,&Q[i].ed);  
            Q[i].minn=INF;  
        }  
        for(int i=1;i<=n;i++)  
        {  
            spfa(i);  
            for(int j=1;j<=q;j++)  
            {  
                Q[j].minn=min(Q[j].minn,mp[i][Q[j].st]+mp[i][Q[j].ed]+val[i]);  
            }  
        }  
        for(int i=1;i<=q;i++)  
        {  
            if(Q[i].minn<INF)printf("%lld\n",Q[i].minn);  
            else puts("-1");  
        }  
        cout<<endl;  
    }  
    return 0;  
}  

