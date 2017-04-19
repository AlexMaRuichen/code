#include<iostream>  
#include<cstring>  
#include<ctime>  
#include<cmath>  
#include<algorithm>  
#include<iomanip>  
#include<cstdlib>  
#include<cstdio>  
#include<map>  
#include<bitset>  
#include<set>  
#include<stack>  
#include<vector>  
#include<queue>  
using namespace std;  
#define MAXN 400010  
#define MAXM 1010  
#define ll long long  
#define eps 1e-8  
#define MOD 1000000007  
#define INF 1000000000  
const double pi=acos(-1);  
struct cl{  
    double x;  
    double y;  
    cl(){  
          
    }  
    cl(double _x,double _y){  
        x=_x;  
        y=_y;  
    }  
    friend cl operator +(const cl &x,const cl &y){  
        return cl(x.x+y.x,x.y+y.y);  
    }  
    friend cl operator -(const cl &x,const cl &y){  
        return cl(x.x-y.x,x.y-y.y);  
    }  
    friend cl operator *(const cl &x,const cl &y){  
        return cl(x.x*y.x-x.y*y.y,x.x*y.y+x.y*y.x);  
    }  
    friend cl operator /(const cl &x,const double &y){  
        return cl(x.x/y,x.y/y);  
    }  
};  
cl a[MAXN],b[MAXN],c[MAXN];  
int A[MAXN],B[MAXN];  
int L;  
int R[MAXN];  
int n;  
int N,m;  
int ans=INF*2+1;  
int C,c1,c2;  
void fft(cl *a,int f){  
    int i,j,k;  
    for(i=0;i<n;i++){  
        if(i<R[i]){  
            swap(a[i],a[R[i]]);  
        }  
    }  
    for(i=1;i<n;i<<=1){  
        cl wn(cos(pi/i),f*sin(pi/i));  
        for(j=0;j<n;j+=i<<1){  
            cl w(1,0);  
            for(k=0;k<i;k++,w=w*wn){  
                cl x=a[j+k],y=w*a[j+i+k];  
                a[j+k]=x+y;  
                a[j+i+k]=x-y;  
            }  
        }  
    }  
    if(f==-1){  
        for(i=0;i<n;i++){  
            a[i]=a[i]/n;  
        }  
    }  
}  
int main(){  
    int i,j;  
    scanf("%d%d",&N,&m);  
    for(i=0;i<N;i++){  
        scanf("%d",&A[i]);  
        C+=A[i]*A[i];  
        c1+=2*A[i];  
        c2-=2*A[i];  
    }  
    for(i=0;i<N;i++){  
        scanf("%d",&B[i]);  
        C+=B[i]*B[i];  
        c1-=2*B[i];  
        c2+=2*B[i];  
    }  
    for(i=0;i<N;i++){  
        a[i].x=a[N+i].x=A[i];  
        b[i].x=B[N-i-1];  
    }  
    for(n=1;n<N<<2;n<<=1){  
        L++;  
    }  
    for(i=0;i<n;i++){  
        R[i]=R[i>>1]>>1|((i&1)<<(L-1));  
    }  
      
    fft(a,1);  
    fft(b,1);  
    for(i=0;i<n;i++){  
        c[i]=a[i]*b[i];  
    }  
    fft(c,-1);  
	printf("%d %d %d\n", C, c1, c2);
    for(i=0;i<N;i++){  
        for(j=0;j<=m;j++){  
            ans=min(ans,C+c1*j+N*j*j-2*int(c[N-1+i].x+.5));  
            ans=min(ans,C+c2*j+N*j*j-2*int(c[N-1+i].x+.5));  
        }  
    }  
    printf("%d\n",ans);  
    return 0;  
}  