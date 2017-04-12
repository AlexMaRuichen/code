
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

void gen() {
	int n = 100000;
	FILE *p = fopen("tt.in","w");
	fprintf(p,"%d\n",n);
	for(int i=1;i<=n;++i) {
		fprintf(p,"%d ",rand()%20000-10000);
	}
	fprintf(p,"\n");
	for(int i=2;i<=n;++i) {
		fprintf(p,"%d %d\n",rand()%(i-1)+1,i);
	}
	int q = 100000;
	fprintf(p,"%d\n", q);
	for(int i=1;i<=q;++i) {
		int opt = rand() & 1;
		if(opt) {
			fprintf(p,"%d %d %d\n",opt, rand() %n+1, rand() %n+1);
		}
		else fprintf(p,"%d %d %d %d\n", opt+2,rand()%n+1,rand()%n+1, rand()%10-5);
	}
	fclose(p);
}

int main() {
	system("g++ std.cpp -o std.exe -Wall");
	system("g++ b.cpp -o b.exe -g -Wall");
	while(1) {
		gen();
		system("b.exe < tt.in > tt.out");
		system("std.exe < tt.in > tt.ans");
		if(system("fc tt.out tt.ans > nul")) {
			puts("Wa");
			return 0;
		}
		static int cnt = 0;
		cout << ++ cnt << endl;
	}
}