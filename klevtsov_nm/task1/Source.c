#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <locale.h>

void main()
{
	setlocale(LC_ALL, "Rus");

	double h, w, d, pFiber, pChip, pWood, mBckWalls, mWalls, mDoors, mShelfs, m, qt;
	/*ДВП*/pFiber = 850;
	/*ДСП*/pChip = 650;
	/*Дерево*/pWood = 640;
	printf("Введите высоту, ширину, глубину: ");
	scanf_s("%lf %lf %lf", &h, &w, &d);

	qt = h / 41.5;
	qt = qt / 1;
	
	//Перевод в метры.
	h = h / 100.0;
	w = w / 100.0;
	d = d / 100.0;

	mBckWalls = h * w  * 0.005 * pFiber;
	mWalls = 2 * h * d * 0.015 * pChip;
	mDoors = 2 * h * w * 0.01 * pWood;
	mShelfs = w * d * 0.015 * (qt + 2) * pChip;

	m = mBckWalls + mWalls + mDoors + mShelfs;

	printf("Масса шкафа равна: %lf", m);
	_getch();
}