#include <stdio.h>

int zero[] = {0, 6, 12, 22, 30, 32, 44, 54, 64, 76, 86, 98, 110, 118, 130, 132, 162, 170, 184, 194, 202, 282, 290, 302, 356, 1046};

int main()
{
	int n, i;
	scanf("%d", &n);
	for (i = 1; zero[i] <= n; i++)
		if (zero[i] == n)
			return puts("2"), 0;
	puts("1");
}