#include <stdio.h>
#include <algorithm>
using namespace std;
int n;
int a[100010];
int b[100010];
long long ans;
void merge_sort(int l,int r)
{
    if(l==r)
        return;
    int mid=(l+r)>>1;
    merge_sort(l,mid);
    merge_sort(mid+1,r);
    int px=l,py=mid+1;
    int cnt=l;
    while(cnt<=r)
    {
        if(px>mid)
        {
            b[cnt]=a[py];
            py++;
            cnt++;
        }
        else if(py>r)
        {
            b[cnt]=a[px];
            px++;
            cnt++;
        }
        else if(a[px]>a[py]) 
        {
            b[cnt]=a[py];
            cnt++;
            py++;
            ans+=mid-px+1;
        }
        else
        {
            b[cnt]=a[px];
            px++;
            cnt++;
        }
         
    }
    for(int i=l;i<=r;i++)
        a[i]=b[i];
    return;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    merge_sort(1,n);
    printf("%lld\n",ans);
}
