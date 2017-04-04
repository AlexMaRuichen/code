#include <stdio.h>
#include <stdlib.h>
  
__attribute__((optimize(2))) inline char getc()
{
	static const int len = 1 << 15;
	static char buf[len], *s, *t;
	if (s == t)
	{
		t = (s = buf) + fread(buf, 1, len, stdin);
		if (s == t)
			return EOF;
	}
	return *s++;
}

__attribute__((optimize(2))) inline void read(register int &x)
{
	static char ch = getc();
	x = 0;
	while(ch < '0' && ch > 0)
		ch = getc();
	if (ch == -1)
		exit(0);
	while(ch >= '0')
		x = (x << 1) + (x << 3) + ch - '0', ch = getc();
}

__attribute__((optimize(2))) inline void out(register int &x)
{
	static char s[10];
	static int id;
	if (x == 0)
		putchar('0');
	else
	{
		id = 0;
		while (x)
			s[++id] = x % 10 + '0', x /= 10;
		while (id)
			putchar(s[id--]);	
	}
	putchar('\n');
}

__attribute__((optimize(2))) int main()
{
	int x;
	while (true)
	{
		read(x);
		out(__builtin_popcount(x));
	}
}