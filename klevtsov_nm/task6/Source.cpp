#define _CRT_SECURE_NO_WARNINGS

#include "locale.h"
#include "..\Console.cpp"
#include "Functions.cpp"

ld enterEpsilon()
{
	ld e;
	do
	{
		printf("Задайте точность вычисления больше или равной 0,000001: ");
		scanf_s("%Lf", &e);
	} while (e < 0.000001);
	return e;
}

ld enterX()
{
	ld x;
	printf("Задайте точку x, в которой необходимо вычислить значение: ");
	scanf_s("%Lf", &x);
	return x;
}

int enterTerms()
{
	int qty;
	do
	{
		printf("Задайте число элементов ряда для выполнения расчета не больше 1000: ");
		scanf_s("%d", &qty);
	} while (qty < 1 || qty > 1000);
	return qty;
}

int enterNMax()
{
	int qty;
	do
	{
		printf("Задайте число экспериментов не больше 25: ");
		scanf_s("%d", &qty);
	} while (qty < 1 || qty > 25);
	return qty;
}

ld (*selectFunc())(ld x, ld e, int& n, ld& reference)
{
	Button funcButton[] = {
		{"sin(x)", false},
		{"cos(x)", false},
		{"exp(x)", false},
		{"arcsin(x) |x|<1", false},
		{"arctg(x) |x|<=1", false},
		{"ln(1+x) -1<x<=1", false},
		{"arccos(x) |x|<1", false},
		{"tg(x) |x|<PI/2", false},
		{"ctg(x) |x|<PI", false},
		{"arcctg(x) |x|<=1", false}
	};
	ld(*func[])(ld x, ld e, int& n, ld& reference) = {
		mySin,
		myCos,
		myExp,
		myAsin,
		myAtan,
		myLog,
		myAcos,
		myTan,
		myCot,
		myAcot
	};
	clrscr();
	int id = clickListener(funcButton, sizeof(funcButton) / sizeof(*funcButton));
	textattr(LIGHTGRAY);
	clrscr();
	return func[id];
}

void single(void)
{
	ld reference;
	int n = enterTerms();
	ld value = selectFunc()(enterX(), enterEpsilon(), n, reference);
	printf("Эталонное значение: %Lf\n", reference);
	printf("Вычисленную оценку значения функции: %Lf\n", value);
	printf("Разница между оценкой и эталонным значением: %Lf\n", fabs(value - reference));
	printf("Количество слагаемых, которое было вычислено: %d\n", n);
}

void serial(void)
{
	ld reference;
	int n = enterNMax();
	ld x = enterX();
	ld (*func)(ld x, ld e, int& n, ld& reference) = selectFunc();
	boolean flag = true;
	for (int i = 1; i <= n; i++)
	{
		int qty = i;
		ld value = func(x, 0.000000001, qty, reference);
		if (flag)
		{
			printf("Эталонное значение: %Lf\n", reference);
			printf("Кол-во    Вычисленная оценка  %13cРазница\n", ' ');
			printf("%35c---------------\n", ' ');
			flag = false;
		}
		printf("%6d  %20Lf  %20Lf\n", qty, value, fabs(value - reference));
	}
}

void selectMode()
{
	void(*modes[])(void) = {
		single,
		serial
	};
	Button modeButton[] = {
		{"Однократный расчет функции в заданной точке", false},
		{"Серийный эксперимент", false}
	};
	int id = clickListener(modeButton, sizeof(modeButton) / sizeof(*modeButton));
	textattr(LIGHTGRAY);
	clrscr();
	(*modes[id])();
}

int main(void)
{
	setlocale(LC_ALL, "Rus");
	Button resButton[] = {
		{"Посчитать еще раз", false},
		{"Выход", false}
	};
	setFull();
	GetWindow(&window, &buf);
	setWindowWidthHeight(buf.X, buf.Y);
	HideCursor();
	int id;
	do
	{
		selectMode();
		system("pause");
		clrscr();
		id = clickListener(resButton, sizeof(resButton) / sizeof(*resButton));
	} while (id == 0);
	return 0;
}