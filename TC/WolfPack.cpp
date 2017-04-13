#line 2 "WolfPack.cpp"  
#include <cstdlib>  
#include <cctype>  
#include <cstring>  
#include <cstdio>  
#include <cmath>  
#include <algorithm>  
#include <vector>  
#include <string>  
#include <iostream>  
#include <sstream>  
#include <map>  
#include <set>  
#include <queue>  
#include <stack>  
#include <fstream>  
#include <numeric>  
#include <iomanip>  
#include <bitset>  
#include <list>  
#include <stdexcept>  
#include <functional>  
#include <utility>  
#include <ctime>

using namespace std;  
  
typedef long long LL;  

const int maxn = 60;
const int maxm = 1e5 + 10;
const int mod = 1e9 + 7;

int n, m;
int c[maxm];
int a[maxn];
int b[maxn];

int mul(int x, int y)
{
	int ans = 1;
	while (y)
	{
		if (y & 1)
			ans = ans * 1ll * x % mod;
		x = x * 1ll * x % mod;
		y >>= 1;
	}
	return ans;
}

int work(int *a)
{
	int mn = *min_element(a, a + n), mx = *max_element(a, a + n);
	int ans = 0;
	for (int i = mx - m; i <= mn + m; i++)
		if (!((i ^ mn ^ m) & 1))
		{
			int tmp = 1;
			for (int j = 0; j < n; j++)
				tmp = tmp * 1ll * c[(m + a[j] - i) >> 1] % mod;
			(ans += tmp) %= mod;
		}
	return ans;
}

class WolfPack  
{  
        public:  
        int calc(vector <int> x, vector <int> y, int m)  
        {  
			n = x.size();
			::m = m;
			c[0] = 1;
			for (int i = 1; i <= m; i++)
				c[i] = c[i - 1] * 1ll * (m - i + 1) % mod * mul(i, mod - 2) % mod;
			for (int i = 1; i < n; i++)
				if ((x[i] ^ y[i] ^ x[0] ^ y[0]) & 1)
					return 0;
			for (int i = 0; i < n; i++)
				a[i] = x[i] - y[i],
				b[i] = x[i] + y[i];
			return work(a) * 1ll * work(b) % mod;
        }
		
};  
  


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
