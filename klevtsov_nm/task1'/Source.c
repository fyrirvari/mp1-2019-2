#include <stdio.h>
#include <math.h>
#include <string.h>
#include <locale.h>

//Разность кодов символов и чисел.
int difWord, difNum;

//Функции, позволяющие понять попадет ли фигура на данную клетку.
int king(char word1, char word2, int num1, int num2)
{
	if (((difWord == 1) && (difNum <= 1)) || ((difWord <= 1) && (difNum == 1)))
		return 1;
	else
		return 0;
}

int queen(char word1, char word2, int num1, int num2)
{
	if ((word1 == word2) || (num1 == num2) || (difWord == difNum))
		return 1;
	else
		return 0;
}

int rook(char word1, char word2, int num1, int num2)
{
	if ((word1 == word2) || (num1 == num2))
		return 1;
	else
		return 0;
}

int phant(char word1, char word2, int num1, int num2)
{
	if (difWord == difNum)
		return 1;
	else
		return 0;
}	

int horse(char word1, char word2, int num1, int num2)
{
	if (((difWord == 1) && (difNum == 2)) || ((difWord == 2) && (difNum == 1)))
		return 1;
	else
		return 0;
}

//Выводы на экран списка фигур способных попасть на данную клетку.
void outPut(char figure[7])
{
	printf("В эту клетку может попасть %s.\n", figure);
}

//Вывод на экран может или не может фигура попасть из клетки в клетку. 
void canMoveOut(char figure[7], char word1, char word2, int num1, int num2, int var)
{
	if (var == 1)
	{
		printf("%s может за один ход перейти из клетки %c%d в клетку %c%d.\n", figure, word1, num1, word2, num2);
	}
	else
	{
		printf("%s не может за один ход перейти из клетки %c%d в клетку %c%d.\n", figure, word1, num1, word2, num2);
		if (king(word1, word2, num1, num2))
			outPut("Король");
		if (queen(word1, word2, num1, num2))
			outPut("Ферзь");
		if (rook(word1, word2, num1, num2))
			outPut("Ладья");
		if (phant(word1, word2, num1, num2))
			outPut("Слон");
		if (horse(word1, word2, num1, num2))
			outPut("Конь");
	}
}

void main()
{
	setlocale(LC_ALL, "Rus");

	char K1[3], K2[3];
	char word1, word2;
	int num1, num2;
	int variable;

	//Ввод клеток.
	do
	{
		printf("Введите клетку 1 (Буква от A до H, цифра от 1 до 8): ");
		scanf("%s", K1);
		printf("Введите клетку 2 (...): ");
		scanf("%s", K2);
		word1 = K1[0];
		word2 = K2[0];
		num1 = (int)K1[1] - 48;
		num2 = (int)K2[1] - 48;
		if ((word1 < 'A') || (word1 > 'H') || (num1 < 1) || (num1 > 8) || (word2 < 'A') || (word2 > 'H') || (num2 < 1) || (num2 > 8))
		{
			printf("Некорректные данные.\n");
		}
	} while ((word1 < 'A') || (word1 > 'H') || (num1 < 1) || (num1 > 8) || (word2 < 'A') || (word2 > 'H') || (num2 < 1) || (num2 > 8));

	difWord = fabs((int)(word1) - (int)(word2));
	difNum = fabs(num1 - num2);

	//Выбор фигуры, для которой мы будем узнавать, попадет ли она на клеткую, а если не попадет, то вывод списка фигур, которые могут попасть на эту клетку.
	printf("Выберите фигуру:\n");
	printf("1)Король.\n");
	printf("2)Ферзь.\n");
	printf("3)Ладья.\n");
	printf("4)Слон.\n");
	printf("5)Конь.\n");
	scanf_s("%d", &variable);
	switch (variable)
	{
	case 1:
		if (king(word1, word2, num1, num2))
			canMoveOut("Король", word1, word2, num1, num2, 1);
		else
			canMoveOut("Король", word1, word2, num1, num2, 0);
		break;
	case 2:
		if (queen(word1, word2, num1, num2))
			canMoveOut("Ферзь", word1, word2, num1, num2, 1);
		else
			canMoveOut("Ферзь", word1, word2, num1, num2, 0);
		break;
	case 3:
		if (rook(word1, word2, num1, num2))
			canMoveOut("Ладья", word1, word2, num1, num2, 1);
		else
			canMoveOut("Ладья", word1, word2, num1, num2, 0);
		break;
	case 4:
		if (phant(word1, word2, num1, num2))
			canMoveOut("Слон", word1, word2, num1, num2, 1);
		else
			canMoveOut("Слон", word1, word2, num1, num2, 0);
		break;
	case 5:
		if (horse(word1, word2, num1, num2))
			canMoveOut("Конь", word1, word2, num1, num2, 1);
		else
			canMoveOut("Конь", word1, word2, num1, num2, 0);
		break;
	default:
		printf("Не допустимое значения варианта.\n");
		break;
	}

	printf("Узнать для других фигур и клеток?\n");
	printf("1)Да.\n");
	printf("2)Нет.\n");
	scanf_s("%d", &variable);
	if (variable == 1)
	{
		main();
	}
}