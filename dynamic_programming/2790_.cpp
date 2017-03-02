#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 50;
int n,k;
long long ans[MAXN][10];
char word[MAXN];
//ans[i][j] j个乘号，前i位数的最大值

long long change(int x,int y)
{
    //计算x ~ y的组成数字
    long long ans = 0;
    for(int i = x; i <= y; i ++)
        ans = ans * 10 + (word[i] - '0');
    return ans;
}

void dpdpd()
{
    for(int i = 1; i <= k; i ++)
        for(int j = 1; j <= n; j ++)
            for(int m = 1; m <= j; m ++)
                if(ans[m][i - 1] * change(m + 1,j) > ans[j][i])
                    ans[j][i] = ans[m][i - 1] * change(m + 1, j);
}

int main()
{
    scanf("%d %d",&n,&k);
    for(int i = 1; i <= n; i ++)
    {
        cin >> word[i];
        ans[i][0] = change(1,i);
    }
    dpdpd();
    printf("%d\n",ans[n][k]);
    return 0;
} 
