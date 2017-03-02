#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
const int N=600+10,M=300+10;
int n,m,just[N],f[N];
string st,a[N];
inline int min(int a,int b)
{if(a<b)return a;return b;}
int main()
{
  freopen("poj3267.in","r",stdin);
  freopen("poj3267.out","w",stdout);
  scanf("%d%d\n",&n,&m);
  cin>>st;
  st="0"+st;
  for(int i=1;i<=n;i++)
    cin>>a[i];
  for(int i=1;i<=m;i++)
  {
    for(int j=1;j<=n;j++)
      just[j]=a[j].size()-1;
    f[i]=i;
    for(int j=i;j>0;j--)
      for(int k=1;k<=n;k++)
      {
        if(st[j]==a[k][just[k]])
          just[k]--;
        if(just[k]<0)
          f[i]=min(f[i],f[j-1]+i-j+1-a[k].size());
      }
  }
  printf("%d\n",f[m]);
}
