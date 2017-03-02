#include <stdio.h>
#include<ext/pb_ds/priority_queue.hpp>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <algorithm>
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
using namespace __gnu_pbds;
__gnu_pbds::priority_queue <int, less<int> , thin_heap_tag> pq;
const int maxn=10010;
int n;
struct cow
{
    int g,d;
    bool operator < (const cow &s) const
    {
        return s.g<g;
    }
}c[maxn];
bool cmp(const cow &a,const cow &b)
{
    return a.d>b.d;
}
int heap[maxn];
int ans;
int idx=1;
int mx;
int main()
{
    scanf("%d",&n);
    register int i;
    for(i=1;i<=n;i++)
    {
        scanf("%d%d",&c[i].g,&c[i].d);
        mx=max(mx,c[i].d);
    }
    sort(c+1,c+n+1,cmp);
    for(i=mx;i;i--)
    {
        while(idx<=n&&i<=c[idx].d)
            pq.push(c[idx++].g);
        if(!pq.empty())
        {
            ans+=pq.top();;
            pq.pop();
        }
    }
    printf("%d\n",ans);
}
