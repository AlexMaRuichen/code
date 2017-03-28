#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

int n, k;
char s[2][20], *cur = s[0], *last = s[1];
int lab[100];

void print(int x)
{
	putchar('A' + (x - 1) % 26);
	x -= (x - 1) % 26 + 1;
	while (x)
		putchar('z'), x -= 26;
	putchar(' ');
}

int main()
{
	scanf("%d%d", &n, &k);
	last[0] = 'Y';
	for (int i = 1; i <= n; i++)
		lab[i] = i;
	for (int i = 1; i + k - 1 <= n; i++)
	{
		scanf("%s", cur);
		if (cur[0] == 'N') 
			lab[i + k - 1] = lab[i];
	}
	for (int i = 1; i <= n; i++)
		print(lab[i]);
	puts("");
}