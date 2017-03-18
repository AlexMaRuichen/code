#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 100100
using namespace std;
int n,ans;
int a[M];
void Gauss_Elimination()
{
    int i,j,k=0;
    for(j=30;~j;j--)
    {
        for(i=k+1;i<=n;i++)
            if(a[i]&(1<<j))
                break;
        if(i==n+1) 
        	continue;
        swap(a[i],a[++k]);
        for(i=1;i<=n;i++)
            if(i!=k&&a[i]&(1<<j))
                a[i]^=a[k];
    }
    for(i=1;i<=k;i++)
        ans^=a[i];   
}
int main()
{
    int i;
    cin>>n;
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    Gauss_Elimination();
    cout<<ans<<endl;
    return 0;
}
