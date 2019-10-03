#include <stdio.h>
#include <locale.h>

char scroll()
{
	char c;

	do { c = getchar(); } while ((c != ' ') && (c != '\t') && (c != '\n'));

	return c;
}

int main()
{
	setlocale(LC_ALL, "Rus");

	char c;
	int qtWords, qtNums;
	int variable;

	qtWords = qtNums = 0;

	printf("Введите строку, в которой требуется найти кол-во слов и чисел.\n");

	do
	{
		c = getchar();

		if ((c >= '0') && (c <= '9'))
			qtNums++;
		else
			qtWords++;

		c = scroll();

	} while (c != '\n');

	printf("Количество слов: %d.\nКоличество чисел: %d.\n", qtWords, qtNums);

	printf("Попробовать снова?\n");
	printf("1)Да.\n");
	printf("2)Нет.\n");
	scanf_s("%d", &variable);
	if (variable == 1)
	{
		getchar();
		main();
	}

	return 0;
}