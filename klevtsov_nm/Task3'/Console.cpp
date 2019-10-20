#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <memory.h>
#include <conio.h>
#include <math.h>
#include <string.h>

enum TColor {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
	DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
	LIGHTMAGENTA, YELLOW, WHITE
};

const int window_width = 90;
const int window_height = 30;
const int COUNT = 16 * 16;
SMALL_RECT window;
COORD buf;

struct button
{
	char title[50];
	bool state;
};

//-----------------------------------------------------------------------------
int wherex(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return -1;

	CONSOLE_SCREEN_BUFFER_INFO buf;

	GetConsoleScreenBufferInfo(Console, &buf);
	return buf.dwCursorPosition.X;
}

//-----------------------------------------------------------------------------
int wherey(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return -1;

	CONSOLE_SCREEN_BUFFER_INFO buf;

	GetConsoleScreenBufferInfo(Console, &buf);
	return buf.dwCursorPosition.Y;
}

//-----------------------------------------------------------------------------
COORD WhereXY(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { -1, -1 };
	if (!Console)
		return pos;

	CONSOLE_SCREEN_BUFFER_INFO buf;

	GetConsoleScreenBufferInfo(Console, &buf);
	return buf.dwCursorPosition;
}

//-----------------------------------------------------------------------------
void clrscr(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;
	COORD pos = buf.dwCursorPosition;
	ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

	int col = Attr;
	int width = buf.dwSize.X;
	int height = buf.dwSize.Y;

	COORD zpos;
	zpos.X = 0;
	zpos.Y = 0;
	SetConsoleCursorPosition(Console, zpos);

	FillConsoleOutputAttribute(Console, col, width * height, zpos, &Count);
	FillConsoleOutputCharacter(Console, ' ', width * height, zpos, &Count);
}

//-----------------------------------------------------------------------------
void gotoxy(int x, int y)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(Console, pos);
}

//-----------------------------------------------------------------------------
void textcolor(int color)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;
	COORD pos = buf.dwCursorPosition;
	ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

	int bk_col = Attr / 16;
	int col = color % 16;
	col = col + bk_col * 16;

	SetConsoleTextAttribute(Console, col);

	char ch;
	pos = WhereXY();
	ReadConsoleOutputCharacter(Console, &ch, 1, pos, &Count);
	printf("%c", ch);
	gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void textbackground(int color)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;
	COORD pos = buf.dwCursorPosition;
	ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

	int text_col = Attr % 16;
	int col = color % 16;
	col = color * 16 + text_col;

	SetConsoleTextAttribute(Console, col);

	char ch;
	pos = WhereXY();
	ReadConsoleOutputCharacter(Console, &ch, 1, pos, &Count);
	printf("%c", ch);
	gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void textattr(int color)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	SetConsoleTextAttribute(Console, color);

	DWORD Count;
	char ch;
	COORD pos = WhereXY();
	ReadConsoleOutputCharacter(Console, &ch, 1, pos, &Count);
	printf("%c", ch);
	gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void setwindow(int width, int height)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	SMALL_RECT rect;
	rect.Left = 0;
	rect.Right = width - 1;
	rect.Top = 0;
	rect.Bottom = height - 1;
	COORD size;
	size.X = width;
	size.Y = height;
	SetConsoleWindowInfo(Console, true, &rect);
	//  printf("%d %d %d %d", rect.Left, rect.Top, rect.Right, rect.Bottom);
	SetConsoleScreenBufferSize(Console, size);
	//  printf("%d %d", size.X, size.Y);
}

//-----------------------------------------------------------------------------
void SetWindow(SMALL_RECT rect, COORD size)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	SetConsoleScreenBufferSize(Console, size);
	SetConsoleWindowInfo(Console, true, &rect);
}

//-----------------------------------------------------------------------------
void GetWindow(SMALL_RECT *rect, COORD *size)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	*rect = buf.srWindow;
	size->X = buf.dwSize.X;
	size->Y = buf.dwSize.Y;
}

//-----------------------------------------------------------------------------
void HideCursor(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_CURSOR_INFO buf;
	GetConsoleCursorInfo(Console, &buf);
	buf.bVisible = false;
	SetConsoleCursorInfo(Console, &buf);
}

