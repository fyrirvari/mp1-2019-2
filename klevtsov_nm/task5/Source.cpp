#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <stdlib.h>  
#include <io.h>  
#include <time.h>  
#include <string.h>
#include "..\Console.cpp"

#define lim 2000

struct File
{
	struct _finddata_t file;
	char buffer[30];
};

void outputFiles(struct File files[], int n, double timeSpent)
{
	textattr(LIGHTGRAY);
	clrscr();
	printf("FILE    %20c     DATE %24c   SIZE\n", ' ', ' ');
	printf("----    %20c     ---- %24c   ----\n", ' ',' ');
	for (int i = 0; i < n; i++)
	{
		printf("%-32.32s %.24s  %10lu\n", files[i].file.name, files[i].buffer, files[i].file.size);
	}
	printf("\nTime spent: %.3lf sec\n", timeSpent);
	system("pause");
}

//----------------------------------------------------------------------------
void shakerSort(struct File files[], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = n - 2; j >= i; j--)
		{
			if (files[j + 1].file.size < files[j].file.size)
			{
				struct File file = files[j + 1];
				files[j + 1] = files[j];
				files[j] = file;
			}
		}
	}	
}

//----------------------------------------------------------------------------
void selectSort(struct File files[], int n)
{
	for (int i = 0; i < n; i++)
	{
		int min = files[i].file.size, k = i;
		for (int j = i + 1; j < n; j++)
		{
			if (files[j].file.size < min)
			{
				min = files[j].file.size;
				k = j;
			}
		}
		struct File file = files[i];
		files[i] = files[k];
		files[k] = file;
	}	
}

//----------------------------------------------------------------------------
void insertSort(struct File files[], int n)
{
	for (int i = 0; i < n; i++)
	{
		int x = files[i].file.size, j;
		struct File file = files[i];
		for (j = i - 1; j >= 0 && files[j].file.size > x; j--)
			files[j + 1] = files[j];
		files[j + 1] = file;
	}	
}

//----------------------------------------------------------------------------
void merge(struct File files[], long lb, long split, long ub)
{
	long pos1 = lb;
	long pos2 = split + 1;
	long pos3 = 0;
	struct File *temp = (File *)malloc((ub - lb + 1) * sizeof(File));
	while (pos1 <= split && pos2 <= ub)
	{
		if (files[pos1].file.size < files[pos2].file.size)
			temp[pos3++] = files[pos1++];
		else
			temp[pos3++] = files[pos2++];
	}

	while (pos2 <= ub)
		temp[pos3++] = files[pos2++];
	while (pos1 <= split)
		temp[pos3++] = files[pos1++];

	for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
		files[lb + pos3] = temp[pos3];

	free(temp);
}

void mergeSort(struct File files[], long lb, long ub)
{
	long split;
	if (lb < ub)
	{
		split = (lb + ub) / 2;
		mergeSort(files, lb, split);
		mergeSort(files, split + 1, ub);
		merge(files, lb, split, ub);
	}
}

void mergeSort(struct File files[], int n)
{
	mergeSort(files, 0, n - 1);	
}

//----------------------------------------------------------------------------
void quickSort(struct File files[], int n)
{
	long i = 0, j = n - 1;
	File temp;
	long p;
	p = files[n >> 1].file.size;
	
	do {
		while (files[i].file.size < p) i++;
		while (files[j].file.size > p) j--;

		if (i <= j) {
			temp = files[i]; files[i] = files[j]; files[j] = temp;
			i++; j--;
		}
	} while (i <= j);
	 
	if (j > 0) quickSort(files, j);
	if (n > i) quickSort(files + i, n - i);
}

//----------------------------------------------------------------------------
int increment(long inc[], long size) {
	int p1, p2, p3, s;

	p1 = p2 = p3 = 1;
	s = -1;
	do {
		if (++s % 2) {
			inc[s] = 8 * p1 - 6 * p2 + 1;
		}
		else {
			inc[s] = 9 * p1 - 9 * p3 + 1;
			p2 *= 2;
			p3 *= 2;
		}
		p1 *= 2;
	} while (3 * inc[s] < size);

	return s > 0 ? --s : 0;
}

void shellSort(struct File files[], int n)
{
	long inc, i, j, seq[40];
	int s;
	s = increment(seq, n);
	while (s >= 0)
	{
		inc = seq[s--];
		for (i = inc; i < n; i++)
		{
			File temp = files[i];
			for (j = i - inc; (j >= 0) && (files[j].file.size > temp.file.size); j -= inc)
				files[j + inc].file.size = files[j].file.size;
			files[j + inc] = temp;
		}
	}

}

//----------------------------------------------------------------------------
void countingSort(struct File files[], int n)
{
	unsigned long max = files[0].file.size; 
	for (int i = 1; i < n; i++)
		if (files[i].file.size > max) max = files[i].file.size;
	File **c = (File **)malloc(++max * sizeof(File *));
	int *qty = (int *)malloc(max * sizeof(int));
	int num = 0;
	memset(qty, 0, max * sizeof(int));
	for (int i = 0; i < n; i++) 
	{
		if (qty[files[i].file.size] == 0)
		{
			c[files[i].file.size] = (File *)malloc(++qty[files[i].file.size] * sizeof(File));
		}
		else
		{
			File *intermediate;
			intermediate = (File *)malloc(qty[files[i].file.size] * sizeof(File));
			for (int j = 0; j < qty[files[i].file.size]; j++)
				intermediate[j] = c[files[i].file.size][j];
			c[files[i].file.size] = (File *)malloc(++qty[files[i].file.size] * sizeof(File));
			for (int j = 0; j < qty[files[i].file.size]; j++)
				c[files[i].file.size][j] = intermediate[j];
			free(intermediate);
		}
		c[files[i].file.size][qty[files[i].file.size] - 1] = files[i];
	}
	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < qty[i]; j++)
		{
			files[num++] = c[i][j];
		}
	}
	free(c);
}

//----------------------------------------------------------------------------
void enterPath(void)
{
	textattr(LIGHTGRAY);
	clrscr();
	struct File file;
	struct File files[lim];
	intptr_t hFile;
	char path[200];
	int count = 0;
	printf("Enter path: ");
	gets_s(path);
	strcat(path, "*.*");

	// Find first *.* file in directory c:\temp
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
	Button button[] = {
		{"Bubble sort", false},
		{"Sort by selection", false},
		{"Insert sort", false},
		{"Merge sort", false},
		{"Quick sort", false},
		{"Shell sort", false},
		{"Sort by counting", false},
		{"Exit", false}
	};
	int n = sizeof(button) / sizeof(*button);
	clrscr();
	int id = clickListener(button, n);
	clock_t begin = clock();
	switch (id)
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
	case 7:
		exit(NULL);
		break;
	default:
		break;
	}
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