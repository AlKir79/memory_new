// memory.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <string>

using namespace std;

int menu()
{
	int size;
	system("cls");
	cout << "Компьютерная игра ПАМЯТЬ" << endl;
	cout << "========================" << endl;
	cout << "1 - Начать игру" << endl;
	cout << "2 - Выход" << endl;
	char key = _getch();
	if (key == '1') {
		do {
			system("cls");
			cout << "Введите размер поля ";
			cin >> size;
		} while (size > 10 || size < 0 || (size % 2) != 0);
		system("cls");
	};
	if (key == '2') exit(1);
	return size;
}

int checkXY(int** arr, int& size, int& x, int& y)
{
	int c = 0;
	for (size_t i = 0; i < size * size; i++)
	{
		if ((arr[0][i] == x) && (arr[1][i] == y)) {
			c = 1; return c;
		}
	}
	return c;
}

int checkVal(int*& arr, int& size, int& val)
{
	int c = 0;
	for (size_t i = 0; i < size * size / 2; i++)
	{
		if (arr[i] == val) {
			c = 1; return c;
		}
	}
	return c;

}

void printArr(int** arr, int& size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			cout << arr[i][j] << "  ";
		}
		cout << endl << endl;
	}
}
void printArrC(string** arr, int& size, int& x, int& y, HANDLE console)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (x == j && y == i) {
				SetConsoleTextAttribute(console, FOREGROUND_RED);
				cout << arr[i][j] << "  ";
				SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				continue;
			}
			cout << arr[i][j] << "  ";
		}
		cout << endl << endl;
	}
}

void fillArr1(int** arr, int& size)
{
	int x, y, val;
	int count = 0;
	int count1 = 0;
	// временный массив для координат
	int** temp = new int* [2];
	for (size_t i = 0; i < 2; i++)
	{
		temp[i] = new int[size * size];
	}
	// временный массив для значений
	int* temp1 = new int[size * size / 2];
	// цикл по всем значениям/2
	for (size_t i = 0; i < size * size / 2; i++)
	{
		//вычисляем значение и проверяем что такого еще не было
		int flag = 1;
		while (flag == 1)
		{
			val = 10 + rand() % 70;
			flag = checkVal(temp1, size, val);
		}
		temp1[count1] = val;
		count1++;
		// вычисляем 2 пары координат значения и проверяем, что таких координат еще не было
		for (size_t j = 0; j < 2; j++)
		{

			int flag = 1;
			while (flag == 1)
			{
				x = rand() % size;
				y = rand() % size;
				flag = checkXY(temp, size, x, y);
			}
			temp[0][count] = x;
			temp[1][count] = y;
			count++;
			arr[x][y] = val;
		}
	}
	delete[]temp;
	delete[]temp1;
}

void fillArr2(string** arr, int& size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			arr[i][j] = "**";
		}
	}
}
void print(string** arr, int& size, int& Score1, int& Score2, string& p, char& key, int& x, int& y, HANDLE console)
{
	system("cls");
	cout << "ОЧКИ ИГРОК 1 - " << Score1 << "      ОЧКИ ИГРОК 2 - " << Score2;
	cout << endl << endl;
	cout << "Играет " << p << endl;
	cout << "Двигая курсор (WASD) выберите первую цифру и нажмите E" << endl << endl;
	printArrC(arr, size, x, y, console);
}

void memArr(int** arr1, int& size)
{
	system("cls");
	cout << "ВНИМАНИЕ!!!" << endl;
	cout << "Приготовьтесь запомнить массив цифр" << endl;
	cout << "Массив будет показан на 10 секунд" << endl;
	cout << "Для продолжения нажмите любую клавишу";
	_getch();
	system("cls");
	printArr(arr1, size);
	Sleep(10000);
}

