#include <stdio.h>
const int maxn=100010;
class BreedCounting
{
    int f[4][maxn];
    int n,q;
    void query()
    {
        static int x,y;
        scanf("%d%d",&x,&y);
        printf("%d %d %d\n",f[1][y]-f[1][x-1],f[2][y]-f[2][x-1],f[3][y]-f[3][x-1]);
    }
public:
    int solve()
    {
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;i++)
        {
            static int x;
            scanf("%d",&x);
            ++f[x][i];
            f[1][i]+=f[1][i-1];
            f[2][i]+=f[2][i-1];
            f[3][i]+=f[3][i-1];
        }
        while(q--)
            query();
    }

}cls;
int main()
{
    cls.solve();
}
