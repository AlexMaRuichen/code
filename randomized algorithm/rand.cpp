#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;
string s[11];
int main()
{
	srand(time(NULL));
	rand();
	s[1]="kdt";
	s[2]="network flow";
	s[3]="blossom";
	s[4]="AC automaton";
	s[5]="Tree partition";
	s[6]="Math";
	s[7]="LCT";
	s[8]="Chairtree";
	s[9]="Presistent Trie";
	s[10]="Multidimensional data structure";
	for(int i=2;i<=10;i++)
		swap(s[i],s[rand()%(i-1)+1]);
	cout<<s[1]<<endl;
}
