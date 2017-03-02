#include <bits/stdc++.h>
using namespace std;
#define N 2000010
#define ll long long
char s[N];
int ln,n,en[210];
struct SAM
{
    vector<int>vec[N];
    int trs[N][26],fa[N],len[N],size[N],cnt,last;
    void init(){cnt=last=1;}
    void insert(int x)
    {
        int p=last,np,q,nq;
        if(trs[p][x])
        {
            q=trs[p][x];
            if(len[q]==len[p]+1)last=q;
            else
            {
                fa[nq=++cnt]=fa[q];
                fa[q]=nq;
                memcpy(trs[nq],trs[q],sizeof(trs[q]));
                len[nq]=len[p]+1;last=nq;
                for(;trs[p][x]==q;p=fa[p])trs[p][x]=nq;
            }
        }
        else
        {   
            np=++cnt;
            last=np;len[np]=len[p]+1;
            for(;p&&!trs[p][x];p=fa[p])trs[p][x]=np;
            if(!p)fa[np]=1;
            else
            {
                q=trs[p][x];
                if(len[q]==len[p]+1)fa[np]=q;
                else
                {
                    fa[nq=++cnt]=fa[q];
                    fa[q]=fa[np]=nq;
                    memcpy(trs[nq],trs[q],sizeof(trs[q]));
                    len[nq]=len[p]+1;
                    for(;trs[p][x]==q;p=fa[p])trs[p][x]=nq;
                }
            }
        }
        size[last]++;
    }
    void dfs(int x)
    {
        for(int i=0,t;i<vec[x].size();i++)
            dfs(t=vec[x][i]),size[x]+=size[t];
    }
    void work()
    {
        for(int i=1;i<=cnt;i++)
            vec[fa[i]].push_back(i);
        dfs(1);     
    }
}sam;
int main()
{
    //freopen("tt.in","r",stdin);
    sam.init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        ln=strlen(s+1);sam.last=1;
        for(int j=ln;j>=1;j--)
            sam.insert(s[j]-'a');
        en[i]=sam.last;
    }
    sam.work();
    for(int i=1;i<=n;i++)
        printf("%d\n",sam.size[en[i]]);
    return 0;
}
