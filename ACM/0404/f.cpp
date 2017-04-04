#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

int mod;

struct matrix
{
	int x[6][6];
	matrix()
	{
		memset(x, 0, sizeof(x));
	}
	void init()
	{
		/*****
		0 0000
		1 0011
		2 1100
		3 1001
		4 1111
		5 0110
		*****/
        x[0][0]=1; x[0][1]=1; x[0][2]=1; x[0][3]=1; x[0][4]=1; x[0][5]=0;
        x[1][0]=1; x[1][1]=0; x[1][2]=1; x[1][3]=0; x[1][4]=0; x[1][5]=0;
        x[2][0]=1; x[2][1]=1; x[2][2]=0; x[2][3]=0; x[2][4]=0; x[2][5]=0;
        x[3][0]=1; x[3][1]=0; x[3][2]=0; x[3][3]=0; x[3][4]=0; x[3][5]=1;
        x[4][0]=1; x[4][1]=0; x[4][2]=0; x[4][3]=0; x[4][4]=0; x[4][5]=0;
        x[5][0]=0; x[5][1]=0; x[5][2]=0; x[5][3]=1; x[5][4]=0; x[5][5]=0;
	}
	void print()
	{
		for (int i = 0; i < 6; i++, puts(""))
			for (int j = 0; j < 6; j++)
				printf("%d ", x[i][j]);
	}
};

matrix operator * (const matrix &a, const matrix &b)
{
	matrix ans;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			for (int k = 0; k < 6; k++)
				(ans.x[i][k] += a.x[i][j] * b.x[j][k]) %= mod;
	return ans;
}

matrix mul(matrix a, int y)
{
	matrix ans;
	for (int i = 0; i < 6; i++)
		ans.x[i][i] = 1;
	while (y)
	{
		if (y & 1)
			ans = ans * a;
		a = a * a;
		y >>= 1;
	}
	return ans;
}

int main()
{
	matrix b;
	b.init();
	matrix ans;
	int n;
	while (scanf("%d%d", &n, &mod) && n && mod)
	{
		ans = b;
		ans = mul(ans, n);
		printf("%d\n", ans.x[0][0]);
	}
}