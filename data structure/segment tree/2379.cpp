#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;
const int maxn=50010;
typedef pair<int,int> point;
point a[maxn];
multiset<int> x, y;
int main()
{
    int n, d;
    scanf("%d%d",&n,&d);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i].first,&a[i].second);
    sort(a+1,a+n+1);
    int ans=0;
    int j=1,k=1;
    for(int i=1;i<=n;i++)
    {
        while(k<=n&&a[k].first<=a[i].first+d)
            y.insert(a[k++].second);
        while(a[j].first+d<a[i].first)
            x.erase(x.find(a[j++].second));
        x.insert(a[i].second);
        if(*x.rbegin()>=2*a[i].second&&*y.rbegin()>=2*a[i].second)
            ans++;
        y.erase(y.find(a[i].second));
    }
    printf("%d\n",ans);
}
