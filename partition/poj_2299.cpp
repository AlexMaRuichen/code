#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <ctype.h>
using namespace std;
int n;
int a[500010];
int b[500010];
int t;
long long ans;
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
   
int  read()
{
    static char ch;
    static int   D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
void merge_sort(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	merge_sort(l,mid);
	merge_sort(mid+1,r);
	int px=l,py=mid+1;
	int cnt=l;
	while(cnt<=r)
	{
		if(px>mid)
			b[cnt++]=a[py++];
		else if(py>r||a[px]<=a[py])
			b[cnt++]=a[px++];
		else 
			b[cnt++]=a[py++],ans+=mid+1-px;
	}
	for(int i=l;i<=r;i++)
		a[i]=b[i];
	return;
}

int main()
{
//	t=read();
	scanf("%d",&t);
	int x=1;
	while(x<=t)
	{
//		n=read();
		scanf("%d",&n);
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++)
			/*a[i]=read()*/scanf("%d",&a[i]);
		merge_sort(1,n);
		printf("Scenario #%d:\n%lld\n\n",x,ans);
		ans=0;
		x++;
		
	}
}
