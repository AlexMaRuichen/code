#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxlen=1e5+10;
const int mod=1e4;
char s[maxlen];
struct hpc
{
	int x[maxlen];
	int len;
	bool flag;
	hpc()
	{
		len=1;
		memset(x,0,sizeof(x));
	}
	void read()
	{
		char ch=getchar();
		int l=0;
		while(ch<'0'||ch>'9')
		{
			if(ch=='-')
				flag=true;
			ch=getchar();
		}
		while(ch>='0'&&ch<='9')
			s[++l]=ch,ch=getchar();
		len=(l+3)/4;
	}
}
int main()
{

}
