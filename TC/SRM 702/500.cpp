#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
class GridSort
{
	char s[55][55];
public:
	string sort(int n,int m,vector <int> grid)
	{
		memset(s,0,sizeof(s));
		for(int i=0;i<n;i++)
		{
			int row=-1;
			for(int j=0;j<m;j++)
			{
				if(row==-1)
					row=(grid[i*m+j]+m-1)/m;
				if((grid[i*m+j]+m-1)/m!=row)
					return "Impossible";
				else
					s[i][j]=grid[i*m+j]%m+'0'+1;					
			}
		}
		for(int i=0;i<n;i++)
			if(strcmp(s[0],s[i]))
				return "Impossible";
		return "Possible";
	}
}cls;
int main()
{
	cout<<cls.sort(2,2,{1,2,3,4})<<endl;
}
