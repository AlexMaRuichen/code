#include<stdio.h>
#include <string.h>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long ll;
const int maxn=50;
string a,b;
ll f[maxn][2][maxn][2];
ll getf(string s,int n,int targ1,int targ2)
{
	memset(f,0,sizeof(f));
	f[0][false][25][true]=1;
	for(int i=0;i<n;i++)
		for(int und=0;und<2;und++)
			for(int k=0;k<maxn;k++)
				for(int is0=0;is0<2;is0++)
				{
					ll cur=f[i][und][k][is0];
					for(int nxt=0;nxt<=9;nxt++)
					{
						if(targ2!=-1&&(nxt!=0||is0==false)&&nxt!=targ1&&nxt!=targ2)
							continue;
						if(und==0&&nxt>s[i]-'0')
							continue;
						bool nis0=is0;
						nis0&=!nxt;
						int nk=k;
						if(!nis0)
						{
							if(targ2!=-1)
							{
								if(nxt==targ1)
									nk--;
								else if(nxt==targ2)
									nk++;
							}
							else
							{
								if(nxt==targ1)
								 	nk--;
								else
									nk++;
							}
						}
						f[i+1][und|(nxt<s[i]-'0')][nk][nis0]+=cur;
					}
				}
	ll res=0;
	if(targ2!=-1)
	{
		for(int i=0;i<2;i++)
			res+=f[n][i][25][false];
		return res;
	}
	for(int i=0;i<2;i++)
		for(int k=0;k<=25;k++)
			res+=f[n][i][k][false];
	return res;
}
ll F(string s)
{
	int n=s.size();
	ll res=0;
	for(int targ1=0;targ1<=9;targ1++)
		res+=getf(s,n,targ1,-1);
	for(int targ1=0;targ1<=9;targ1++)
		for(int targ2=targ1+1;targ2<=9;targ2++)
			res-=getf(s,n,targ1,targ2);
	return res;
}
int main()
{
	cin>>a>>b;
	for(int i=a.size()-1;i>=0;i--)
	{
		int c=a[i]-'0';
		if(c>0)
		{
			a[i]--;
			break;
		}
		else
			a[i]='9';
	}
	printf("%lld\n",F(b)-F(a));
}
