#include <stdio.h>
#include <ctype.h>
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
int main()
{
	int n,ans=0;
	int a[100001]={};
	n=read();
	register int i;
	for(i=1;i<=n;i++)
		a[i]=read();
	for(i=1;i<=n&&a[i]==a[i+1];i++);
	bool f=a[i]<a[i+1];
	++i;
	for(;i<=n;i++)
		if(f&&a[i]<a[i-1])
			f=false,++ans;
		else if(!f&&a[i]>a[i-1])
			f=true,++ans;
	printf("%d\n",ans+2);
}
