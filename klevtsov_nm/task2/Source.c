#include <stdio.h>
#include <time.h>
#include <locale.h>

//Пользователь против компьютера.
void userPcVersus()
{
	int userAlleged, userQt;
	int pcGuessed, pcAlleged, pcQt;
	int lLim, rLim;
	char symb;
	lLim = 1; rLim = 1000;
	pcQt = userQt = 0;
	pcGuessed = rand() % 1000 + 1;


	//Инициализация локальной переменной "userAlleged".
	printf("Введите число от 0 до 1000: ");
	scanf_s("%d", &userAlleged);
	if (userAlleged < pcGuessed)
		printf("Загаданное число больше.\n");
	else if (userAlleged > pcGuessed)
		printf("Загаданное число меньше.\n");
	else
		printf("Вы угадали.\n");
	userQt++;

	//Инициализация локальной переменной "symb".
	pcAlleged = (lLim + rLim) / 2;
	printf("Это %d?(Введите, если загаданное больше: \">\", меньше: \"<\", равно: \"=\")\n", pcAlleged);
	getchar(); scanf_s("%c", &symb);
	if (symb == '>')
	{
		lLim = pcAlleged;
	}
	else if (symb == '<')
	{
		rLim = pcAlleged;
	}
	else
	{
		printf("Число угаданно. ");
	}
	pcQt++;

	while ((symb != '=') || (pcGuessed != userAlleged))
	{
		if (pcGuessed != userAlleged);
		{
			printf("Введите число от 0 до 1000: ");
			scanf_s("%d", &userAlleged);
			if (userAlleged < pcGuessed)
				printf("Загаданное число больше.\n");
			else if (userAlleged > pcGuessed)
				printf("Загаданное число меньше.\n");
			else
				printf("Вы угадали.\n");
			userQt++;
		}
		if (symb != '=')
		{
			pcAlleged = (lLim + rLim) / 2;
			printf("Это %d?(Введите, если загаданное больше: \">\", меньше: \"<\", равно: \"=\")\n", pcAlleged);
			getchar(); scanf_s("%c", &symb);
			if (symb == '>')
			{
				lLim = pcAlleged;
			}
			else if (symb == '<')
			{
				rLim = pcAlleged;
			}
			else
			{
				printf("Число угаданно.\n");
			}
			pcQt++;
		}
	}

	if (pcQt < userQt)
		printf("Победил компьютер, угадав число за %d ход(а/ов).\n", pcQt);
	else if (pcQt > userQt)
		printf("Победил пользователь, угадав число за %d ход(а/ов).\n", userQt);
	else
		printf("Как говорится: \"Победила дружба\".\n");
}

//Пользователь отгадывает.
void userGuesses()
{
	int  guessed, alleged, qt;
	qt = 0;
	guessed = rand() % 1000 + 1;

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

	printf("Количество попыток - %d.\n", qt);
}

//Компьютер отгадывает.
void computerGuesses()
{
	int alleged, qt;
	int lLim, rLim;
	char symb;
	lLim = 1; rLim = 1000;
	qt = 0;

	do
	{
		alleged = (lLim + rLim) / 2;
		printf("Это %d?(Введите, если загаданное больше: \">\", меньше: \"<\", равно: \"=\")\n", alleged);
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

	printf("Количество попыток - %d.\n", qt);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int variable;

	//Выбор режима программы "Угадай число".
	printf("Выберите режим программы:\n");
	printf("0)Выход.\n");
	printf("1)Режим №1 (компьютер загадывает число).\n");
	printf("2)Режим №2 (пользователь загадывает число).\n");
	printf("2)Режим №3 (кто быстрее пользователь или компьютер).\n");
	scanf_s("%d", &variable);
	switch (variable)
	{
	case 0:
		exit();
		break;
	case 1:
		userGuesses();
		break;
	case 2:
		computerGuesses();
		break;
	case 3:
		userPcVersus();
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