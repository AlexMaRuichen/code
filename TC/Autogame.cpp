// BEGIN CUT HERE  
/* 

*/  
// END CUT HERE  
#line 7 "Autogame.cpp"  
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

const int maxn = 60;
const double eps = 1e-6;
const int inf = 1e9;  
const int mod = 1e9 + 7;

int n;
int fa[maxn];
int size[maxn];

int getfa(int x)
{
	return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}

void merge(int x, int y)
{
	x = getfa(x);
	y = getfa(y);
	if (x == y)
		return;
	if (size[y] < size[x])
		swap(x, y);
	fa[x] = y;
	size[y] += size[x];
}

void init()
{
	for (int i = 0; i < n; i++)
		fa[i] = i, size[i] = 1;
}

class Autogame  
{  
	public:
	int wayscnt(vector <int> a, int K)  
	{
		n = a.size();
		vector <int> pos(n);
		for (int i = 0; i < n; i++)
			--a[i];
		for (int i = 0; i < n; i++)
			pos[i] = i;
		init();
		for (int i = 1; i <= min(n, K); i++)
		{
			for (int j = 0; j < n; j++)
				pos[j] = a[pos[j]];
			for (int j = 0; j < n; j++)
				for (int k = j + 1; k < n; k++)
					if (pos[j] == pos[k])
						merge(j, k);
		}
		int ans = 1;
		for (int i = 0; i < n; i++)
			if (getfa(i) == i)
				ans = ans * 1ll * (size[i] + 1) % mod;
		return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 8; verify_case(0, Arg2, wayscnt(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 4; verify_case(1, Arg2, wayscnt(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {2,1}	; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 42; int Arg2 = 4; verify_case(2, Arg2, wayscnt(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {2,3,4,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 9; verify_case(3, Arg2, wayscnt(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {4,4,3,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 18; verify_case(4, Arg2, wayscnt(Arg0, Arg1)); }

// END CUT HERE

};  

// BEGIN CUT HERE  
int main()  
{  
	Autogame ___test;  
	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
