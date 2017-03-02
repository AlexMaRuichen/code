#include <stdio.h>
int main()
{
	int mod=2012,f[1010],l,ch,i,s;
	l=f[1]=1;
	for(ch=getchar();l>0&&(ch=='('||ch==')');ch=getchar())
	{
		s=ch=='('?1:-1;
		l+=s;
		for(i=s<0?1:l;i>=1&&i<=l;i-=s)
			f[i]=f[i-s]+f[i]>=mod?f[i-s]+f[i]-mod:f[i-s]+f[i];
		f[l+1]=0;
	}
	printf("%d\n",l==1?f[1]:0);
}

