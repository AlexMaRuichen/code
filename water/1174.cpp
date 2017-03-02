#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
struct stu
{
	string name;
	string num;
	int a,b,c;
}s[100010];
bool cmp(stu x,stu y)
{
	return x.a+x.b+x.c>y.a+y.b+y.c;
}
int n;
int avea,aveb,avec;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i].num>>s[i].name>>s[i].a>>s[i].b>>s[i].c;
		avea+=s[i].a;
		aveb+=s[i].b;
		avec+=s[i].c;
	}
	sort(s+1,s+n+1,cmp);
	cout<<avea/n<<" "<<aveb/n<<" "<<avec/n<<endl;
	cout<<s[1].num<<" "<<s[1].name<<" "<<s[1].a<<" "<<s[1].b<<" "<<s[1].c;
}
