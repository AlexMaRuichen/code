#include<iostream>  
#include<cstdio>  
#include<map>  
#include<cstring>  
#include<cmath>  
#include<vector>  
#include<algorithm>  
#include<set>  
#include<string>  
#include<queue>  
#define inf 100000005  
#define M 40  
#define N 200015  
#define maxn 300005  
#define eps 1e-10  
#define zero(a) fabs(a)<eps  
#define Min(a,b) ((a)<(b)?(a):(b))  
#define Max(a,b) ((a)>(b)?(a):(b))  
#define pb(a) push_back(a)  
#define mp(a,b) make_pair(a,b)  
#define mem(a,b) memset(a,b,sizeof(a))  
#define LL unsigned long long  
#define MOD 1000000007  
#define lson step<<1  
#define rson step<<1|1  
#define sqr(a) ((a)*(a))  
#define Key_value ch[ch[root][1]][0]  
#define test puts("OK");  
#pragma comment(linker, "/STACK:1024000000,1024000000")  
using namespace std;  
struct SAM  
{  
    SAM *pre,*son[26];  
    int len,nl,ml;  
}*root,*tail,que[N],*b[N];  
int tot=0;  
char str[N/2];  
int cnt[N/2];  
void add(int c,int l)  
{  
    SAM *p=tail,*np=&que[tot++];  
    np->len=np->ml=l;tail=np;  
    while(p&&p->son[c]==NULL) p->son[c]=np,p=p->pre;  
    if(p==NULL) np->pre=root;  
    else  
    {  
        SAM *q=p->son[c];  
        if(p->len+1==q->len) np->pre=q;  
        else  
        {  
            SAM *nq=&que[tot++];  
            *nq=*q;  
            nq->len=nq->ml=p->len+1;  
            np->pre=q->pre=nq;  
            while(p&&p->son[c]==q) p->son[c]=nq,p=p->pre;  
        }  
    }  
}  
int main()  
{  
   // freopen("1.in","r",stdin);  
    tail=root=&que[tot++];  
    scanf("%s",str);int l=strlen(str);  
    for(int i=0;str[i];i++) add(str[i]-'a',i+1);  
    for(int i=0;i<tot;i++) cnt[que[i].len]++;  
    for(int i=1;i<=l;i++) cnt[i]+=cnt[i-1];  
    for(int i=0;i<tot;i++) b[--cnt[que[i].len]]=&que[i];  
    while(scanf("%s",str)!=EOF)  
    {  
        SAM *p=root;  
        for(int i=0,l=0;str[i];i++)  
        {  
            int c=str[i]-'a';  
            if(p->son[c]) {l++;p=p->son[c];}  
            else  
            {  
                while(p&&p->son[c]==NULL) p=p->pre;  
                if(p==NULL) {l=0;p=root;}  
                else {l=p->len+1;p=p->son[c];}  
            }  
            if(l>p->nl) p->nl=l;  
        }  
        for(int i=tot-1;i>=0;i--)  
        {  
            p=b[i];  
            if(p->nl<p->ml) p->ml=p->nl;  
            if(p->pre&&p->pre->nl<p->nl) p->pre->nl=p->nl;  
            p->nl=0;  
        }  
    }  
    int ans=0;  
    for(int i=0;i<tot;i++) if(que[i].ml>ans) ans=que[i].ml;  
    printf("%d\n",ans);  
    return 0;  
}  