//-----------------------------------------------------------------------------
void ShowCursor(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_CURSOR_INFO buf;
	GetConsoleCursorInfo(Console, &buf);
	buf.bVisible = true;
	SetConsoleCursorInfo(Console, &buf);
}

//-----------------------------------------------------------------------------

void clrpart(int x, int y, int length, int str)
{
	textattr(LIGHTGRAY);
	for (int i = 0; i < str; i++)
	{
		for (int j = 0; j < length; j++)
		{
			gotoxy(x + j, y + i);
			printf(" ");
		}
	}
}

//Адаптировать кнопки после нажатия на нужные клавишы.
void appropriate(button button[], int n, int margin_left, int margin_top)
{
	int button_width = 25;
	char str[50];
	for (int i = 0; i < n; i++)
	{
		gotoxy(margin_left + 1, margin_top + 4 * i + 1);
		if (button[i].state)
		{
			textcolor(BLACK); 
			textbackground(RED);
		}
		else
		{
			textcolor(BLACK); 
			textbackground(YELLOW);
		}
		for(int k = 0; k < 3; k++)
		{
			gotoxy(margin_left + 1, margin_top + k + 4 * i + 1);
			strcpy(str, "");
			strcat(str, " ");
			if (k == 1)
			{
				strcat(str, button[i].title);
				for (int j = 1 + strlen(button[i].title); j < button_width; j++)
					strcat(str, " ");
			}
			else
				for (int j = 1; j < button_width; j++)
					strcat(str, " ");
			puts(str);
		}
	}
}

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
int get_entered(int n)
{
	int result = 0, k = n;
	char ch;
	char str[50];
	int l_lim = 0, r_lim = 0; //Диапазон, в котором должно находится введенное число.
	gets_s(str);
	if (is_digit(str[0])) //Проверка на цифру.
	{
		for (int i = 0; i < k; i++) //Считаем, что введено число, если в строке первые n элементов - цифры.
		{
			if (is_digit(str[i]))
			{
				result += (str[i] - '0') * pow(10, --n);
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
	else if (!(strcmp(str, "stop")))
	{
		return -1;
	}
	else
		return 0;
}

//Вывод результата работы.
void output()
{
	textattr(LIGHTGRAY);
	clrscr();
	gotoxy(window_width / 2 - 20, 1);
	printf("Вы сдались.");
}

void output(int cnt)
{
	textattr(LIGHTGRAY);
	clrscr();
	gotoxy(window_width / 2 - 20, 1);
	printf("Вы угадали за %d попыток! Моё уважение.\n", cnt);
}

//Рисование голов быка и коровы ¯\_(ツ)_/¯.
void output_bull_and_cow()
{
	char bull[] = "W#BBBBB#W#WB*B*BW###BBBBB####BYBYB#####YYY###";
	char cow[] = "##Y###Y###WWWWWWW###W*W*W####WWPWW####WWPWW##";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			gotoxy(window_width - 20 + j, 3 + i);
			if (bull[i * 9 + j] == 'W')
				textbackground(WHITE);
			else if (bull[i * 9 + j] == 'B')
				textbackground(BROWN);
			else if (bull[i * 9 + j] == '*')
				textbackground(BLACK);
			else if (bull[i * 9 + j] == 'Y')
				textbackground(YELLOW);
			else if (bull[i * 9 + j] == '#')
				textbackground(BLACK);
			printf(" ");
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			gotoxy(window_width - 10 + j, 3 + i);
			if (cow[i * 9 + j] == 'W')
				textbackground(WHITE);
			else if (cow[i * 9 + j] == 'P')
				textbackground(LIGHTMAGENTA);
			else if (cow[i * 9 + j] == '*')
				textbackground(BLACK);
			else if (cow[i * 9 + j] == 'Y')
				textbackground(YELLOW);
			else if (cow[i * 9 + j] == '#')
				textbackground(BLACK);
			printf(" ");
		}
	}
}

//Рисование цифр ¯\_(ツ)_/¯.
void output_pixes(int x, int y, int digit)
{
	char num[22];
	switch (digit)
	{
	case 0:
		strcpy(num, "_#_#_##_##_##_##_#_#_");
		break;
	case 1:
		strcpy(num, "__#_###_#__#__#__#__#");
		break;
	case 2:
		strcpy(num, "_#_#_#__#_#_#__#__###");
		break;
	case 3:
		strcpy(num, "_#_#_#__#_#___##_#_#_");
		break;
	case 4:
		strcpy(num, "__#_##_###_####__#__#");
		break;
	case 5:
		strcpy(num, "####__##___#__##_#_#_");
		break;
	case 6:
		strcpy(num, "_#_#_##__##_#_##_#_#_");
		break;
	case 7:
		strcpy(num, "###__#_#_#__#__#__#__");
		break;
	case 8:
		strcpy(num, "_#_#_##_#_#_#_##_#_#_");
		break;
	case 9:
		strcpy(num, "_#_#_##_#_##__##_#_#_");
		break;
	}
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			gotoxy(x + j, y + i);
			if (num[i * 3 + j] == '_')
				textbackground(BLACK);
			else
				textbackground(WHITE);
			printf(" ");
		}
	}
}

