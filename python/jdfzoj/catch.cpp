#include <stdio.h>
#include <stdlib.h>
using namespace std;
const int maxn=1010;
int main()
{
	char s[]="curl http://www.lydsy.com/JudgeOnline/problem.php?id=1000 -o 1000.html";
	for(int i=1;i<=5;i++)
	{
		s[54]=s[62]=i+'0';
		for(int j=0;j<=9;j++)
		{
			s[55]=s[63]=j+'0';
			for(int k=0;k<=9;k++)
			{
				s[56]=s[64]=k+'0';
				for(int l=0;l<=9;l++)
				{
					s[57]=s[65]=l+'0';
					system(s);
				}
			}
		}
	}
}
