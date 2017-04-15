#include <algorithm>
#include <cstdio>
using namespace std;
int ran() 
{
    static int x = 1364684679;
    x += (x << 2) + 1;
    return x;
}
struct node 
{
    int k, mn, delta, mark, w, sz;
    node *l, *r;
    static node *getnew(node *w = NULL) 
	{
        static node *list = NULL;
        if (w) 
		{
            w->r = list;
            list = w;
            return NULL;
        }
        if (!list) 
		{
            node *q = new node[10000];
            for (int i = 0; i < 10000; i++) 
			{
                q[i].w = ran();
                q[i].r = list;
                list = q + i;
            }
        }
        node *p = list;
        list = list->r;
        p->l = p->r = NULL;
        p->delta = p->mark = 0;
        return p;
    }
    void down() 
	{
        if (mark) 
		{
            if (l)
                swap(l->l, l->r), l->mark ^= 1;
            if (r)
                swap(r->l, r->r), r->mark ^= 1;
            mark = 0;
        }
        if (delta) 
		{
            if (l)
                l->mn += delta, l->delta += delta, l->k += delta;
            if (r)
                r->mn += delta, r->delta += delta, r->k += delta;
            delta = 0;
        }
    }
    void update() 
	{
        mn = k;
        if (l && mn > l->mn + delta)
            mn = l->mn + delta;
        if (r && mn > r->mn + delta)
            mn = r->mn + delta;
        sz = 1;
        if (l)
            sz += l->sz;
        if (r)
            sz += r->sz;
    }
};
#define SIZE(_) ((_) ? (_)->sz : 0)
struct Treap 
{
    node *root;
    Treap() 
	{ root = NULL; }
    void ins(node *&p, int a, int k) 
	{
        if (!p) 
		{
            p = node::getnew();
            p->k = p->mn = k;
            p->sz = 1;
        } 
		else 
		{
            p->down();
            if (SIZE(p->l) >= a) 
			{
                ins(p->l, a, k);
                node *q = p->l;
                if (q->w < p->w) 
				{
                    q->down();
                    p->l = q->r;
                    q->r = p;
                    p = q;
                    p->r->update();
                }
            } 
			else 
			{
                ins(p->r, a - SIZE(p->l) - 1, k);
                node *q = p->r;
                if (q->w < p->w) 
				{
                    q->down();
                    p->r = q->l;
                    q->l = p;
                    p = q;
                    p->l->update();
                }
            }
            p->update();
        }
    }
    void ins(int a, int k) 
	{ 
		ins(root, a, k); 
	}
    static void merge(node *&p, node *x, node *y) 
	{
        if (!x || !y) 
		{
            p = x ? x : y;
        } 
		else if (x->w < y->w) 
		{
            x->down();
            merge(x->r, x->r, y);
            x->update();
            p = x;
        } 
		else 
		{
            y->down();
            merge(y->l, x, y->l);
            y->update();
            p = y;
        }
    }
    void del(node *&p, int a) 
	{
        p->down();
        if (SIZE(p->l) == a) 
		{
            node *q = p;
            merge(p, p->l, p->r);
            node::getnew(q);
        } 
		else if (SIZE(p->l) > a) 
		{
            del(p->l, a);
            p->update();
        } 
		else 
		{
            del(p->r, a - SIZE(p->l) - 1);
            p->update();
        }
    }
    void del(int a) 
	{ 
		del(root, a); 
	}
    static void cut(node *p, node *&x, node *&y, int a) 
	{
        if (a == 0) 
		{
            x = NULL;
            y = p;
        } 
		else if (a == SIZE(p)) 
		{
            x = p;
            y = NULL;
        } 
		else 
		{
            p->down();
            if (SIZE(p->l) >= a) 
			{
                y = p;
                cut(p->l, x, y->l, a);
                y->update();
            } 
			else 
			{
                x = p;
                cut(p->r, x->r, y, a - SIZE(p->l) - 1);
                x->update();
            }
        }
    }
    int ask(node *p, int a, int b) 
	{
        if (a == 0 && b == SIZE(p) - 1)
            return p->mn;
        p->down();
        int u = SIZE(p->l);
        int r = (a <= u && u <= b ? p->k : ~0u >> 1);
        if (a < u)
            r = min(r, ask(p->l, a, b >= u ? u - 1 : b));
        if (b > u)
            r = min(r, ask(p->r, a <= u ? 0 : a - u - 1, b - u - 1));
        return r;
    }
    int ask(int a, int b) 
	{ 
		return ask(root, a, b); 
	}
    void dfs(node *p, int lv) 
	{
        if (p) 
		{
            dfs(p->l, lv + 1);
            for (int i = 0; i < lv; i++)
                putchar(' '), putchar(' ');
            printf("%d %d %d %d %d\n", p->k, p->sz, p->mn, p->delta, p->mark);
            dfs(p->r, lv + 1);
        }
    }
    void dfs() 
	{
        dfs(root, 0);
        puts("");
    }
} T;
void Ins(int a, int k) 
{
    // printf("ins %d %d\n",a,k);
    T.ins(a, k);
}
void Del(int a) 
{
    // printf("del %d\n",a);
    T.del(a);
}
void Revolve(int a, int b, int c) 
{
    // printf("revolve %d %d %d\n",a,b,c);
    node *p, *q, *r, *s;
    Treap::cut(T.root, p, q, a);
    Treap::cut(q, q, r, b - a + 1);
    Treap::cut(r, r, s, c - b);
    Treap::merge(p, p, r);
    Treap::merge(p, p, q);
    Treap::merge(T.root, p, s);
}
void Reverse(int a, int b) 
{
    // printf("reverse %d %d\n",a,b);
    node *p, *q, *r;
    Treap::cut(T.root, p, q, a);
    Treap::cut(q, q, r, b - a + 1);
    q->mark ^= 1;
    swap(q->l, q->r);
    Treap::merge(p, p, q);
    Treap::merge(T.root, p, r);
}
void Add(int a, int b, int c) 
{
    // printf("add %d %d %d\n",a,b,c);
    node *p, *q, *r;
    Treap::cut(T.root, p, q, a);
    Treap::cut(q, q, r, b - a + 1);
    // T.dfs(q,0);puts("");
    q->k += c;
    q->mn += c;
    q->delta += c;
    // printf("c=%d\n",c);
    // T.dfs(q,0);
    // puts("");
    Treap::merge(p, p, q);
    Treap::merge(T.root, p, r);
}
int Ask(int a, int b) 
{
    // printf("ask %d %d\n",a,b);
    return T.ask(a, b);
}
int main() 
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) 
	{
        int x;
        scanf("%d", &x);
        Ins(i, x);
    }
    int M;
    // T.dfs();
    scanf("%d", &M);
    char buf[100];
    while (M--) 
	{
        scanf("%s", buf);
        if (buf[0] == 'A') 
		{
            int x, y, d;
            scanf("%d%d%d", &x, &y, &d);
            x--;
            y--;
            Add(x, y, d);
            // T.dfs();
        } 
		else if (buf[0] == 'I') 
		{
            int x, y;
            scanf("%d%d", &x, &y);
            Ins(x, y);
        } 
		else if (buf[0] == 'D') 
		{
            int x;
            scanf("%d", &x);
            x--;
            Del(x);
        } 
		else if (buf[0] == 'M') 
		{
            int x, y;
            scanf("%d%d", &x, &y);
            x--;
            y--;
            printf("%d\n", Ask(x, y));
        } 
		else if (buf[3] == 'E') 
		{
            int x, y;
            scanf("%d%d", &x, &y);
            x--;
            y--;
            Reverse(x, y);
        } 
		else 
		{
            int x, y, t;
            scanf("%d%d%d", &x, &y, &t);
            x--;
            y--;
            t %= (y - x + 1);
            t += (y - x + 1);
            t %= (y - x + 1);
            if (t) 
			{
                Revolve(x, y - t, y);
            }
        }
    }
    return 0;
}