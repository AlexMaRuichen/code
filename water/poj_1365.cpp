#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
long long x=1;
int p;
int e;
int ansp[4000];
int anse[4000];
int pre[40000];
int prime[40000];
int cnt;
int tot=1;
string line;
long long mul(int x,int y)
{
	long long ans=1;
	while(y)
	{
		if(y&1)
			ans*=x;
		x*=x;
		y>>=1;
	}
	return ans;
}
int main()
{
	for(int i=2;i<=32800;i++)
		if(!pre[i])
			for(int j=2;i*j<=32800;j++)
				pre[i*j]=true;
	for(int i=2;i<=32767;i++)
		if(!pre[i])
			prime[++cnt]=i;	
	while(getline(cin,line),line[0]!=48)
	{
		memset(ansp,0,sizeof(ansp));
		memset(anse,0,sizeof(anse));
		istringstream stream(line);  
		int tmp=cnt;
		int tcnt=0;
		tot=1;
		x=1;
		while(stream>>p>>e)
			x*=mul(p,e);
		x--;
		while(tmp)
		{
			if(x%prime[tmp]==0)
			{
				ansp[++tcnt]=prime[tmp];
				while(x%prime[tmp]==0)
					x/=prime[tmp],anse[tcnt]++;
			}
			tmp--;
		}
		for(int i=1;i<=tcnt;i++)
			printf("%d %d ",ansp[i],anse[i]);
		puts("");
	}
}
