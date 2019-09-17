#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <locale.h>

void main()
{
	setlocale(LC_ALL, "Rus");

	double x1, y1, R1, x2, y2, R2, d, branch;
	printf("Введите значения первой окружности (x, y), R: ");
	scanf_s("%lf %lf %lf", &x1, &y1, &R1);

	printf("Введите значения второй окружности (x, y), R: ");
	scanf_s("%lf %lf %lf", &x2, &y2, &R2);
	
	d = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));

	//Определяем взаимное расположение двух окружностей.
	if ((R1 == R2) && (x1 == x2) && (y1 == y2))
	{
		printf("Окружности совпадают.");
	}
	else if (R1 + R2 < d)
	{
		printf("Не имеют общих точек.");
	}
	else if ((R1 + R2 == d) || (fabs(R1 - R2) == d))
	{
		printf("Окружности соприкасаются.");
	}
	else if ((R1 + R2 > d) && (fabs(R1 - R2) < d))
	{
		printf("Окружности пересекаются.");
	}
	else if (fabs(R1 - R2) > d)
	{
		printf("Окружность с меньшим радиусом внутри другой.");
	}
	_getch();
}