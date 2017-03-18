#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
int W,L;
string m;
string x[610];
int f[400];
int match[610];
int main()
{
	cin>>W>>L;
	cin>>m;
	m="0"+m;
	for(int i=1;i<=W;i++)
		cin>>x[i];
	for(int i=1;i<=L;i++)
	{
		for(int j=1;j<=W;j++)
			match[j]=x[j].size()-1;
		f[i]=i;
		for(int j=i;j;j--)
			for(int k=1;k<=W;k++)
			{
				if(m[j]==x[k][match[k]])
					match[k]--;
				if(match[k]<0)
					f[i]=min(f[i],f[j-1]+i-j+1-int(x[k].size()));
			}
	}
	cout<<f[L]<<endl;
}
