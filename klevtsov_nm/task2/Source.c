#include <stdio.h>
#include <time.h>
#include <locale.h>

//Пользователь отгадывает.
int userGuesses()
{
	int  guessed, alleged, qt;
	qt = 0;

	guessed = rand() % 1000 + 1;

	//Пользователь пытается отгдать загаданное компьютером число.
	do
	{
		printf("Введите число от 0 до 1000: ");
		scanf_s("%d", &alleged);

		if (alleged < guessed)
			printf("Загаданное число больше.\n");
		else if (alleged > guessed)
			printf("Загаданное число меньше.\n");
		else
			printf("Вы угадали.\n");

		qt++;
	} while (alleged != guessed);

	return qt;
}

//Компьютер отгадывает.
int computerGuesses()
{
	int  guessed, alleged, qt;
	int lLim, rLim;
	char symb;

	lLim = 1; rLim = 1000;
	qt = 0;

	do
	{
		alleged = (lLim + rLim) / 2;

		//Пользователь сообщает компьютеры в каких отношениях предлагаемое число с загаданным.
		printf("Это %d?(Загаданное больше: >, меньше: <, равно: =)\n", alleged);
		getchar(); scanf_s("%c", &symb);

		if (symb == '>')
		{
			lLim = alleged;
		}
		else if (symb == '<')
		{
			rLim = alleged;
		}
		else
		{
			printf("Число угаданно. ");
		}

		qt++;
	} while (symb != '=');

	return qt;
}

int main()
{
	setlocale(LC_ALL, "Rus");

	int variable, qt;
	
	srand(time(NULL));

	//Выбор режима программы "Угадай число".
	printf("Выберите режим программы:\n");
	printf("0)Выход.\n");
	printf("1)Режим №1 (компьютер загадывает число).\n");
	printf("2)Режим №2 (пользователь загадывает число).\n");
	scanf_s("%d", &variable);
	
	switch (variable)
	{
	case 0:
		exit();
		break;
	case 1:
		qt = userGuesses();
		printf("Количество попыток - %d.\n", qt);
		break;
	case 2:
		qt = computerGuesses();
		printf("Количество попыток - %d.\n", qt);
		break;
	default:
		printf("Не выбран режим.\n");
		break;
	} 

	printf("Попробовать снова?\n");
	printf("1)Да.\n");
	printf("2)Нет.\n");
	scanf_s("%d", &variable);
	if (variable == 1)
	{
		main();
	}

	return 0;
}