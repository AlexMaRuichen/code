#include <stdio.h>
#include <algorithm>
#define color(x) ((x)=='R'?1:(x)=='G'?4:16)
using namespace std;
int n,m;
char a[1010];
int l[1010];
int r[1010];
int c[1010];
int ans[2][1010];
int tot;
int g[4];
int main()
{
	while(~scanf("%d",&n))
	{
		m=n;
		tot=0;
		scanf("%s",a);
		register int i,p=1,j,q;
		for(i=1;i<=n;i++)
			l[i]=i-1,r[i]=i+1,c[i]=color(a[i-1]);
		l[1]=n;
		r[n]=1;
		int cnt=n-2;
		while(cnt)
		{
			for(i=1;i<4;i++)
				g[i]=0;
			for(q=p;r[q]!=p;q=r[q])
				++g[c[q]==1?1:c[q]==4?2:3];
			++g[c[l[p]]==1?1:c[l[p]]==4?2:3];
			for(i=1;i<4;i++)
				if(g[i]==1)
				{
					for(q=p;c[q]!=(i==1?1:i==2?4:16);q=r[q]);
					for(j=1;j<=n;j++,p=r[p])
						if(p!=l[q]&&p!=q&&p!=r[q])
						{
							ans[0][++tot]=p;
							ans[1][tot]=q;
						}
					cnt=0;
					goto lableA;
				}
			for(i=1;i<n;i++,p=r[p])
				if(c[p]+c[l[p]]+c[r[p]]==1+4+16)
					break;
			if(i>=n)
				break;
			ans[0][++tot]=l[p];
			ans[1][tot]=r[p];
			l[r[p]]=l[p];
			r[l[p]]=r[p];
			p=r[p];
			n--,cnt--;
		}
		lableA:
		if(cnt)
			puts("0");
		else 
		{
			printf("%d\n",m-3);
			for(int i=1;i<=tot;i++)
				printf("%d %d\n",ans[0][i],ans[1][i]);
		}
	}
}
