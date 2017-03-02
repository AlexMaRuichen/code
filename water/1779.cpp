#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <ctype.h>
using namespace std;
string ans,tmp,k,m;
int main()
{
	cin>>tmp>>ans;
	while(k.length()<ans.length())
		k+=tmp;
	for(int i=0;i<ans.length();i++)
		if(isupper(ans[i]))
			k[i]=toupper(k[i]);
		else
			k[i]=tolower(k[i]);
	for(int i=0;i<ans.length();i++)
		m+=(ans[i]-k[i]<0?ans[i]-k[i]+(isupper(ans[i])?'A':'a')+26:ans[i]-k[i]+(isupper(ans[i])?'A':'a'));
	cout<<m;
}

