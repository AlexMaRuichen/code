#include <iostream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;
const int mod=2014;
map <string,int> m;
string s;
int recursion(string s)
{
	if(m.find(s)!=m.end())
		return m[s];
	int ans=1;
	int l=s.length();
	for(int i=1;i*2<l;i++)
	{
		if(s.substr(0,i)==s.substr(l-i,i))
			ans+=recursion(s.substr(i,l-i));
		if(s.substr(0,i)==s.substr(i,i))
			ans+=recursion(s.substr(i,l-i));
		if(s.substr(0,i)==s.substr(l-i,i))
			ans+=recursion(s.substr(0,l-i));
		if(s.substr(l-i*2,i)==s.substr(l-i,i))
			ans+=recursion(s.substr(0,l-i));
	}
	ans%=mod;
	m[s]=ans;
	return ans;
}
int main()
{
	cin>>s;
	cout<<((recursion(s)-1)%mod+mod)%mod<<endl;
}
