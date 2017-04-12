#include <stdio.h>

#include <algorithm>

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

using namespace std;

const int maxn = 1e5 + 10;
const double eps = 1e-15;

int n;
double p, q;
double a[maxn];
double b[maxn];

double f(double x)
{
	double y = 1;
	for (int i = 1; i <= n; i++)
		tense(y, (1 - x * b[i]) / a[i]);
	return y * p + x * q;
}

int main()
{
	scanf("%d%lf%lf", &n, &p, &q);
	for (int i = 1; i <= n; i++)
		scanf("%lf%lf", &a[i], &b[i]);
	double l = 0, r = 1.0 / (*max_element(b + 1, b + n + 1)), ll, rr;
	while (r - l > eps)
	{
		ll = (l + r) / 2;
		rr = (ll + r) / 2;
		f(ll) > f(rr) ? r = rr : l = ll;
	}
	printf("%.15lf\n", f((l + r) * 0.5));
}
