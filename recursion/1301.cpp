#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
using namespace std;
string dlr;
string ldr;
string lrd;
int tot;
int len;
void process(int l,int r,int L,int R);
int main()
{
	cin>>ldr>>lrd;
	len=ldr.length();
	process(0,len-1,0,len-1);
	cout<<dlr;
}
void process(int l,int r,int L,int R)
{
	if(l>r)
		return;
	dlr+=lrd[R];
	if(l==r)
		return;
	int i;
	for(i=l;i<=r;i++)
		if(ldr[i]==lrd[R])
			break;
	process(l,i-1,L,L+i-l-1);
	process(i+1,r,L+i-l,R-1);
}
