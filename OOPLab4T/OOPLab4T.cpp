 // OOPLab4T.cpp : Цей файл містить є шаблоном для 
// виконання лаб. роботи №4. 
// Він містинь функцію "main" з якої починається та закінчується виконання програми.
//


#include <iostream>
#include "Lab4.h"
#include "Task2.h"
#include <conio.h>
using namespace std;


// Ваші файли загловки 
//
#include "Lab4Exmaple.h"
#include "Lab4.h"
int main()
{
	char ch;
	do {
		cout << "\nSelect Task: \n";
		cout << "    1.  Task1 \n";
		cout << "    2.  Task2 \n";
		cout << "    3.  Exit \n";

		ch = _getch();
		switch (ch) {
		case '1':  Task1(); break;
		case '2': Task2(); break;
		}
	} while (ch != '3');
	return 0;
}