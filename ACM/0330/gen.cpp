#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>

using namespace std;

int main()
{
	srand(time(NULL));
	rand();
	int n = 1e5;
	printf("%d\n", n);
	for (int i = 1; i <= n; i++)
		printf("%d %d %d %d %d %d\n", rand(), rand() , rand(), rand(), rand(), rand());
}