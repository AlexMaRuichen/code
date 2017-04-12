#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>

using namespace std;

int main()
{
	srand(time(NULL));
	rand();
	int T = 10;
	while (T--)
	{
		printf("%d %d %d %d\n", 200, 1000000, 1, 200);
		for (int i = 1; i <= 1000000; i++)
			printf("%d\n", rand() % 100 + 1);
	}
	puts("0 0 0 0 ");
}