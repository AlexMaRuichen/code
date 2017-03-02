#include <stdio.h>
#define id(x) (x=='B'?1:x=='E'?2:x=='S'?3:x=='I'?4:x=='G'?5:x=='O'?6:7)
char s[5];
int n;
int cnt[8][7];
long long ans;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        static char s[5];
        static int v;
        scanf("%s%d",s,&v);
        cnt[id(s[0])][(v%7+7)%7]++;
    }
    for(int B=0;B<7;B++)
    for(int E=0;E<7;E++)
    for(int S=0;S<7;S++)
    for(int I=0;I<7;I++)
    for(int G=0;G<7;G++)
    for(int O=0;O<7;O++)
    for(int M=0;M<7;M++)
        if((B+E+S+S+I+E)*(G+O+E+S)*(M+O+O)%7==0)
            ans+=cnt[1][B]*1ll*cnt[2][E]*cnt[3][S]*cnt[4][I]*cnt[5][G]*cnt[6][O]*cnt[7][M];
    printf("%lld\n",ans);
}
