#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 1e6 + 10;
const int maxm = 1e4 + 10;

int cnt = 1;

int Next[maxm];

char stra[maxm], strb[maxn];

int main()
{
	scanf("%s%s", stra + 1, strb + 1);
	for (int i = 2, j = 0; stra[i]; i++, cnt++)
	{
		while (j && stra[j + 1] ^ stra[i])
			j = Next[j];
		stra[j + 1] == stra[i] ? ++j : 1;
		Next[i] = j;
	}
	for (int i = 1, j = 0; strb[i]; i++)
	{
		while (j && stra[j + 1] ^ strb[i])
			j = Next[j];
		stra[j + 1] == strb[i] ? ++j : 1;
		if (j >= cnt)
			return puts("YES"), 0;
	}
	puts("NO");
}