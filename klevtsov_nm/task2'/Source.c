#include <stdio.h>
#include <locale.h>

//Проверка символа на принадлежность ко мн-ву чисел.
int isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

//Проверка символа на пренадлежность к алфавиту.
int isWord(char c)
{
	//Русские символы кодируются 2мя байтами в UTF-8. Робить не так як треба.
	return (/*(c >= 'А' && c <= 'я')*/c < 0 || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

//Проверка символа на не принадлежность к символам разделения.
int isNotSeparation(char c)
{
	return (c != ' ' && c != '\t' && c != '\n');
}

void cnt()
{
	setlocale(LC_ALL, "Russian");
	char c;
	int qtWords, qtNums;
	int flag;
	qtWords = qtNums = 0; 
	printf("Введите строку, в которой требуется найти кол-во слов и чисел.\n");

	do
	{
		do { c = getchar(); } while (c == ' ' || c == '\t');

		//Существует последовательность одиннаковых символов: flag = 1, иначе 0.
		flag = 1;
		if (c == '\n')
			break;

		if (isDigit(c))
		{
			do
			{
				c = getchar();
				if (!isDigit(c) && isNotSeparation(c))
					flag = 0;
			} while (isNotSeparation(c));

			if (flag)
				qtNums++;
		}
		else if (isWord(c))
		{
			do
			{
				c = getchar();
				if (!isWord(c) && isNotSeparation(c))
					flag = 0;
			} while (isNotSeparation(c));

			if (flag)
				qtWords++;
		}
		else
			do { c = getchar(); } while (isNotSeparation(c));
	} while (c != '\n');
	printf("Количество слов: %d.\nКоличество чисел: %d.\n", qtWords, qtNums);
}

int main()
{
	int variable;
	cnt();

	while (!0)
	{
		printf("Попробовать снова?\n");
		printf("1)Да.\n");
		printf("2)Нет.\n");
		scanf_s("%d", &variable); getchar();
		if (variable == 1)
			cnt();
		else
			break;
	}
	return 0;
}