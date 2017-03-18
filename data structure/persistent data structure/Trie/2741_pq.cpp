#include<cmath>  
#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
#define M 13000  
#define ls son[0]  
#define rs son[1]  
using namespace std;  
struct Trie{  
    Trie *son[2];  
    int cnt;  
}*trie[M],**tree=trie+1,mempool[M*40],*C=mempool;  
int n,m,block,ans,a[M],s[120][M];  
inline Trie* New_Node(Trie*_,Trie*__,int ___)  
{  
    C->son[0]=_;  
    C->son[1]=__;  
    C->cnt=___;  
    return C++;  
}  
Trie* Build_Tree(Trie *p,int x,int pos)  
{  
    if(!pos)  
        return New_Node(0x0,0x0,p->cnt+1);  
    if(~x&pos)  
        return New_Node(Build_Tree(p->ls,x,pos>>1),p->rs,p->cnt+1);  
    else  
        return New_Node(p->ls,Build_Tree(p->rs,x,pos>>1),p->cnt+1);  
}  
int Get_Ans(Trie *l,Trie *r,int x,int pos)  
{  
    int num=x&pos?1:0;    
    if(!pos)    
        return 0;    
    if(r->son[!num]->cnt-l->son[!num]->cnt)    
        return pos + Get_Ans(l->son[!num],r->son[!num],x,pos>>1);    
    else    
        return Get_Ans(l->son[num],r->son[num],x,pos>>1);    
}  
int main()  
{  
      
    //freopen("xor.in","r",stdin);  
    //freopen("xor.out","w",stdout);  
      
    int i,j,x,y;  
    cin>>n>>m;  
    tree[-1]=New_Node(C,C,0);  
    tree[0]=Build_Tree(tree[-1],0,1<<30);  
    for(i=1;i<=n;i++)  
        scanf("%d",&a[i]),tree[i]=Build_Tree(tree[i-1],a[i]^=a[i-1],1<<30);  
    block=static_cast<int>(sqrt(n+1));  
    for(i=0;i*block<=n;i++)  
        for(j=i*block;j<=n;j++)  
            s[i][j]=max(Get_Ans(tree[i*block-1],tree[j],a[j],1<<30),j?s[i][j-1]:0);  
    for(i=1;i<=m;i++)  
    {  
        if(i==16)  
            ++i,--i;  
        scanf("%d%d",&x,&y);  
        x=((long long)x+ans)%n+1;y=((long long)y+ans)%n+1;  
        if(x>y) swap(x,y); --x;  
        int temp=x/block+1;  
        ans=s[temp][y];  
        for(temp=min(temp*block-1,y);temp>=x;--temp)  
            ans=max(Get_Ans(tree[x-1],tree[y],a[temp],1<<30),ans);  
        printf("%d\n",ans);  
    }  
}  
