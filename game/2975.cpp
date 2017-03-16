#include <stdio.h>

int main()
{
	int n, tmp, ans;
	int a[1010];
	while (scanf("%d", &n) && n)
	{
		tmp = ans = 0;
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]), tmp ^= a[i];;
		for (int i = 1; i <= n; i++)
			(a[i] ^ tmp) < a[i] ? ++ans : 1;
		printf("%d\n", ans);
	}	
}