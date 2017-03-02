#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 100100
using namespace std;
int n;
long long ans;
char s[M];
namespace Suffix_Automaton{
    struct Sam{
        Sam *son[26],*parent;
        int max_dpt;
        Sam() {}
        Sam(int _):max_dpt(_) {}
    }mempool[M<<1],*C=mempool;
    Sam *root=new (C++)Sam(0),*last;
    void Extend(int x)
    {
        Sam *p=last;
        //if(p->son[x]&&p->son[x]->max_dpt==p->max_dpt+1)
        //  return ;
        Sam *np=new (C++)Sam(p->max_dpt+1);
        for(;p&&!p->son[x];p=p->parent)
            p->son[x]=np;
        if(!p)
            np->parent=root,ans+=np->max_dpt;
        else
        {
            Sam *q=p->son[x];
            if(p->max_dpt+1==q->max_dpt)
                np->parent=q,ans+=np->max_dpt-q->max_dpt;
            else
            {
                Sam *nq=new (C++)Sam(p->max_dpt+1);
                memcpy(nq->son,q->son,sizeof nq->son);
                nq->parent=q->parent;
                q->parent=nq;np->parent=nq;
                ans+=np->max_dpt-nq->max_dpt;
                for(;p&&p->son[x]==q;p=p->parent)
                    p->son[x]=nq;
            }
        }
        last=np;
    }
}
int main()
{
    using namespace Suffix_Automaton;
    int i,j;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        last=root;
        for(j=1;s[j];j++)
        {
            Extend(s[j]-'a');
            printf("%lld\n",ans);
        }
    }
    return 0;
}
