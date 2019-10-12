#include <stdio.h>
#define m(a, b) (((a) > (b)) ? (a) : (b))

int main()
{
	char str[4];
	gets(str);
	printf("%s", str);
	return 0;
}