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
	cin>>ldr>>dlr;
	len=ldr.length();
	process(0,len-1,0,len-1);
	for(int i=len-1;i>=0;i--)
		printf("%c",lrd[i]);
}
void process(int l,int r,int L,int R)
{
	if(l>r)
		return;
	lrd+=dlr[L];
	if(l==r)
		return;
	int i;
	for(i=l;i<=r;i++)
		if(ldr[i]==dlr[L])
			break;
	process(i+1,r,L+i-l+1,R);		
	process(l,i-1,L+1,L+i-l);
}