//Название "Bulls and cows", не знаю зачем, но оченб захотелось ¯\_(ツ)_/¯.
void output_title()
{
	char str[][20] = {
		"__#______#_#_____",
		"_#_#_____#_#_____",
		"_#_#_____#_#_____",
		"_##__#_#_#_#__#__",
		"_#_#_#_#_#_#_#_#_",
		"##_#_#_#_#_#_#___",
		"_#_#_#_#_#_#__#_#",
		"__#___#__#_#_#__#",
		"________________#",
		"______###_##___##",
		"_____#__#_#_#_#_#",
		"_____#__#_#_#_#_#",
		"_____#_##_#_#_#_#",
		"______#_#_#_#__#_",
		"_________________",
		"_#___#__#___#__#_",
		"#_#_#_#_#___#_#_#",
		"#___#_#_#_#_#_#__",
		"#_#_#_#_#_#_#__#_",
		"_#___#___#_#__#__"
	};
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			gotoxy(window_width - 30 + j, 3 + i);
			if (str[i][j] == '_')
				textbackground(BLACK);
			else
				textbackground(WHITE);
			printf(" ");
		}
	}
}

void bulls_and_cows(int n)
{
	textattr(LIGHTGRAY);
	setwindow(window_width, window_height);
	clrscr();
	setwindow(window_width, window_height);
	HideCursor();
	int alleged[5], guessed[5];
	int entered, bulls, cows, cnt = 0, flag = 1;

	//Компьютер "задумывает" n-значное число с неповторяющимися цифрами.
	guessed[0] = rand() % 9 + 1;
	for (int i = 1; i < n; i++)
	{
		guessed[i] = get_element(guessed, n, i);
	}
	gotoxy(1, 1);
	printf("Введите %d-значное число с неповторяющимися цифрами или \"stop\" для того, чтобы сдаться.", n);
	output_bull_and_cow();
	//Вычисление "коров" и "быков".
	while (true)
	{
		GetWindow(&window, &buf);
		bulls = cows = 0;
		clrpart(0, 3, 50, 7);
		gotoxy(1, 3);
		entered = get_entered(n);
		if (entered == -1)
		{
			output();
			return;
		}
		else if (entered == 0)
		{
			gotoxy(1, 9);
			printf("Неверный ввод. Попробуйте еще раз.");
			Sleep(1500);
			continue;
		}
		else if (entered == -2)
		{
			gotoxy(1, 9);
			printf("Введено не %d-значное число. Попробуйте еще раз.", n);
			Sleep(1500);
			continue;
		}

		for (int i = n - 1; i >= 0; i--)
		{
			alleged[i] = entered % 10;
			entered = entered / 10;
		}

		if (are_there_duplicates(alleged, n))
		{
			gotoxy(1, 9);
			printf("Введено число с повторяющимися цифрами!");
			Sleep(1500);
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
		{
			output_pixes(window_width - 17, 10, bulls);
			output_pixes(window_width - 7, 10, cows);
		}
		cnt++;
		gotoxy(1, 11);
		textattr(LIGHTGRAY);
		printf("Предыдущее число:");
		for (int i = 0; i < n; i++)
		{
			output_pixes(1 + 4 * i, 13, alleged[i]);
		}
	}
	output(cnt);
}

void set_length()
{
	textattr(LIGHTGRAY);
	setwindow(window_width, window_height);
	clrscr();
	setwindow(window_width, window_height);
	HideCursor();
	output_title();

	button button[4] = {
		{"length = 2", false},
		{"length = 3", false},
		{"length = 4", false},
		{"length = 5", false}
	};
	int n = sizeof(button) / sizeof(*button);
	char c = 0;
	bool changed = true;
	int id = 0;
	while (true)
	{
		GetWindow(&window, &buf);
		textattr(LIGHTGRAY);
		gotoxy(1, 1);
		printf("Выберите длину числа.");
		if (_kbhit())
		{
			c = _getch();
			if (c == 224 || c == 0)
				c = _getch();
			else if (c == 13)
			{
				bulls_and_cows(id + 2);
				return;
			}
			else
				continue;
		}
		button[id].state = false;
		if (c == 72 && id > 0)
		{
			id--;
			changed = true;
		}
		else if (c == 80 && id < n - 1)
		{
			id++;
			changed = true;
		}
		button[id].state = true;
		if (buf.X != window_width || buf.Y != window_height)
		{
			textattr(LIGHTGRAY);
			setwindow(window_width, window_height);
			clrscr();
			setwindow(window_width, window_height);
			HideCursor();
			output_title();
		}
		if (buf.X != window_width || buf.Y != window_height || changed)
		{
			appropriate(button, n, 0, 2);
			changed = false;
		}
		c = 0;
	}
}

void menu()
{
	textattr(LIGHTGRAY);
	setwindow(window_width, window_height);
	clrscr();
	setwindow(window_width, window_height);
	HideCursor();
	output_title();

	button button[2] = {
		{"Start", false},
		{"Exit", false}
	};
	int n = sizeof(button) / sizeof(*button);
	char c = 0;
	bool changed = true;
	int id = 0;
	while (true)
	{
		GetWindow(&window, &buf);
		if (_kbhit())
		{
			c = _getch();
			if (c == 224 || c == 0)
				c = _getch();
			else if (c == 13)
			{
				switch (id)
				{
				case 0:
					set_length();
					break;
				case 1:
					exit(0);
					break;
				}
				return;
			}
			else
				continue;
		}
		button[id].state = false;
		if (c == 72 && id > 0)
		{
			id--;
			changed = true;
		}
		else if (c == 80 && id < n - 1)
		{
			id++;
			changed = true;
		}
		button[id].state = true;

		//Перерисовывает если изменены параметры консоли.
		if (buf.X != window_width || buf.Y != window_height)
		{
			textattr(LIGHTGRAY);
			setwindow(window_width, window_height);
			clrscr();
			setwindow(window_width, window_height);
			HideCursor();
			output_title();
		}
		if (buf.X != window_width || buf.Y != window_height || changed) 
		{
			appropriate(button, n, 0, 0);
			changed = false;
		}
		c = 0;
	}
}

void last_screen()
{
	button button[2] = {
		{"To try again", false},
		{"Exit to menu", false}
	};
	int n = sizeof(button) / sizeof(*button);
	char c = 0;
	bool changed = true;
	int id = 0;
	output_title();
	while (true)
	{
		GetWindow(&window, &buf);
		textattr(LIGHTGRAY);
		if (_kbhit())
		{
			c = _getch();
			if (c == 224 || c == 0)
				c = _getch();
			else if (c == 13)
			{
				switch (id)
				{
				case 0:
					set_length();
					break;
				case 1:
					menu();
					break;
				};
				return;
			}
			else
				continue;
		}
		button[id].state = false;
		if (c == 72 && id > 0)
		{
			id--;
			changed = true;
		}
		else if (c == 80 && id < n - 1)
		{
			id++;
			changed = true;
		}
		button[id].state = true;
		if (changed)
		{
			appropriate(button, n, 0, 2);
			changed = false;
		}
		c = 0;
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int flag;
	menu();
	do
	{
		last_screen();
	} while (true);

	ShowCursor();

	return 0;
}
//- end of file ---------------------------------------------------------------