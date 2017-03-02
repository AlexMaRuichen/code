#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
const int maxn=100010;
int n;
int a[100];
string back[20];
string s[maxn];
void in(int i)
{
	cin>>s[i];
	if(s[i]==back[1])
	{
		--a[1];
		if(a[1]<0)
		{
			puts("NO");
			exit(0);
		}
		s[i]=back[1];
	}
	else if(s[i]==back[2])
	{
		--a[2];
		if(a[2]<0)
		{
			puts("NO");
			exit(0);
		}
		s[i]=back[2];
	}
	else if(s[i]==back[3])
	{
		--a[3];
		if(a[3]<0)
		{
			puts("NO");
			exit(0);
		}
		s[i]=back[3];
	}
	else if(s[i]==back[4])
	{
		--a[4];
		if(a[4]<0)
		{
			puts("NO");
			exit(0);
		}
		s[i]=back[4];
	}
	else if(s[i]==back[5])
	{
		--a[5];
		if(a[5]<0)
		{
			puts("NO");
			exit(0);
		}
		s[i]=back[5];
	}
	else if(s[i]==back[6])
	{
		--a[6];
		if(a[6]<0)
		{
			puts("NO");
			exit(0);
		}
		s[i]=back[6];
	}
	else if(s[i]==back[7])
	{
		if(a[1])
		{
			--a[1];
			s[i]=back[1];
		}
		else
		{
			--a[2];
			if(a[2]<0)
			{
				puts("NO");
				exit(0);
			}
			s[i]=back[2];
		}
	}
	else if(s[i]==back[8])
	{
		if(a[2])
		{
			--a[2];
			s[i]=back[2];
		}
		else
		{
			--a[3];
			if(a[3]<0)
			{
				puts("NO");
				exit(0);
			}
			s[i]=back[3];
		}
	}
	else if(s[i]==back[9])
	{
		if(a[3])
		{
			--a[3];
			s[i]=back[3];
		}
		else
		{
			--a[4];
			if(a[4]<0)
			{
				puts("NO");
				exit(0);
			}
			s[i]=back[4];
		}
	}
	else if(s[i]==back[10])
	{
		if(a[4])
		{
			--a[4];
			s[i]=back[4];
		}
		else
		{
			--a[5];
			if(a[5]<0)
			{
				puts("NO");
				exit(0);
			}
			s[i]=back[5];
		}
	}
	else if(s[i]==back[11])
	{
		if(a[5])
		{
			--a[5];
			s[i]=back[5];
		}
		else
		{
			--a[6];
			if(a[6]<0)
			{
				puts("NO");
				exit(0);
			}
			s[i]=back[6];
		}
	}
}
int main()
{
	back[1]="S";
	back[2]="M";
	back[3]="L";
	back[4]="XL";
	back[5]="XXL";
	back[6]="XXXL";
	back[7]="S,M";
	back[8]="M,L";
	back[9]="L,XL";
	back[10]="XL,XXL";
	back[11]="XXL,XXXL";
	for(int i=1;i<=6;i++)
		cin>>a[i];
	cin>>n;
	for(int i=1;i<=n;i++)
		in(i);
	puts("YES");
	for(int i=1;i<=n;i++)
		cout<<s[i]<<endl;
}
