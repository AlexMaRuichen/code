#include <stdio.h>

#include <algorithm>
#include <iostream>  
#include <string>  
#include <map>  

using namespace std;  

template <typename T> __attribute__((optimize(2))) inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> __attribute__((optimize(2))) inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

const int inf = 1e9;
const int maxn = 30;

int n, m, d[maxn][maxn], x, y, z;  
int f[1 << 8][maxn], e[8], v[maxn];
int c, b;  
map <string, int> city;  


__attribute__((optimize(2))) int main()  
{  
	string s, t;
	while (cin >> n >> m && n)
	{
		city.clear();
		int i, j, k;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				d[i][j] = i == j ? 0 : inf;
		for (i = 0; i < n; i++)
		{
			cin >> s;
			city[s] = i;
		}
		while (m--)
		{
			cin >> s >> t >> z;
			x = city[s];
			y = city[t];
			tense(d[x][y], z);
			tense(d[y][x], z);
		}
		for (k = 0; k < n; k++)
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		for (i = 0; i < 8; i++)
		{
			cin >> s;
			e[i] = city[s];
			for (j = 0; j < n; j++)
				f[1 << i][j] = d[j][e[i]];
		}
		for (i = 1; i < 256; i++)  
		{
			if (!(i & (i - 1)))
				continue;

			for (k = 0; k < n; k++)
			{
				f[i][k] = inf;
				v[k] = 0;
				for (int sub = i; sub; sub = (sub - 1) & i)
					tense(f[i][k], f[sub][k] + f[i - sub][k]);
			}
			for (j = 0; b = inf, j < n; j++)
			{
				for (k = 0; k < n; k++)
					if (f[i][k] <= b && !v[k])
						b = f[i][c = k];
				for (k = 0, v[c] = 1; k < n; k++)
					tense(f[i][c], f[i][k] + d[k][c]);
			}
		}

		for (i = 0, b = inf; z = 0, i < 256; b = min(b, z), i++)
			for (j = 0; y = 0, j < 4; z += !!y * f[y][x], j++)
				for (k = 0; k < 8; k += 2)
					if ((i >> k & 3) == j)
						y += 3 << k, x = e[k];
		cout << b << endl;
	}
}