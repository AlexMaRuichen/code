#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 1e6 + 10;

template <typename T> __attribute__((optimize(2))) inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> __attribute__((optimize(2))) inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}


int f[maxn];
int q[maxn];

__attribute__((optimize(2))) int main()
{
	int T, x, k, t;
	scanf("%d", &T);
	while (T--)
	{
		memset(f, 0x3f, sizeof(f));
		scanf("%d%d%d", &x, &k, &t);
		f[x] = 0;
		int l = 1, r = 0;
		q[++r] = x; 
		for (int i = x - 1; i; i--)
		{
			while (l <= r && q[l] - i > t)
				++l;
			tense(f[i], f[q[l]]);
			if (i * 1ll * k <= x)
				tense(f[i], f[i * k]);
			++f[i];
			while (l <= r && f[q[r]] > f[i])
				--r;
			q[++r] = i;
		}
		/*for (int i = 1; i <= x; i++)
			printf("%d ", f[i]);
		puts("");*/
		printf("%d\n", f[1]);
	}
}