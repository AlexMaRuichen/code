#include <bits/stdc++.h>
using namespace  std;
typedef long long ll;
const int inf=2e4;
int Rand()
{
	int x=rand()%50000+50000,y=rand()%1000+1;
	return x*y;
}
int v[1100][1100];
void data()
{
	FILE *f=fopen("t.in","w");
	memset(v,0,sizeof(v));
	int n=1000,m=0;
	fprintf(f,"%d\n",n);
	for(int i=1;i<=n&&m<=inf;++i)
		for(int j=i+1;j<=n&&m<=inf;++j)
			v[i][j]=rand()%2,m+=v[i][j];
	fprintf(f,"%d\n",m);
	for(int i=1;i<=n;++i)
		fprintf(f,"%d\n",Rand());
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			if(v[i][j])
				fprintf(f,"%d %d %d\n",i,j,Rand());
	int q=rand()%20000+1;
	fprintf(f,"%d\n",q);
	for(int i=1;i<=q;++i)
		fprintf(f,"%d %d\n",rand()%n+1,rand()%n+1);
	fprintf(f,"0 0\n");
	fclose(f);
}
int Case;
int main()
{
	srand(time(NULL));
	rand();
	system("g++ d.cpp -o d -g");
	system("g++ std.cpp -o std -g");
	while(++Case)
	{
		data();
		system("d<t.in>d.out");
		system("std<t.in>std.out");
		printf("Case #%d:",Case);
		if(system("fc d.out std.out > nul")==1)
		{
			puts("WA!!!!!!!!!!");
			return 0;
		}
		puts("Accepted");
	}
}