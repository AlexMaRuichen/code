#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<map>
#include<cstring>
using namespace std;
#define maxn 1001000
#define TIMES 17
#define llg int
#define yyj(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout);
llg n,m,a[maxn],k,sum[maxn],c[maxn],xian[maxn],nextt[maxn],ans[maxn];
vector<llg>f[maxn];

inline int getint()
{
       int w=0,q=0; char c=getchar();
       while((c<'0' || c>'9') && c!='-') c=getchar(); if(c=='-') q=1,c=getchar(); 
       while (c>='0' && c<='9') w=w*10+c-'0', c=getchar(); return q ? -w : w;
}

llg lowbit(llg x) {return x&-x;}

void add(llg x,llg val) {for (;x<=n+1;x+=x&-x) c[x]+=val;}

llg find (llg x)
{
    llg pos=0;
    for (llg i=TIMES;i>=0;i--)
    {
        if (pos+(1<<i)<=n+1 && c[pos+(1<<i)]<x) 
            x-=c[pos+(1<<i)],pos+=(1<<i);
    }
    return pos+1;
}

int main()
{
    yyj("E");
    cin>>n;
    for (llg i=1;i<=n;i++) a[i]=getint();
    for (llg i=1;i<=n+1;i++) xian[i]=n+1;
    for (llg i=n+1;i>=1;i--) 
    {
        nextt[i]=xian[a[i]];
        xian[a[i]]=i;
    }
    
    for (llg i=1;i<=n+1;i++) add(xian[i],1),f[1].push_back(i);;
    for (llg i=1;i<=n;i++)
    {
        llg w=f[i].size();
        for (llg j=0;j<w;j++)
        {
            llg d=f[i][j];
            llg wz=find(d+1);
            ans[d]++;
            f[wz].push_back(d);
        }
        add(i,-1),add(nextt[i],1);
    }
    for (llg i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}