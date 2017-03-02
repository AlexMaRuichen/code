#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <set>
#include <queue>
using namespace std;
struct point
{
    int x,y;
    point(int a,int b)
    {
		x=a,y=b;
	}
} ;
int n,x[500],y[500],idx[500];
set<pair<int,int> >points;
vector<point> nodes;
vector<int> adj[510];
int dis(int a,int b)
{
    return abs(nodes[a].x - nodes[b].x)+abs(nodes[a].y - nodes[b].y);
}
bool in_segment(int x1,int y1,int x2,int y2,int x3,int y3)
{
    if(x2==x3)
        return x1==x2 &&y1>min(y2,y3)&&y1<max(y2,y3);
    else if(y2==y3)
        return y1==y2 &&x1>min(x2,x3)&&x1<max(x2,x3);
    else
        return true;
}
bool possible(int a,int b)
{
    bool good1=nodes[a].x==nodes[b].x||nodes[a].y==nodes[b].y||points.find(make_pair(nodes[a].x,nodes[b].y))==points.end();
    for(int i=0;i<n;i++)
        if(in_segment(x[i],y[i],nodes[a].x,nodes[a].y,nodes[a].x,nodes[b].y) ||in_segment(x[i],y[i],nodes[a].x,nodes[b].y,nodes[b].x,nodes[b].y))
        {
            good1=false;
            break;
        }
    if(good1)
        return true;
    bool good2=nodes[a].x==nodes[b].x||nodes[a].y==nodes[b].y||points.find(make_pair(nodes[b].x,nodes[a].y))==points.end();
    for(int i=0;i<n;i++)
        if(in_segment(x[i],y[i],nodes[a].x,nodes[a].y,nodes[b].x,nodes[a].y) ||in_segment(x[i],y[i],nodes[b].x,nodes[a].y,nodes[b].x,nodes[b].y))
        {
            good2=false;
            break;
        }
    if(good2)
        return true;
    return false;
}
bool v[510];
int f[510];
int dijkstra(int a,int b)
{
    for(int i=0;i<nodes.size();i++)
    {
        f[i]=~0u>>2;
        v[i]=false;
    }
    for(int i=0;i<n;i++)
        if(idx[i] !=a &&idx[i] !=b)
            v[idx[i]]=true;
	f[a]=0;
    for(int i=0;i<nodes.size();i++)
    {
        int k=0;
        for(int j=0;j<nodes.size();j++)
            if(!v[j] &&(f[j]<f[k]||v[k]))
                k=j;
        if(v[k]||f[k]==~0u>>2)
            return -1;
        if(k==b)
            return f[k];
        v[k]=true;
        for(int j=0;j<adj[k].size();j++)
            if(!v[adj[k][j]])
                f[adj[k][j]]=min(f[adj[k][j]],f[k]+dis(k,adj[k][j]));
    }
    return -1;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d %d",&x[i],&y[i]);
        points.insert(make_pair(x[i],y[i]));
    }
    for(int i=0;i<n;i++)
        for(int a=-1;a <=1;a++)
            for(int b=-1;b <=1;b++)
            {
                if(a==0 &&b==0)
                {
                    nodes.push_back(point(x[i],y[i]));
                    idx[i]=nodes.size()- 1;
                }
                else if(a * b==0 &&points.find(make_pair(x[i] +a,y[i] +b))==points.end())
                    nodes.push_back(point(x[i]+a,y[i]+b));
            }
    for(int i=0;i<nodes.size();i++)
        for(int j=i +1;j<nodes.size();j++)
            if(possible(i,j))
            {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
    int ans=0;
    for(int i=0;i<n;i++)
    {
        int k=dijkstra(idx[i],idx[(i+1)%n]);
        if(k<0)
        {
            ans=-1;
            break;
        }
        else
            ans+=k;
    }
    printf("%d\n",ans);
}
