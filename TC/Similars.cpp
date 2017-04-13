#line 7 "Similars.cpp"  
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

const double eps = 1e-6;
const int inf = 1e9; 
vector <int> v;
map <int, int> m;
  
class Similars  
{  
        public:  
        int maxsim(int L, int R)  
        {  
			for (int i = L, tmp, x; i <= R; i++)
			{
				x = i;
				tmp = 0;
				while (x)
					tmp |= 1 << (x % 10), x /= 10;
				if (m[tmp] <= 1)
				{
					++m[tmp];
					v.push_back(tmp);
				}
			}
			int ans = 0;
			for (int i = 0; i < v.size(); i++)
				for (int j = i + 1; j < v.size(); j++)
					relax(ans, __builtin_popcount(v[i] & v[j]));
			return ans;
        }
        
  
};  
  


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
