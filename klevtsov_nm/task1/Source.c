#include <stdio.h>
#include <locale.h>

void main()
{
	setlocale(LC_ALL, "Rus");

	double h, w, d, pDVP, pDSP, pWood, qt, mBckWall, mWalls, mDoors, mCaps, mShelfs, m, variable;

	printf("Введите высоту(см), ширину(см), глубину(см): ");
	scanf_s("%lf %lf %lf", &h, &w, &d);

	//Плотности ДВП, ДСП и дерева ().
	pDVP = 0.85;
	pDSP = 0.65;
	pWood = 0.64;

	//Количество полок внутри шкафа.
	qt = (int)((h - 2 * 1.5) / 41.5);

	//Нахождение масс.
	mBckWall = h * w  * 0.5 * pDVP;
	mWalls = 2 * h * d * 1.5 * pDSP;
	mDoors = 2 * h * w * 1 * pWood;
	mCaps = 2 * w * d * 1.5 * pDSP;
	mShelfs = (w - 1.5) * (d - 0.5) * qt * pDSP;

	m = (mBckWall + mWalls + mDoors +mCaps + mShelfs) / 1000; 

	printf("Выберите способ вывода:\n");
	printf("1)В вещественных числах.\n");
	printf("2)В целых числах.\n");
	scanf_s("%lf", &variable);
	switch ((int)variable)
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