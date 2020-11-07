#include "ui.h"
#include "func.h"
#include "ex_work.h"
#include "test.h"


void greeting() { // Приветсвие
	system("cls");
	cout << "Эта программа подсчитывает количество символов, слов, строк, абзацев в тексте, " << endl;
	cout << "удаляет символы с конца заданной строки, " << endl;
	cout << "заменяет все первые строчные буквы слов прописными." << endl;
	cout << endl;
	cout << "Автор: Нерадовский Артемий" << endl;
	cout << "Группа: 494" << endl;
	cout << "Лабораторная работа №4" << endl;
	cout << "Вариант 12" << endl;
	cout << endl;
}

void main_menu() {
	int var;
	const int ignor = 32767;
	cout << endl;
	while (true) {
		cout << "Menu" << endl;
		cout << "Выберите вариант: " << endl;
		cout << "1. Ввести текст вручную." << endl;
		cout << "2. Вывести текст из файла." << endl;
		cout << "3. Вывести информацию о программе и авторе." << endl;
		cout << "4. Выполнить тесты. " << endl;
		cout << "5. Выйти из программы. " << endl;
		cout << endl;
		var = number_check();

		if (!error_check()) {
			continue;
		}
		cin.ignore(ignor, '\n');
		switch (var) {
			case keyboard: {
				keyboard_way();
				break;
			}
			case from_file: {
				file_way();
				break;
			}
			case info: {
				greeting();
				break;
			}
			case test: {
				module_tests();
				main_menu();
			}
			case out: {
				cout << "Программа завершена." << endl;
				exit(0);
			}
			default: {
				cout << "Пожалуйста введите цифру из ниже указанных! " << endl;
			}
		}
		cin.clear();
	}
}

int menu_text_work() {
	int var; 
	const int ignor = 32767;
	while (true) {
		cout << endl;
		cout << "Что сделать с текстом? " << endl;
		cout << "1. Подсчетать количество символов, слов, строк, абзацев в тексте" << endl;
		cout << "2. Удалить символы с конца заданной строки." << endl;
		cout << "3. Заменить все первые строчные буквы слов прописными." << endl;
		cout << "4. Назад в меню." << endl;
		var = number_check();

		if (!error_check()) {
			continue;
		}
		cin.ignore(ignor, '\n');
		switch (var) {
			case count_sym: {
				return count_sym;
				break;
			}
			case del_from_end: {
				return del_from_end;
				break;
			}
			case change_letters: {
				return change_letters;
			}
			case back_in_menu: {
				main_menu();
				break;
			}
			default: {
				cout << "Пожалуйста введите цифру из указанных ниже!" << endl;
				continue;
			}
		}
	}
}

int wtdw_file(string& pFile) {
	bool d = true;
	ifstream foutcheck;
	int del;
	const int ignor = 32767;
	while (d) {
		cout << endl;
		cout << "Файл не пуст! Выберите вариант." << endl;
		cout << "1. Перезаписать." << endl;
		cout << "2. Дописать в конец." << endl;
		cout << "3. Указать другой файл." << endl;
		cin >> del;

		if (!error_check()) {
			continue;
		}
		cin.ignore(ignor, '\n');
		switch (del) {
			case rewrite: {
				return rewrite;
			}
			case add: {
				return add;
			}
			case newfile: {
				bool trg = true;
				while (trg) {
					cout << "Введите путь к файлу. " << endl;
					cin >> pFile;
					foutcheck.open(pFile, ios::in);
					while (file_name_check(pFile)) {
						foutcheck.close();
						cout << "Ошибка! Некорректный путь или имя файла." << endl;
						cout << "Введите путь к файлу: " << endl;
						cin >> pFile;
						foutcheck.open(pFile, ios::in);
					}
					while (!check_read_only(pFile)) {
						foutcheck.close();
						cout << "Введите путь к файлу: " << endl;
						cin >> pFile;
						foutcheck.open(pFile);
					}
					if (!foutcheck.is_open()) {
						ifstream newfile(pFile);
						newfile.close();
						return rewrite;
					}
					else {
						bool check = file_check_size(pFile);
						foutcheck.close();
						if (check) {
							return 0;
						}
						else {
							return wtdw_file(pFile);
						}
					}
				}
			}
			default: {
				cout << "Пожалуйста введите цифру 1, 2 или 3. " << endl;
				continue;
			}
		}
	}
	return 0;
}

int save_result_q() {
	int var = 0;
	const int ignor = 32767;
	bool sw = true;
	while (sw) {
		cout << "1. Да " << endl;
		cout << "2. Нет " << endl;
		cin >> var;
		if (!error_check()) {
			continue;
		}
		cin.ignore(ignor, '\n');
		switch (var) {
			case yes: {
				sw = false;
				return yes;			
			}
			case no: {
				sw = false;
				break;
			}
			default: {
				cout << "Пожалуйста введите цифру 1 или 2. " << endl;
			}
		}
		cin.clear();
	}
	return 0;
}