#include <iostream>
#include "ui.h"
#include<Windows.h>
int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	greeting();
	main_menu();
	return 0;
}