void victory()
{
	Beep(247, 500);
	Beep(417, 500);
	Beep(417, 500);
	Beep(370, 500);
	Beep(417, 500);
	Beep(329, 500);
	Beep(247, 500);
	Beep(247, 500);
	Beep(247, 500);
	Beep(417, 500);
	Beep(417, 500);
	Beep(370, 500);
	Beep(417, 500);
	Beep(497, 500);
	Sleep(500);
	Beep(497, 500);
	Beep(277, 500);
	Beep(277, 500);
	Beep(440, 500);
	Beep(440, 500);
	Beep(417, 500);
	Beep(370, 500);
	Beep(329, 500);
	Beep(247, 500);
	Beep(417, 500);
	Beep(417, 500);
	Beep(370, 500);
	Beep(417, 500);
	Beep(329, 500);
}

int game(int** arr1, string** arr2, int& size, int& Score1, int& Score2, string& p, int& count, HANDLE console)
{
	char key;
	int x = 0, y = 0;
	int x1 = 0, y1 = 0;
	int flag = 0;
	while (count < size * size / 2)
	{
		print(arr2, size, Score1, Score2, p, key, x, y, console);
		key = _getch(); Beep(1568, 200);
		// управление курсором
		if ((key == 'w' || key == 'W') && (y != 0))	y--;
		if ((key == 's' || key == 'S') && (y < size - 1))	y++;
		if ((key == 'a' || key == 'A') && (x != 0))	x--;
		if ((key == 'd' || key == 'D') && (x < size - 1))	x++;
		if ((key == 'e' || key == 'E') && arr2[y][x] == "**")
		{
			// если нажата клавиша е и это первое значение, то запоминаем значения координат положения курсора
			if (flag == 0) {
				Beep(800, 200);
				x1 = x;
				y1 = y;
				arr2[y][x] = to_string(arr1[y][x]);
				flag = 1;
				continue;
			}
			// иначе начинаем сравнивать
			if (flag == 1) {
				flag = 0;
				arr2[y][x] = to_string(arr1[y][x]);
				if (arr1[y][x] == arr1[y1][x1])
				{
					if (p == "ИГРОК 1") Score1 += 10;
					if (p == "ИГРОК 2") Score2 += 10;
					Beep(1800, 200);
					count++;
				}
				else {
					print(arr2, size, Score1, Score2, p, key, x, y, console);
					Sleep(3000);
					arr2[y1][x1] = "**";
					arr2[y][x] = "**";
					print(arr2, size, Score1, Score2, p, key, x, y, console);
					break;
				}
			}
		}
	}
	if (p == "ИГРОК 1") return Score1;
	if (p == "ИГРОК 2") return Score2;

}

int main()
{
	int count = 0;
	int Score1 = 0;
	int Score2 = 0;
	string p1 = "ИГРОК 1";
	string p2 = "ИГРОК 2";
	setlocale(LC_ALL, "");
	srand(time(NULL));
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true)
	{
		int size = menu();
		int** arr1 = new int* [size];
		for (size_t i = 0; i < size; i++)
		{
			arr1[i] = new int[size];
		}
		string** arr2 = new string * [size];
		for (size_t i = 0; i < size; i++)
		{
			arr2[i] = new string[size];
		}
		fillArr1(arr1, size);
		fillArr2(arr2, size);
		memArr(arr1, size);
		while (count < size * size / 2)
		{
			Score1 = game(arr1, arr2, size, Score1, Score2, p1, count, console);
			Score2 = game(arr1, arr2, size, Score1, Score2, p2, count, console);
		}
		system("cls");
		if (Score1 > Score2) cout << "ВЫИГРАЛ ИГРОК 1" << endl << "ЕГО РЕЗУЛЬТАТ " << Score1;
		else cout << "ВЫИГРАЛ ИГРОК 2" << endl << "ЕГО РЕЗУЛЬТАТ " << Score2;
		victory();
		cout << endl << "Для продолжения нажмите любую клавишу.";
		_getch();
	}
}