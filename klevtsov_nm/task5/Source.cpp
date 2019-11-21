#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <stdlib.h>  
#include <io.h> 
#include <time.h>  
#include <string.h>
#include "..\Console.cpp"
#include "Sorts.cpp"

#define lim 5000


void outputFiles(struct File files[], int n, double timeSpent)
{
	textattr(LIGHTGRAY);
	clrscr();
	printf("FILE    %20c     DATE %24c   SIZE\n", ' ', ' ');
	printf("----    %20c     ---- %24c   ----\n", ' ', ' ');
	for (int i = 0; i < n; i++)
	{
		printf("%-32.32s %.24s  %10lu\n", files[i].file.name, files[i].buffer, files[i].file.size);
	}
	printf("\nTime spent: %.3lf sec\n", timeSpent);
	system("pause");
}

//----------------------------------------------------------------------------
struct File files[lim];

void enterPath(void)
{
	textattr(LIGHTGRAY);
	clrscr();
	struct File file;
	intptr_t hFile;
	char path[200];
	int count = 0;
	printf("Enter path: ");
	gets_s(path);
	strcat(path, "*.*");

	// Find first *.* file in directory
	if ((hFile = _findfirst(path, &file.file)) == -1L)
		printf("No files in current directory!\n");
	else
	{
		do {
			ctime_s(file.buffer, _countof(file.buffer), &file.file.time_write);
			if (file.file.attrib & _A_SUBDIR) continue;
			files[count++] = file;
			if (count == lim) break;
		} while (_findnext(hFile, &file.file) == 0);
		_findclose(hFile);
	}
	Button button1[] = {
		{"Bubble sort", false},
		{"Sort by selection", false},
		{"Insert sort", false},
		{"Merge sort", false},
		{"Quick sort", false},
		{"Shell sort", false},
		{"Sort by counting", false},
		{"Exit", false}
	};
	int n1 = sizeof(button1) / sizeof(*button1);
	clrscr();
	int id1 = clickListener(button1, n1);
	if (id1 == 7) exit(NULL);

	textattr(LIGHTGRAY);
	clrscr();
	Button button2[] = {
		{"Ascending", false},
		{"Descending", false}
	};
	int n2 = sizeof(button2) / sizeof(*button2);
	int id2 = clickListener(button2, n2);

	clock_t begin = clock();
	switch (id1)
	{
	case 0:
		shakerSort(files, count);
		break;
	case 1:
		selectSort(files, count);
		break;
	case 2:
		insertSort(files, count);
		break;
	case 3:
		mergeSort(files, count);
		break;
	case 4:
		quickSort(files, count);
		break;
	case 5:
		shellSort(files, count);
		break;
	case 6:
		countingSort(files, count);
		break;
	default:
		break;
	}
	if (id2) reverse(files, count);
	clock_t end = clock();
	double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
	outputFiles(files, count, timeSpent);
}

int main(void)
{
	setFull();
	GetWindow(&window, &buf);
	setWindowWidthHeight(buf.X, buf.Y);
	HideCursor();
	enterPath();

	Button button[] = {
		{"Sure", false},
		{"Nope", false}
	};
	int n = sizeof(button) / sizeof(*button);
	while (true)
	{
		clrscr();
		textattr(LIGHTGRAY);
		gotoxy(50, 1);
		printf("Try again?\n\n");
		int id = clickListener(button, n);
		if (id == 1) break;
		enterPath();
	}
	return 0;
}