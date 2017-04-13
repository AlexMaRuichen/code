#line 7 "CurvyonRails.cpp"  
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

const int maxn = 25 * 25 * 6;
const int maxm = 1e6;
const double eps = 1e-6;
const int inf = 1e9;  

int n, m;
  
struct edge
{
	int to, len, cost;
	edge *next, *rev;
	edge() {}
	edge(int to, int len, int cost, edge *next) :to(to), len(len), cost(cost), next(next) {}
	void* operator new(size_t);
}*head[maxn], mem[maxm];

void* edge :: operator new(size_t)
{
	static edge *p = mem;
	return p++;
}

void add(int x, int y, int z, int c)
{
	head[x] = new edge(y, z, c, head[x]);
	head[y] = new edge(x, 0, -c, head[y]);
	head[x]->rev = head[y];
	head[y]->rev = head[x];
}

queue <int> q;
int S, T;
bool v[maxn];
int f[maxn];
edge *pre[maxn];

bool spfa()
{
	memset(f, 0x3f, sizeof(f));
	f[S] = 0;
	q.push(S);
	v[S] = true;
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		for (edge *p = head[x]; p; p = p->next)
			if (p->len && tense(f[p->to], f[x] + p->cost))
			{
				pre[p->to] = p;
				if (!v[p->to])
					v[p->to] = true, q.push(p->to);
			}
		v[x] = false;
	}
	return f[T] ^ 0x3f3f3f3f;
}

inline void operator += (pair<int, int> &a, const pair<int, int> &b)
{
	a.first += b.first;
	a.second += b.second;
}

pair<int, int> augment()
{
	pair<int, int> ans(0, inf);
	for (edge *p = pre[T]; p; p = pre[p->rev->to])
		if (p->len < ans.second)
			ans.second = p->len;
	for (edge *p = pre[T]; p; p = pre[p->rev->to])
		p->len -= ans.second, p->rev->len += ans.second, ans.first += p->cost * ans.second;
	return ans;
}

pair<int, int> EK()
{
	pair<int, int> ans(0, 0);
	while (spfa())
		ans += augment();
	return ans;
}

inline bool check(int x, int y)
{
	return x >= 0 && x < n && y >= 0 && y < m;
}

int cnt;
int id[30][30];
int idx[30][30];
int idy[30][30];

class CurvyonRails  
{  
	public:  
	int getmin(vector <string> field)  
	{
		n = field.size();
		m = field[0].size();
		int cntw = 0, cntb = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (field[i][j] ^ 'w')
					(i + j) & 1 ? ++cntw : ++cntb;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				id[i][j] = ++cnt,
				idx[i][j] = ++cnt,
				idy[i][j] = ++cnt;
		S = ++cnt;
		T = ++cnt;
		if (cntw ^ cntb)
			return -1;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (field[i][j] ^ 'w')
				{
					if ((i + j) & 1)
					{
						add(S, id[i][j], 2, 0);
						if (field[i][j] == '.')
							add(id[i][j], idx[i][j], 2, 0),
							add(id[i][j], idy[i][j], 2, 0);
						else
							add(id[i][j], idx[i][j], 1, 1),
							add(id[i][j], idx[i][j], 1, 0),
							add(id[i][j], idy[i][j], 1, 1),
							add(id[i][j], idy[i][j], 1, 0);
						if (check(i + 1, j))
							add(idy[i][j], idy[i + 1][j], 1, 0);
						if (check(i - 1, j))
							add(idy[i][j], idy[i - 1][j], 1, 0);
						if (check(i, j + 1))
							add(idx[i][j], idx[i][j + 1], 1, 0);
						if (check(i, j - 1))
							add(idx[i][j], idx[i][j - 1], 1, 0);
					}
					else
					{
						add(id[i][j], T, 2, 0);
						if (field[i][j] == '.')
							add(idx[i][j], id[i][j], 2, 0),
							add(idy[i][j], id[i][j], 2, 0);
						else
							add(idx[i][j], id[i][j], 1, 1),
							add(idx[i][j], id[i][j], 1, 0),
							add(idy[i][j], id[i][j], 1, 1),
							add(idy[i][j], id[i][j], 1, 0);
					}
				}
		pair <int, int> ans = EK();
		return ans.second == cntw * 2 ? ans.first : -1;
	}  
        
  
};  
  


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
