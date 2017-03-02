#include <stdio.h>
#include <stdlib.h>
using namespace std;
const int maxn=1010;
int main()
{
	char s[]="curl http://www.lydsy.com/JudgeOnline/problem.php?id=1000 -o 1000.html";
	for(int i=1;i<=5;i++)
	{
		s[53]=s[61]=i+'0';
		for(int j=0;j<=9;j++)
		{
			s[54]=s[62]=j+'0';
			for(int k=0;k<=9;k++)
			{
				s[55]=s[63]=k+'0';
				for(int l=0;l<=9;l++)
				{
					s[56]=s[64]=l+'0';
					system(s);
				}
			}
		}
	}
}
