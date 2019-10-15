#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#define True 1

//Получение цифры неповторяющейся с предыдущими.
int get_element(int guessed[], int n, int i)
{
	int digit, flag = 1;
	while (flag)
	{
		digit = rand() % 10;
		for (int j = 0; j < i; j++)
		{
			if (digit == guessed[j])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
		{
			flag = 1;
			continue;
		}
		else
			flag = 0;
	}
	return digit;
}

//Если имеются повторяющиеся элементы - "1", иначе - "0".
int are_there_duplicates(int alleged[], int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			if (alleged[i] == alleged[j])
				return 1;
	return 0;
}

//Проверка на принадлежность к, состоящему из цифр от 1 до 9, множеству.
int is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

//Проверка символа на принадлежность к алфавиту.
int is_word(char c)

{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

//Введено ни число, ни стоп-слово - "0", введено стоп-слово - "-1", введено не n-значное число - "-2"
int get_entered(n)
{
	int result = 0, k = n;
	char c[20];
	int l_lim = 0, r_lim = 0; //Диапазон, в котором должно находится введенное число.
	gets(c);
	if (is_digit(c[0])) //Проверка на цифру.
	{
		for (int i = 0; i < k; i++) //Считаем, что введено число, если в строке первые n элементов - цифры.
		{
			if (is_digit(c[i]))
			{
				result += (c[i] - '0') * pow(10, --n);
				l_lim += pow(10, n);
				r_lim += 9 * pow(10, n);
			}
			else
				return 0;
		}
		if (result >= l_lim && result <= r_lim)
			return result;
		else
			return -2;
	}
	else if (!(strcmp(c, "stop")))
	{
		return -1;
	}
	else
		return 0;
}

void bulls_and_cows(int n)
{
	int alleged[5], guessed[5];
	int entered, bulls, cows, cnt = 0, flag = 1;

	//Компьютер "задумывает" n-значное число с неповторяющимися цифрами.
	guessed[0] = rand() % 9 + 1;
	for (int i = 1; i < n; ++i)
	{
		guessed[i] = get_element(guessed, n, i);
	}

	//Вычисление "коров" и "быков".
	while (True)
	{
		bulls = cows = 0;
		printf("Введите %d-значное число с неповторяющимися цифрами или \"stop\" для того, чтобы сдаться.\n", n);
		entered = get_entered(n);
		if (entered == -1)
		{
			printf("Вы сдались.\n");
			flag = 0;
			break;
		}
		else if (entered == 0)
		{
			printf("Неверный ввод. Попробуйте еще раз.\n");
			continue;
		}
		else if (entered == -2)
		{
			printf("Введено не %d-значное число. Попробуйте еще раз.\n", n);
			continue;
		}

		for (int i = n - 1; i >= 0; i--)
		{
			alleged[i] = entered % 10;
			entered = entered / 10;
		}

		if (are_there_duplicates(alleged, n))
		{
			printf("Введено число с повторяющимися цифрами!\n");
			continue;
		}
		
		for (int i = 0; i < n; i++)
		{
			if (alleged[i] == guessed[i])
				bulls++;
			else
				for (int j = 0; j < n; j++)
					if (alleged[i] == guessed[j])
						cows++;
		}
		if (bulls == n)
			break;
		else
			printf("Быков: %d.\nКоров: %d.\n", bulls, cows);
		cnt++;
	}
	if (flag)
		printf("Вы угадали за %d попыток! Моё уважение.\n", cnt);
}

//Выбор длины загадываемого числа.
void set_length()
{
	int n;
	printf("Выберите длину загадываемого числа(от 2 до 5), если же хотите выйти из программы введите \"0\": ");
	scanf_s("%d", &n); getchar();
	switch (n)
	{
	case 0:
		exit();
	case 2:case 3:case 4:case 5:
		bulls_and_cows(n);
		break;
	default:
		printf("Недопустимые данные.\n");
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int variable;
	
	set_length();

	while (True)
	{
		printf("Попробовать снова?\n");
		printf("1)Да.\n");
		printf("2)Нет.\n");
		scanf_s("%d", &variable);
		if (variable == 1)
			set_length();
		else
			break;
	}
	return 0;
}