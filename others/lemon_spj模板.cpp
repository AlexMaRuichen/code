#include <bits/stdc++.h>
using namespace std;
#define N 110000
FILE* fin;//标准输入
FILE* fout;//用户输出
FILE* fstd;//标准输出
FILE* fscore;//得分文件
FILE* freport;//报告文件
int n,c;
int num[N],a[N];
void quit(int x)
{
	fprintf(fscore,"%d",x);
	fclose(fin);
	fclose(fout);
	fclose(fstd);
	fclose(fscore);
	fclose(freport);
	exit(0);
}
void check(int x)
{
	if(a[x]<1||a[x]>c||--num[a[x]]<0)
	{
		fprintf(freport,"输出的第%d个数不合法",x);
		quit(0);
	}
}
int main(int argc,char*argv[])
{
	fin=fopen(argv[1],"r");//标准输入
	fout=fopen(argv[2],"r");//用户输出
	fstd=fopen(argv[3],"r");//标准输出
	fscore=fopen(argv[5],"w");//得分文件
	freport=fopen(argv[6],"w");//报告文件
	
	fscanf(fin,"%d%d",&n,&c);
	for(int i=1;i<=c;i++)
		fscanf(fin,"%d",&num[i]);
	for(int i=1;i<=n;i++)
	{
		if(fscanf(fout,"%d",&a[i])==EOF)
		{
			fprintf(freport,"你的输出小于n个数");
			quit(0);
		}
	}
	for(int i=1;i<=n/2;i++)
	{
		if(a[i*2]==a[i*2-1])
		{
			fprintf(freport,"第%d行的两个数相等",i);
			quit(0);
		}
		check(i*2);
		check(i*2-1);
	}
	fprintf(freport,"答案正确");
	quit(10);
	return 0;
}
