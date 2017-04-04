#include <bits/stdc++.h>  
#define xx first  
#define yy second  
#define mp make_pair  
#define pb push_back  
#define fill( x, y ) memset( x, y, sizeof x )  
#define copy( x, y ) memcpy( x, y, sizeof x )  
using namespace std;  
  
typedef long long LL;  
typedef pair < int, int > pa;  
  
inline int read()  
{  
    int sc = 0; char ch = getchar();  
    while( ch < '0' || ch > '9' ) ch = getchar();  
    while( ch >= '0' && ch <= '9' ) sc = sc * 10 + ch - '0', ch = getchar();  
    return sc;  
}  
  
const int MAXN = 400010;  
const int MAXM = 40000000;  
const int mod = 998244353;  
  
int n, rt[MAXN], f[MAXM], ls[MAXM], rs[MAXM], cur, Q, tot;  
  
inline int qpow(int x, int y) { int ret = 1; for( ; y ; y >>= 1, x = 1LL * x * x % mod ) if( y & 1 ) ret = 1LL * ret * x % mod; return ret; }  
  
inline int merge(int a, int b) { return ( 1LL * a * ( mod + 1 - b ) + 1LL * b * ( mod + 1 - a ) ) % mod; }  
  
inline void add2(int &x, int l, int r, int ql, int qr, int v)  
{  
    if( !x ) x = ++tot;  
    if( l == ql && r == qr ) { f[ x ] = merge( f[ x ], v ); return ; }  
    int mid = l + r >> 1;  
    if( qr <= mid ) add2( ls[ x ], l, mid, ql, qr, v );  
    else if( ql > mid ) add2( rs[ x ], mid + 1, r, ql, qr, v );  
    else add2( ls[ x ], l, mid, ql, mid, v ), add2( rs[ x ], mid + 1, r, mid + 1, qr, v );  
}  
  
inline void add1(int x, int l, int r, int ql, int qr, int nxtl, int nxtr, int v)  
{  
    if( l == ql && r == qr ) { add2( rt[ x ], 0, n, nxtl, nxtr, v ); return ; }  
    int mid = l + r >> 1;  
    if( qr <= mid ) add1( x << 1, l, mid, ql, qr, nxtl, nxtr, v );  
    else if( ql > mid ) add1( x << 1 | 1, mid + 1, r, ql, qr, nxtl, nxtr, v );  
    else add1( x << 1, l, mid, ql, mid, nxtl, nxtr, v ), add1( x << 1 | 1, mid + 1, r, mid + 1, qr, nxtl, nxtr, v );  
}  
  
inline int query2(int x, int l, int r, int p)  
{  
    if( !x ) return 0;  
    int ret = f[ x ];  
    if( l == r ) return ret;  
    int mid = l + r >> 1;  
    if( p <= mid ) return merge( query2( ls[ x ], l, mid, p ), ret );  
    return merge( query2( rs[ x ], mid + 1, r, p ), ret );  
}  
  
inline int query1(int x, int l, int r, int p, int v)  
{  
	printf("%d %d\n", l, r);
    int ret = query2( rt[ x ], 0, n, v );  
    if( l == r ) return ret;  
    int mid = l + r >> 1;  
    if( p <= mid ) 
	return merge( query1( x << 1, l, mid, p, v ), ret );  
    return merge( query1( x << 1 | 1, mid + 1, r, p, v ), ret );  
}  
  
int main()  
{  
#ifdef wxh010910  
    freopen( "data.in", "r", stdin );  
#endif  
    n = read() + 1; Q = read();  
    while( Q-- )  
    {  
        int opt = read(), l = read(), r = read(), len = r - l + 1, inv = qpow( len, mod - 2 );  
        if( opt == 1 )  
        {  
            add1( 1, 0, n, l, r, l, r, 1LL * 2 * inv % mod );  
            add1( 1, 0, n, 0, l - 1, l, r, inv );  
            add1( 1, 0, n, l, r, r + 1, n, inv );  
            cur++;  
        }  
        else  
        {  
            if( l == 1 && ( cur & 1 ) ) printf( "%d\n", query1( 1, 0, n, 0, r ) );  
            else printf( "%d\n", ( mod + 1 - query1( 1, 0, n, l - 1, r ) ) % mod );  
        }  
    }  
} 