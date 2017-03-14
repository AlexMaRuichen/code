#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 1e6 + 10;

int n;
int Next[maxn];
char s[maxn];

int main()
{
	scanf("%d%s", &n, s + 1);
	for (int i = 2, j = 0; i <= n; i++)
	{
		while (j && s[j + 1] ^ s[i])
			j = Next[j];
		s[j + 1] == s[i] ? ++j : 1;
		Next[i] = j;
	}
	printf("%d\n", n - Next[n]);
}