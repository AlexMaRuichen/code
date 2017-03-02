#include<map>  
#include<string>  
#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
#define M 1010  
using namespace std;  
struct point{  
    int x,y;  
    point(){}  
    point(int _,int __):x(_),y(__){}  
    point operator + (const point z) const  
    {  
        point re;  
        re.x=x+z.x;  
        re.y=y+z.y;  
        return re;  
    }  
    void Read()  
    {  
        scanf("%d%d",&x,&y);  
    }  
};  
struct picture{  
    point size;  
    char image[110][110];  
}pictures[110];  
struct entry{  
    point pos;  
    int file;  
    int layer;  
    bool operator < (const entry &x) const  
    {  
        return layer < x.layer;  
    }  
}entries[510];  
int max_x,max_y;  
int n,m,cnt;  
char ans[M][M];  
char s[M];  
string st;  
map<string,int>picture_file,entry_file;  
void Initialize()  
{  
    printf("Scenario #%d:\n",++cnt);  
    max_x=max_y=0;  
    memset(ans,' ',sizeof ans);  
    picture_file.clear();  
    entry_file.clear();  
}  
void Draw(const entry &e)  
{  
    int i,j;  
    const picture &p=pictures[e.file];  
    max_x=max(max_x,e.pos.x+p.size.x-1);  
    max_y=max(max_y,e.pos.y+p.size.y-1);  
    for(i=0;i<p.size.x;i++)  
        for(j=0;j<p.size.y;j++)  
            if(p.image[i][j]!='.')  
                ans[e.pos.x+i][e.pos.y+j]=p.image[i][j];  
}  
void Output()  
{  
    int i,j;  
    for(i=0;i<=max_x;i++)  
    {  
        ans[i][max_y+1]=0;  
        puts(ans[i]);  
    }  
    puts("");  
}  
inline void Kill_Char(int x)  
{  
    char c;  
    for(;x;x--)  
        do c=getchar(); while(c==' '||c=='\t'||c=='\n'||c=='\r');  
}  
char Get_Char()  
{  
    char c;  
    do c=getchar(); while(c==' '||c=='\t'||c=='\n'||c=='\r');  
    return c;  
}  
inline void Kill_Colon()  
{  
    int k=strlen(s+1);  
    if(s[k]==';')  
        s[k]=0;  
    else  
        Kill_Char(1);  
}  
int main()  
{  
      
    //freopen("1.txt","w",stdout);  
      
    int T,i,j,k;  
    point temp;  
    char c;  
    for(cin>>T;T;T--)  
    {  
        Initialize();  
        cin>>n;  
        for(i=1;i<=n;i++)  
        {  
            cin>>st;  
            picture_file[st]=i;  
            pictures[i].size.Read();  
            getchar();  
            for(j=0;j<pictures[i].size.x;j++)  
                scanf("%s",pictures[i].image[j]);  
        }  
        cin>>m;  
        for(i=1;i<=m;i++)  
        {  
            Kill_Char(1);  
            st.clear();  
            while(c=Get_Char(),c!='{')  
                st+=c;  
            entry_file[st]=i;  
            Kill_Char(6);  
            scanf("%d",&temp.y);  
            Kill_Char(9);  
            scanf("%d",&temp.x);  
            Kill_Char(12);  
            entries[i].pos=point(-1,-1);  
            s[0]=Get_Char();  
            if(s[0]=='a')  
                entries[i].pos=temp,Kill_Char(8);  
            else  
            {  
                Kill_Char(8);  
                scanf("%s",s+1);  
                Kill_Colon();  
                int fa=entry_file[string(s+1)];  
                entries[i].pos=entries[fa].pos+temp;  
            }  
            Kill_Char(5);  
            scanf("%s",s+1);  
            Kill_Colon();  
            entries[i].file=picture_file[string(s+1)];  
            Kill_Char(6);  
            scanf("%s",s+1);  
            Kill_Colon();  
            sscanf(s+1,"%d",&entries[i].layer);  
            Kill_Char(1);  
        }  
        stable_sort(entries+1,entries+m+1);  
        for(i=1;i<=m;i++)  
            Draw(entries[i]);  
        Output();  
    }  
}  
