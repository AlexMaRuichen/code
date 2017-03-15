#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 110 
#define EPS 1e-7
#define INF 0x3f3f3f3f
using namespace std;
int m,n;
namespace Linear_Programming
{
    double A[M][M], b[M],c[M],v;
    void Pivot(int l,int e)
    {
        int i,j;
 
        b[l]/=A[l][e];
        for(i=1;i<=n;i++)
            if(i!=e)
                A[l][i]/=A[l][e];
        A[l][e]=1/A[l][e];
 
        for(i=1;i<=m;i++)
            if(i!=l&&fabs(A[i][e])>EPS)
            {
                b[i]-=A[i][e]*b[l];
                for(j=1;j<=n;j++)
                    if(j!=e)
                        A[i][j]-=A[i][e]*A[l][j];
                A[i][e]=-A[i][e]*A[l][e];
            }
 
        v+=c[e]*b[l];
        for(i=1;i<=n;i++)
            if(i!=e)
                c[i]-=c[e]*A[l][i];
        c[e]=-c[e]*A[l][e];
    }
    double Simplex()
    {
        int i,l,e;
        while(1)
        {
            for(i=1;i<=n;i++)
                if(c[i]>EPS)
                    break;
            if((e=i)==n+1)
                return v;
            double temp=INF;
            for(i=1;i<=m;i++)
                if(A[i][e]>EPS&&b[i]/A[i][e]<temp)
                    temp=b[i]/A[i][e],l=i;
            if(temp==INF) return INF;
            Pivot(l,e);
        }
    }
}
int main()
{
    using namespace Linear_Programming;
    int i,j;
    cin>>m>>n;
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=n;j++)
            scanf("%lf",&A[i][j]);
        scanf("%lf",&b[i]);
    }
    for(i=1;i<=n;i++)
        scanf("%lf",&c[i]);
    double ans=Simplex();
    if(ans==INF)
        puts("Infinity");
    else
        printf("%.2lf\n",ans);
}
 