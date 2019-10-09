#include <stdio.h>
#define m(a, b) (((a) > (b)) ? (a) : (b))

int main()
{
	int a, b;
	scanf_s("%d %d", &a, &b);
	printf("%d", m(a, b));
	return 0;
}