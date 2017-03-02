#include <cstdio>
int main()
{
	int a, b, c, N;
	char buf[1<<10];
	//read asd*f/-zxcBvwwPezas%^&.zxOIUH8132187521235468215
/*	scanf("%*[^0-9]%[0-9]", buf);
	puts(buf);

	//read [ 11 :20 :41]
	scanf("%*[^0-9]%d%*[^0-9]%d%*[^0-9]%d", &a, &b, &c);
	printf("%d:%d:%d\n", a, b, c);

	//read Lily11Andy12Dadi51Mami42*/
	N = 4;
	while(N--)
	{
		scanf("%*[a-zA-Z]%d", &a);
		printf("%d\n", a);
	}
}
