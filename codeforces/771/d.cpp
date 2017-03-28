#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <vector>

using namespace std;

template <typename T> inline bool tense(T &a, const T &b)
{
	return a > b ? a = b, 1 : 0;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, 1 : 0;
}

const int maxn = 85;
const int inf = 1e9;

int n;

vector<int> V, K, X; 

int f[maxn][maxn][maxn][2];

int calc(const vector<int> &v, int from, int limit) 
{
	int cnt = 0;
	for(int i = from; i < v.size() && v[i] < limit; ++i)
		++cnt;
	return cnt;
}

int cost(int v, int k, int x, int w)
{
	return calc(V, v, w) + calc(K, k, w) + calc(X, x, w);
}

char s[maxn];

int main() 
{
	scanf("%d%s", &n, s);
	for (int i = 0; i < n; i++)
		if (s[i] == 'V')
			V.push_back(i);
		else if (s[i] == 'K')
			K.push_back(i);
		else
			X.push_back(i);
	memset(f, 0x3f, sizeof(f));
	f[0][0][0][0] = 0;
	for(int v = 0; v <= V.size(); ++v)
		for(int k = 0; k <= K.size(); ++k)
			for(int x = 0; x <= X.size(); ++x)
				for(int type = 0; type < 2; ++type) 
				{
					int tmp = f[v][k][x][type];
					if(v < V.size())
						tense(f[v+1][k][x][1], tmp + cost(v, k, x, V[v]));
					if(k < K.size() && type == 0)
						tense(f[v][k+1][x][0], tmp + cost(v, k, x, K[k]));
					if(x < X.size())
						tense(f[v][k][x+1][0], tmp + cost(v, k, x, X[x]));
				}
	int ans = inf;
	for(int i = 0; i < 2; ++i)
		tense(ans, f[V.size()][K.size()][X.size()][i]);
	printf("%d\n", ans);
}