#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 100010;

struct edge
{
	int to;
	edge *next;
	edge() {}
	edge(int to, edge *next) :to(to), next(next) {}
	void* operator new(size_t);
}*head[maxn], mem[maxn << 1];

void* edge :: operator new(size_t)
{
	static edge *p = mem;
	return p++;
}

int main()
{

}