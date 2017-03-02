#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
void gen()
{
    ofstream fout("a.in");
    int n=100000;
    fout<<n<<endl;
    for(int i=1;i<=n;i++)
        fout<<rand()%1000000+1<<" ";
    fout<<endl;
    fout.close();
}
int main()
{
    system("g++ 2230.cpp -o 2230 -g");
    system("g++ 2230_.cpp -o 2230_ -g");
    srand(time(NULL));
    rand();
    int cnt=0;
    while(true)
    {
        gen();
        system("./2230<a.in>a.out");
        system("./2230_<a.in>b.out");
        if(system("diff a.out b.out -bw > /dev/null"))
        {
            cout<<"WA"<<endl;
            break;
        }
        cout<<++cnt<<" AC\n";
    }
}
