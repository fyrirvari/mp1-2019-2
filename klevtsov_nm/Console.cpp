#include "windows.h"
#include "stdio.h"
#include "memory.h"
#include "conio.h"
#include "string.h"

enum TColor {BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
             DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
             LIGHTMAGENTA, YELLOW, WHITE};

int window_width = 130;
int window_height = 50;
const int titleLength = 45;
const int COUNT = 16 * 16;
SMALL_RECT window;
COORD buf;

struct Button
{
	char title[titleLength];
	bool state;
};

void setWindowWidthHeight(int window_width_, int window_height_)
{
	window_width = window_width_;
	window_height = window_height_;
}

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
    return - 1;

  CONSOLE_SCREEN_BUFFER_INFO buf;

  GetConsoleScreenBufferInfo(Console, &buf);
  return buf.dwCursorPosition.Y;
}

//-----------------------------------------------------------------------------
COORD WhereXY(void)
{
  HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos = {-1, -1};
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
  rect.Top= 0;
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
void setwindow(void)
{
	int width = window_width, height = window_height;
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
void setFull(void)
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
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

//-----------------------------------------------------------------------------
void appropriate(Button button[], int n, int margin_left, int margin_top)
{
	int button_width = titleLength + 5;
	char str[titleLength + 6];
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
		for (int k = 0; k < 3; k++)
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

//-----------------------------------------------------------------------------
void appropriate(Button button[], int n)
{
	int margin_left = 0, margin_top = 0;
	int button_width = titleLength + 5;
	char str[titleLength + 6];
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
		for (int k = 0; k < 3; k++)
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

//-----------------------------------------------------------------------------
int clickListener(Button button[], int n)
{
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
				return id;
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
			appropriate(button, n);
			changed = false;
		}
		c = 0;
	}
}

//- end of file ---------------------------------------------------------------
