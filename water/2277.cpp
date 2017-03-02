#include <stdio.h>
#include <algorithm> 
#include <ctype.h> 
using namespace std;
int n;
int ans[20005];
char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
struct cow
{
	int x,id;
	bool operator < (const cow &s) const
	{
		return x<s.x;
	}
}a[6][20005];
int  read()
{
    static char ch;
    static int   D;
    while(!isdigit(ch=getchar()));
    for(D=ch-'0'; isdigit(ch=getchar());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
int lower_bound(int i,int x)
{
	int l=1,r=n;
	while(true)
	{
		int mid=(l+r)>>1;
		if(a[i][mid].x==x)
			return mid;
		else if(a[i][mid].x>x)
			r=mid-1;
		else
			l=mid+1;
	}
}
bool cmp(int x,int y) 
{
	int f = 0;
	for(int i=1;i<=5;i++)
		if(a[i][lower_bound(i,x)].id>a[i][lower_bound(i,y)].id)
			++f;
	return f>2;
}
int tmp;
int main() 
{
  	n=read();
    for(int i=1;i<=5;i++)
        for(int j=1;j<=n;j++) 
        {
			a[i][j].x=read();
			a[i][j].id=j;
			ans[j]=a[i][j].x;
		}
	for(int i=1;i<=5;i++)
		sort(a[i]+1,a[i]+n+1);
    sort(ans+1,ans+n+1,cmp);
    for(int i=n;i;i--)
        printf ("%d\n", ans[i]);
}

