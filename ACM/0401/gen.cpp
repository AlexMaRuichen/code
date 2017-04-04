#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>

using namespace std;

void gen()
{
	FILE *p = fopen("a.in", "w");
	int T = 10;
	while (T--)
	{
		int n = 1000;
		fprintf(p, "%d\n", n);
		for (int i = 1; i <= n; i++)
			fprintf(p, "%d\n", rand() % 10000 + 1);
	}
	fclose(p);
}

int main()
{
	srand(time(NULL));
	rand();
	system("g++ d.cpp -o d -g -Wall");
	system("g++ tmp.cpp -o tmp -g -Wall");
	while (true)
	{
		static int cnt;
		gen();
		system("d < a.in > a.out");
		system("tmp < a.in > b.out");
		if (system("fc a.out b.out"))
			return puts("WA"), 0;
		printf("%d AC\n", ++cnt);
	}
}