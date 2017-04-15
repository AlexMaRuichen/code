// BEGIN CUT HERE
/* 
 
*/
// END CUT HERE
#line 7 "Nim.cpp"
#include <bits/stdc++.h>

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

using namespace std;

typedef long long LL;

const int maxn = 1 << 17;
const double eps = 1e-6;
const int inf = 1e9;
const int mod = 1e9 + 7;

int inv;
int a[maxn];

void DWT(int l, int r)
{
	if (l == r)
		return;
	int mid = l + r >> 1;
	DWT(l, mid);
	DWT(mid + 1, r);
	for (int i = l, j = mid + 1, x; i <= mid; i++, j++)
	{
		x = (a[i] + a[j]) % mod;
		a[i] = (a[i] - a[j] + mod) % mod;
		a[j] = x;
	}
}

void IDWT(int l, int r)
{
	if (l == r)
		return;
	int mid = l + r >> 1;
	for (int i = l, j = mid + 1, x; i <= mid; i++, j++)
	{
		x = (a[j] - a[i] + mod) * 1ll * inv % mod;
		a[i] = (a[i] + a[j]) * 1ll * inv % mod;
		a[j] = x;
	}
	IDWT(l, mid);
	IDWT(mid + 1, r);
}

bool v[65536];
int p[65536];
int cnt;

void sieve(int N)
{
	for (int i = 2; i < 65536; i++)
		if (!v[i])
		{
			p[++cnt] = i;
			for (int j = 2; i * j < 65536; j++)
				v[i * j] = true;
		}
}

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

class Nim
{
	public:
	int count(int K, int L)
	{ 
		inv = mul(2, mod - 2);
		sieve(L);
		int len = 1;
        for (int i = 1; p[i] <= L; i++) 
			a[p[i]] = 1;
		for(; len <= L; len <<= 1);
		--len;
		DWT(0, len);
		for (int i = 0 ; i <= len; i++)
			a[i] = mul(a[i], K);
		IDWT(0, len);
		return a[0];
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 7; int Arg2 = 6; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 13; int Arg2 = 120; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 100; int Arg2 = 294844622; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 123456789; int Arg1 = 12345; int Arg2 = 235511047; verify_case(3, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	Nim ___test;
	___test.run_test(1);
	return 0;
}
// END CUT HERE
