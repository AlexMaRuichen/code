#include <stdio.h>
#define min(i,j) (i)<(j)?(i):(j)
unsigned char s[10000010];
int n,ans,t;
unsigned char ch,*p=s+1;;
int main()
{
	fread(&n,4,1,stdin);
	fread(s,1,n+1,stdin);
	register int i,j,k;
	for(i=1,j=2,k=0;i<=n&&j<=n&&k<=n;)
	{
		t=s[i+k>n?i+k-n:i+k]-s[j+k>n?j+k-n:j+k];
		if(!t)
			++k;
		else
		{
			t>0?i+=k+1:j+=k+1;
			i==j?++j,k=0:k=0;
		}
	}
	ans=min(i,j);
	fwrite(s+ans,1,n-ans+1,stdout);
	fwrite(s+1,1,ans-1,stdout);
	fwrite("\n",1,1,stdout);
}

