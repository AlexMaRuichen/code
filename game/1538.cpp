#include <stdio.h>

int T;
int n, m, p, l, i;

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d%d", &n, &m, &p);
		if (n <= (m << 1))
		{
			if ((n ^ p) && ((n & 1) == (p & 1)))
				puts("1");
			else if (n == p)
				printf("%d\n", m - ((n - 1) >> 1));
			else
				puts("0");
		}
		else if (n == (m << 1 | 1))
		{
			if(p < (m << 1) && (p & 1))  
				puts("1");  
			else  
				puts("0");  	
		}
		else
		{
			l = n - (m << 1);
			for (i = 1; i <= 15; i++)
				if (l == (1 << i))
				{
					 puts("0");
					 goto lableA;
				}
			for (i = 2; i <= 15; i++)
				if (l < (1 << i))
				{
					(p > (m << 1) + (1 << (i - 1)) && p < (m << 1) + (1 << i)) ? 
					puts("Thrown") : 
					puts("0");
					break;
				}
		}
		lableA:;
	}
}