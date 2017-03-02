#include <stdio.h>
const int maxn=1e5+10;
int fa[maxn],id[maxn];
int n;
char c[10];
int main ()
 {
    scanf("%d",&n);
    fa[0]=-1;
    id[0]=-1;
    for (int i = 1; i <= n; i++)
	{
    	static int k;
		scanf("%s",c);
        if(c[0]=='a')
		{
        	scanf("%d",&k);
            fa[i]=i-1;
            id[i]=k;
        }
        if(c[0]=='s')
		{
            fa[i]=fa[fa[i-1]];
            id[i]=id[fa[i-1]];
        }
        if(c[0]=='t')
		{
            scanf("%d", &k);
            fa[i]=fa[k-1];
            id[i]=id[k-1];
        }
        printf("%d\n",id[i]);
    }
    return 0;
}
