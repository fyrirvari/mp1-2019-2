#include <stdio.h>
#include <time.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");

	int variable, guessed, alleged, qt;
	char symb;

	srand(time(NULL));

	qt = 0;

	printf("Выберите режим программы:\n");
	printf("1)Режим №1 (компьютер загадывает число).\n");
	printf("2)Режим №2 (пользователь загадывает число).\n");
	scanf_s("%d", &variable);
	
	switch (variable)
	{
	case 1:
		guessed = rand() % 1001;

		do
		{
			printf("Введите число от 0 до 1000: ");
			scanf_s("%d", &alleged);

			if (alleged < guessed)
				printf("Загаданное число больше.\n");
			else if (alleged > guessed)
				printf("Загаданное число меньше.\n");
			else
				printf("Угадали.\n");

			qt++;
		} while (alleged != guessed);

		break;
	case 2:
		do
		{
			//Сделать с помощью бинарного поиска!
			alleged = rand() % 1001;
			printf("Это %d?(Больше >, меньше <, равно =)", alleged);
			scanf_s("%c", &symb);
			qt++;
		} while (symb != '=');

		break;
	default:
		printf("Не выбран режим.\n");
		break;
	}

	if ((variable == 1) || (variable == 2)) 
		printf("Количество попыток - %d.\n", qt);

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