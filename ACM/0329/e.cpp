#include <stdio.h>

#include <algorithm>

using namespace std;

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

char a[10][10];  
char s[10];  

inline bool check(int x, int y)
{
	return x & (1 << y);
}

inline int lab(int x, int y)
{
	return (x - 1) * 4 + y;
}

bool win(int x)
{
	for (int i = 1; i <= 4; i++)
	{
		bool flag = true;
		for (int j = 1; j <= 4; j++)
			if (!check(x, lab(i, j)))
			{
				flag = false;
				break;
			}
		if (flag)
			return true;
	}
	for (int j = 1; j <= 4; j++)
	{
		bool flag = true;
		for (int i = 1; i <= 4; i++)
			if (!check(x, lab(i, j)))
			{
				flag =false;
				break;
			}
		if (flag)
			return true;
	}
	bool flag = true;
	for (int i = 1; i <= 4; i++)
		if (!check(x, lab(i, i)))
			{
				flag =false;
				break;
			}
	if (flag)
		return true;
	flag = true;
	for (int i = 1; i <= 4; i++)
		if (!check(x, lab(i, 5 - i)))
			{
				flag =false;
				break;
			}
	if (flag)
		return true;
	return false;
}

bool dfsw(int dep, int x, int y, bool flag)
{
	if (win(x))
		return true;
	if (win(y))
		return false;
	if (dep == 17)
		return false;
	if (flag)
	{
		for (int i = 1; i <= 16; i++)
			if (!check(x, i) && !check(y, i))
				if (dfsw(dep + 1, x + (1 << i), y, false))
					return true;
		return false;
	}
	else
	{
		for (int i = 1; i <= 16; i++)
			if (!check(x, i) && !check(y, i))
				if (!dfsw(dep + 1, x, y + (1 << i), true))
					return false;
		return true;
	}
}

bool dfsl(int dep, int x, int y, bool flag)
{
	if (win(x))
		return false;
	if (win(y))
		return true;
	if (dep == 17)
		return false;
	if (flag)
	{
		for (int i = 1; i <= 16; i++)
			if (!check(x, i) && !check(y, i))
				if (dfsl(dep + 1, x + (1 << i), y, false))
					return true;
		return false;
	}
	else
	{
		for (int i = 1; i <= 16; i++)
			if (!check(x, i) && !check(y, i))
				if (!dfsl(dep + 1, x, y + (1 << i), true))
					return false;
		return true;
	}
}

bool dfst(int dep, int x, int y, bool flag)
{
	if (win(x))
		return false;
	if (win(y))
		return false;
	if (dep == 17)
		return true;

	if (flag)
	{
		for (int i = 1; i <= 16; i++)
			if (!check(x, i) && !check(y, i))
				if (dfst(dep + 1, x + (1 << i), y, false))
					return true;
		return false;
	}
	else
	{
		for (int i = 1; i <= 16; i++)
			if (!check(x, i) && !check(y, i))
				if (!dfst(dep + 1, x, y + (1 << i), true))
					return false;
		return true;
	}
}
  
int main()  
{  
	int T;  
	scanf("%d", &T);
	while (T--)  
	{ 
		scanf("%s", s);
		int cntx = 0, cnty = 0, x = 0, y = 0;  
		for(int i = 1; i <= 4; i++)  
		{ 
			scanf("%s", a[i] + 1);
			for(int j = 1; j <= 4; j++)  
				if(a[i][j]=='x')  
					++cntx, x |= (1 << lab(i, j));  
				else if(a[i][j]=='o')  
					++cnty, y |= (1 << lab(i, j));  
		}
		if (cntx ^ cnty)
			swap(x, y);
		if (s[0] == 'W')
			dfsw(cntx + cnty + 1, x, y, true) ? puts("YES") : puts("NO");
		else if (s[0] == 'L')
			dfsl(cntx + cnty + 1, x, y, true) ? puts("YES") : puts("NO");
		else
			dfst(cntx + cnty + 1, x, y, true) ? puts("YES") : puts("NO");
	} 
}  
