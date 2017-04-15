#include <stdio.h>
#include <string.h>
#include <time.h>

#include <algorithm>

using namespace std;

int main()
{
	srand(time(NULL));
	rand();
	int n = 200000;
	printf("%d\n", n);
	for (int i = 1; i <= n; i++)
		printf("%d\n", rand());
}