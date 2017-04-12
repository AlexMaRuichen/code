#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 2e4 + 10;
const double eps = 1e-7;

int n, k;

double x[maxn];
double v[maxn];
double d[maxn];

bool check(double L) 
{
    for (int i = 1; i <= n; i++)
        d[i] = x[i] - L * v[i];
    sort(d + 1, d + n + 1);
    double sum = 0;
    for (int i = 1; i <= k; i++)
        sum += d[i];
    return sum <= 0;
}

int main() 
{
    double f, p, b, c;
    while (scanf("%d%d%lf", &n, &k, &f) == 3) 
	{
        for (int i = 1; i <= n; i++) 
		{
            scanf("%lf%lf%lf", &p, &b, &c);
            v[i] = p * b / (p + b);
            x[i] = v[i] * c * f;
        }
        double l = 0, r = 10000000000, mid;
        while (r - l >= eps) 
		{
            mid = (l + r) / 2;
        	check(mid) ? r = mid : l = mid;
        }
        printf("%.4lf\n", l);
    }
}