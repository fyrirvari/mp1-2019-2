#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "..\Console.cpp"

struct Product
{
	char title[100];
	char point; // указатель: "*" - поштучно; "#" - на развес.
	double price;
	int barcode;
	double qty;
};

class vector
{
private:
	int size_;
public:
	Product arr[50];
	vector()
	{
		size_ = 0;
	}

	void push_back(Product product)
	{
		arr[size_++] = product;
	}

	int size()
	{
		return size_;
	}

	bool empty()
	{
		if (size_ == 0)
			return true;
		else
			return false;
	}
};

int findEl(vector list, int wanted)
{
	int num;
	for (num = 0; num < list.size(); num++)
	{
		if (list.arr[num].barcode == wanted)
			return num;
	}
	return -1;
}

vector products;
void createProductsList(void)
{
	FILE *productsList;
	Product product;
	if ((productsList = fopen("products_list.txt", "r")) == NULL)
	{
		printf("Warning: \"File not open!\"");
		system("pause");
		exit(NULL);
	}
	while (!feof(productsList))
	{
		fscanf(productsList, "%d %lf", &product.barcode, &product.price);
		fgetc(productsList);
		fgets(product.title, 100, productsList);
		if (product.point = product.title[strlen(product.title) - 1] == '\n')
		{
			product.point = product.title[strlen(product.title) - 2];
			product.title[strlen(product.title) - 2] = '\0'; // убираем последний символ, который осуществляет переход на следующую строку, а также доп. символ(point).
		}
		else
		{
			product.point = product.title[strlen(product.title) - 1];
			product.title[strlen(product.title) - 1] = '\0'; // ...

		}
		product.qty = 1;
		products.push_back(product);
	}
	fclose(productsList);
}

void showProductList(int x, int y)
{
	textattr(WHITE | BLACK);
	clrscr();
	int strNum = 0;
	for(int i = 0; i < products.size(); i++)
	{
		gotoxy(x, y + strNum);
		printf("%d\t%.2lf\t%s\n", products.arr[i].barcode, products.arr[i].price, products.arr[i].title);
		strNum++;
	}
}

void createCheck(vector check)
{
	textbackground(WHITE);
	textcolor(BLACK);
	clrscr();
	int i;
	double sum = 0, discount;
	gotoxy(90, 1);
	printf("Ltd \"Klevts\'s shop\"");
	gotoxy(90, 2);
	printf("C. Nizhny Novgorod, st. Gagarin Avenue 23");
	gotoxy(90, 3);
	printf("Opening hours: 08:00 - 23:00 seven days a week");
	for (i = 0; i < check.size(); i++)
	{
		gotoxy(1, 5 + i);
		printf("%s", check.arr[i].title);
		gotoxy(70, 5 + i);
		printf("%.2lfx", check.arr[i].price);
		if (check.arr[i].point == '*')
			printf("%.0lf", check.arr[i].qty);
		else
			printf("%.3lf", check.arr[i].qty);
		gotoxy(140, 5 + i);
		discount = (rand() % 11) * 5;
		printf("%.0lf%%", discount);
		gotoxy(window_width - 10, 5 + i);
		printf("=%.2lf", check.arr[i].price * check.arr[i].qty * (1 - discount / 100.0));
		sum += check.arr[i].price * check.arr[i].qty * (1 - discount / 100.0);
	}
	gotoxy(window_width - 14, 5 + i);
	printf("_____________", sum);
	gotoxy(1, 5 + i + 1);
	printf("Total price");
	gotoxy(window_width - 10, 5 + i + 1);
	printf("=%.2lf", sum);
	gotoxy(90, 5 + i + 3);
	printf("Thank you for your purchase!");
	_getch(); _getch();
}

//---------------------------------------------------------------------------
bool isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

int enterWanted()
{
	int result = 0, n = 4;
	char ch;
	char str[50];
	gets_s(str);
	if (isDigit(str[0]))
	{
		for (int i = 0; i < 4; i++)
		{
			if (isDigit(str[i]))
			{
				result += (str[i] - '0') * pow(10, --n);
			}
			else
				return 0;
		}
		return result;
	}
	else if (!(strcmp(str, "no more")))
	{
		return -1;
	}
	else
		return 0;
}
//---------------------------------------------------------------------------

void purchaseMenu(void)
{
	textattr(WHITE | BLACK);
	clrscr();
	vector check;
	showProductList(80, 1); //Только ради облегчения ввода штриховых кодов.¯\_(ツ)_/¯
	while (true)
	{
		textattr(WHITE | BLACK);
		clrpart(1, 2, 50, 8);
		int wanted;
		gotoxy(1, 1);
		printf("Enter product barcode or \"no more\" to stop");
		gotoxy(1, 2);
		wanted = enterWanted();
		if (wanted == -1)
			break;
		else if (wanted == 0)
		{
			gotoxy(1, 3);
			printf("Entered not our shop\'s barcode");
			Sleep(1000);
			continue;
		}

		int num;
		num = findEl(check, wanted);
		if (num == -1)
		{
			num = findEl(products, wanted);
			if (num == -1)
			{
				gotoxy(1, 3);
				printf("Entered not our shop\'s barcode");
				Sleep(1000);
				continue;

			}
			else
			{
				gotoxy(1, 4);
				printf("Price: %.2lf", products.arr[num].price);
				gotoxy(1, 5);
				printf("Name: %s", products.arr[num].title);

				Product product = products.arr[num];
				if (product.point == '*')
					product.qty = 1;
				else
				{
					gotoxy(1, 7);
					printf("Enter mass (kg)");
					gotoxy(1, 8);
					scanf_s("%lf", &product.qty); getchar();
				}
				check.push_back(product);
			}
		}
		else
		{
			gotoxy(1, 4);
			printf("Price: %.2lf", check.arr[num].price);
			gotoxy(1, 5);
			printf("Name: %s", check.arr[num].title);

			if (check.arr[num].point == '*')
				check.arr[num].qty++;
			else
			{
				double mass;
				gotoxy(1, 7);
				printf("Enter mass (kg)");
				gotoxy(1, 8);
				scanf_s("%lf", &mass); getchar();
				check.arr[num].qty += mass;
			}
		}
		Sleep(2000);
	}
	if (!check.empty())
		createCheck(check);
}

void menu(void)
{
	textattr(WHITE | BLACK);
	clrscr();

	Button button[] = {
		{"Product list", false},
		{"Buy", false},
		{"Exit", false}
	};
	int n = sizeof(button) / sizeof(*button);
	int id;
	id = clickListener(button, n);

	switch (id)
	{
	case 0:
		showProductList(0, 0);
		system("pause");
		menu();
		break;
	case 1:
		purchaseMenu();
		menu();
		break;
	case 2:
		exit(NULL);
		break;
	}
}

int main(void)
{
	createProductsList();
	if (products.empty())
	{
		printf("The store is empty! All products are took out!");
		system("pause");
		exit(NULL);
	}

	setFull();
	GetWindow(&window, &buf);
	setWindowWidthHeight(buf.X, buf.Y);
	HideCursor();
	srand(time(NULL));
	menu();

	return 0;
}