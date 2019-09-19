#include <stdio.h>
#include <locale.h>

//Плотности ДВП, ДСП и дерева (г/см^3).
const double pDVP = 0.85;
const double pDSP = 0.65;
const double pWood = 0.64;

double input(int lLim, int rLim, int k)
{
	double value;

	do
	{
		switch (k)
		{
		case 1:
			printf("Введите высоту от %d до %d см: ", lLim, rLim);
			break;
		case 2:
			printf("Введите ширину от %d до %d см: ", lLim, rLim);
			break;
		case 3:
			printf("Введите глубину от %d до %d см: ", lLim, rLim);
			break;
		}

		scanf_s("%lf", &value);

		if ((value < lLim) || (value > rLim))
		{
			printf("Не удововлетворяет условию.\n");
		}
	}
	while ((value < lLim) || (value > rLim));

	return value;
}

void main()
{
	setlocale(LC_ALL, "Rus");

	double h, w, d;
	double  mBckWall, mWalls, mDoors, mCaps, mShelfs, m;
	int qt, variable;

	//Ввод высоты(см), ширины(см), глубины.
	h = input(180, 220, 1);
	w = input(80, 120, 2);
	d = input(50, 90, 3);

	//Количество полок внутри шкафа.
	qt = (int)((h - 3) / 41.5);

	//Нахождение масс.
	mBckWall = h * w  * 0.5 * pDVP;
	mWalls = 2 * h * d * 1.5 * pDSP;
	mDoors = h * w * 1 * pWood;
	mCaps = 2 * (w - 3) * d * 1.5 * pDSP;
	mShelfs = qt * (w - 3) * d * 1.5 * pDSP;

	m = (mBckWall + mWalls + mDoors + mCaps + mShelfs) / 1000;

	printf("Выберите способ вывода:\n");
	printf("1)Вещественное число.\n");
	printf("2)Целое число.\n");
	scanf_s("%d", &variable);
	switch (variable)
	{
	case 1:
		printf("Масса шкафа равна: %lf (кг)\n", m);
		break;
	case 2:
		printf("Масса шкафа равна: %d (кг)\n", (int)m);
		break;
	}

	system("pause");
}