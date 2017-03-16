#include <stdio.h>

#include <algorithm>

using namespace std;

int p, q;

int main()
{
	while (scanf("%d%d", &p, &q) && p && q)
	{
		bool flag = false;
		if (p < q)
			swap(p, q);
		while (q)
		{
			flag ^= 1;
			if (p / q >= 2) 
				break;
			p -= q;
			swap(p, q);
		}
		puts(flag ? "Stan wins" : "Ollie wins");
	}
}