#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int maxa=30;
const int maxn=100;
int n,k,npos;
int cnt[maxa];
string adj[maxa][maxn];
string back[maxn];

bool check(int pos, string a)
{
    for(int i=0;i<cnt[pos];i++)
        if(adj[pos][i]==a)
            return true;
    return false;
}

int num(int pos1, int pos2)
{
    int total=1;
    for(int i=pos1;i<=pos2;i++)
        total*=cnt[i];
    return total;
}

string kth(int k)
{
    string s="";
    for(int i=0;i<npos;i++)
    {
        if(i>0)
            s=s+" ";
        s+=adj[i][k/num(i+1,npos-1)];
        k%=num(i+1,npos-1);
    }
    return s;
}

int before(string s)
{
    int total=0;
    for(int i=0;i<n;i++)
        if(back[i]<=s)
            total++;
    return total;
}

int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++)
    {
        string s;
        while(cin>>s)
            if(s=="no")
                break;
        int pos=0;
        s="";
        back[i]="";
        while(cin>>s)
        {
            if(s=="cow.")
                break;
            if(pos>0)
                back[i]+=" ";
            back[i]+=s;
            if(!check(pos,s))
            {
                adj[pos][cnt[pos]]=s;
                cnt[pos]++;
            }
            pos++;
        }
        npos=pos;
    }

    for(int pos=0;pos<npos;pos++)
     sort(adj[pos],adj[pos]+cnt[pos]);

    int K=k-1;
    while(K-before(kth(K))<k-1)
        K++;

    cout<<kth(K)<<endl;
}
