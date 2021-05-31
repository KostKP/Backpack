#include <Windows.h>
#include <conio.h>
#include <malloc.h> //int *a = (int*)malloc(n * sizeof(int));
#include <iostream>     // std::cout, std::endl
#include <iomanip>      // std::setw

using namespace std;

struct item {
	int weight = 0;
	int price = 0;
};

void FillTable(int** table, item* a, int n, int m) {
	for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) {
		if (i == 0 || j == 0) table[i][j] = 0;
		else if (j < a[i - 1].weight) table[i][j] = table[i - 1][j];
		else table[i][j] = max(table[i - 1][j], table[i - 1][j - a[i - 1].weight] + a[i - 1].price);
	}
}

void printNumbers(int** table, item* a, int n, int m) {
	cout << "Предметы: ";
	for (int i = n; i >= 1; --i) {
		if (table[i][m] == table[i - 1][m]) continue;
		cout << i << ' ';
		m = m - a[i - 1].weight;
	}
}

void main() {
	srand(time(NULL));
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);

	int count, weight;

	cout << "Вместимость рюкзака = ";
	cin >> weight;

	cout << "Кол-во предметов = ";
	cin >> count;

	item* a = (item*)malloc(count * sizeof(item));
	system("CLS");
	for (int i = 0; i < count; ++i) {
		cout << "Предмет " << i + 1 << ':' << endl;
		cout << "Вес предмета = ";
		cin >> a[i].weight;
		cout << "Цена предмеита = ";
		cin >> a[i].price;
		system("CLS");
	}
	for (int i = 0; i < count; ++i) cout << "Предмет " << i + 1 << ": p["  << a[i].weight << "], w[" << a[i].price << ']' << endl;

	int** table = (int**)malloc((count + 1) * sizeof(int*));
	for (int i = 0; i <= count; ++i) table[i] = (int*)malloc((weight + 1) * sizeof(int));

	cout << "Таблица:" << endl;
	FillTable(table, a, count, weight);

	SetConsoleTextAttribute(hConsole, 10);
	cout << "  +";
	for (int i = 0; i <= weight; ++i) cout << std::setw(3) << i;
	SetConsoleTextAttribute(hConsole, 15);
	cout << endl;

	for (int i = 0; i <= count; ++i) {
		SetConsoleTextAttribute(hConsole, 10);
		cout << std::setw(3) << i;
		SetConsoleTextAttribute(hConsole, 15);
		for (int j = 0; j <= weight; ++j) cout << std::setw(3) << table[i][j];
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, 11);
	printNumbers(table, a, count, weight);
	SetConsoleTextAttribute(hConsole, 15);
}


//16 5 4 5 5 7 3 4 7 9 6 8
//10 5 5 5 3 9 2 10 4 4 2 8
//10 5 7 10 7 6 5 2 2 1 7 6

