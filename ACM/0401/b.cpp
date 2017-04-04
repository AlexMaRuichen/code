#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 1010;

struct heap
{
    heap *ls, *rs;
    int val, dis, size;
    heap();
    heap(int x);
    void* operator new(size_t);
}*root[maxn], nil, *null=&nil, mem[maxn], *p;

heap :: heap()
{
    ls = rs = this;
    val = size = 0;
    dis = -1;
}

heap :: heap(int x)
{
    ls = rs = null;
    val = x;
    dis = 0;
    size = 1;
}

void* heap :: operator new(size_t)
{
    return p++;
}

heap* merge(heap *x, heap *y)
{
    if(x == null)
        return y;
    if(y == null)
        return x;
    if(x->val < y->val)
        swap(x, y);
    x->rs = merge(x->rs, y);
    x->size = x->ls->size + x->rs->size + 1;
    if(x->ls->dis < x->rs->dis)
        swap(x->ls, x->rs);
    x->dis = x->rs->dis + 1;
    return x;
}
void pop(heap *&x)
{
    x=merge(x->ls, x->rs);
}

int size[maxn];

void work(int *a, int n, int *ans)  
{
	int cnt = 0, res = 0;
	p = mem;
	for(int i = 0; i < n; i++)
	{
		root[++cnt] = new heap(a[i]);
		size[cnt] = 1;
		while(cnt > 1 && root[cnt - 1]->val > root[cnt]->val)
		{
			--cnt;
			if (size[cnt + 1] & 1)
				res += root[cnt]->val - root[cnt + 1]->val;
			root[cnt] = merge(root[cnt], root[cnt + 1]);
			size[cnt] += size[cnt + 1];
			while((root[cnt]->size << 1) > size[cnt] + 1)
				pop(root[cnt]);
		}
		ans[i] = res;
	}
}  
  
  
int a[maxn], b[maxn], c[maxn], cost[2][maxn][maxn], f[maxn][maxn];  
  
  
int main()  
{  
    int n, k;  
    while (1)  
    {  
        scanf("%d%d", &n, &k);  
        if (n == 0) 
			break;  
        for (int i = 0; i < n; ++i)  
        {  
            scanf("%d", a + i);  
            b[i] = a[i] - i;  
            c[i] = -a[i] - i;  
        }  

        memset(cost, 0x3f, sizeof(cost));

        for (int i = 0; i < n; i++)  
        {  
            work(b + i, n - i, cost[0][i] + i);  
            work(c + i, n - i, cost[1][i] + i);  
        }  
  
        memset(f, 0x3f, sizeof(f));
        f[0][0] = 0;                
        for (int t = 1; t <= k; ++t)  
            for (int i = 1; i <= n; ++i)  
                for (int j = 0; j < i; ++j)  
                    f[t][i] = min(f[t][i], f[t - 1][j] + min(cost[0][j][i - 1], cost[1][j][i - 1]));  
        printf("%d\n", f[k][n]);  
    }  
}  
