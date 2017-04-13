// BEGIN CUT HERE  
/* 
 
*/  
// END CUT HERE  
#line 7 "Revmatching.cpp"  
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

const int maxn = 30;
const double eps = 1e-6;
const int inf = 1e9;  
  
class Revmatching  
{  
        public:  
        int smallest(vector <string> A)  
        {  
			int n = A.size();
			int ans = inf;
			int mask = 1 << n;
			for (int i = 1; i < mask; i++)
			{
				int at[maxn] = {};
				int cnt = 0;
				for (int j = 0; j < n; j++)
					if (i & (1 << j))
					{
						++cnt;
						for (int k = 0; k < n; k++)
							at[k] += A[j][k] - '0';
					}
				sort(at, at + n);
				int del = n - cnt + 1;
				tense(ans, accumulate(at, at + del, 0));
			}
			return ans;
        }  
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, smallest(Arg0)); }
	void test_case_1() { string Arr0[] = {"0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, smallest(Arg0)); }
	void test_case_2() { string Arr0[] = {"44","44"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(2, Arg1, smallest(Arg0)); }
	void test_case_3() { string Arr0[] = {"861","870","245"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(3, Arg1, smallest(Arg0)); }
	void test_case_4() { string Arr0[] = {"01000","30200","11102","10001","11001"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(4, Arg1, smallest(Arg0)); }
	void test_case_5() { string Arr0[] = {"0111101100","0001101001","1001001000","1000100001","0110011111","0011110100","1000001100","0001100000","1000100001","0101110010"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(5, Arg1, smallest(Arg0)); }

// END CUT HERE
  
};  
  
// BEGIN CUT HERE  
int main()  
{  
        Revmatching ___test;  
        ___test.run_test(-1);  
        return 0;  
}  
// END CUT HERE  
