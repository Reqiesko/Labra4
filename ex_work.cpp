#include "ui.h"
#include "func.h"
#include "ex_work.h"


void keyboard_way() {
	vector<string> text;
	count_ev_in_text count = {};
	string buffer = "\0";
	cout << "Введите текст." << endl;
	cout << "По окончании ввода введите пустую строку." << endl;
	while (true) {
		getline(cin, buffer);
		if (buffer != "\0") {
			text.push_back(buffer);
		}
		else {
			if (text.size() == 0) {
				cout << "Вы не ввели текст." << endl;
				cout << "Введите текст: " << endl;
				cout << endl;
			}
			else {
				break;
			}
		}
	}
	cout << "Ваш текст:" << endl;
	cout << endl;
	for (int i = 0; i < text.size(); i++) {
		cout << i + 1 << ". " << text[i] << endl;
	}
	cout << "Выберите вариант:" << endl;
	cout << "Сохранить исходные данные в файл? " << endl;

	if (save_result_q() == 1) {
		string adres;
		ifstream foutcheck;
		cout << "Введите путь к файлу для сохранения исходных данных. " << endl;
		cin >> adres;
		foutcheck.open(adres, ios::in);
		while (!check_read_only(adres)) {
			foutcheck.close();
			cout << "Введите путь к файлу: " << endl;
			cin >> adres;
			foutcheck.open(adres);
		}
		while (file_name_check(adres)) {
			foutcheck.close();
			cout << "Ошибка! Некорректное путь или имя файла." << endl;
			cout << "Введите путь к файлу: " << endl;;
			cin >> adres;
			foutcheck.open(adres, ios::in);
		}
		if (file_exist(adres) == false) {
			foutcheck.close();
			save_source(adres, text, rewrite);
		}
		else {
			foutcheck.close();
			if (file_check_size(adres) == true) {
				save_source(adres, text, rewrite);
			}
			else {
				save_source(adres, text, wtdw_file(adres));
			}
		}
	}
	while (true) {
		int var = menu_text_work();
		switch (var) {
		case count_sym: {
			count = counting(text);
			cout << endl;
			cout << "Количество символов: " << count.symbols << endl;
			cout << "Количество слов: " << count.words << endl;
			cout << "Количество строк: " << count.lines << endl;
			cout << "Количество абзацев: " << count.paragraphs << endl;
			cout << endl;
			cout << "Выберите вариант:" << endl;
			cout << "Сохранить результат в файл? " << endl;
			if (save_result_q() == 1) {
				string adres;
				ifstream foutcheck;
				cout << "Введите путь к файлу для сохранения результата. " << endl;
				cin >> adres;
				foutcheck.open(adres, ios::in);
				while (!check_read_only(adres)) {
					foutcheck.close();
					cout << "Введите путь к файлу: " << endl;
					cin >> adres;
					foutcheck.open(adres);
				}
				while (file_name_check(adres)) {
					foutcheck.close();
					cout << "Ошибка! Некорректное путь или имя файла." << endl;
					cout << "Введите путь к файлу: " << endl;;
					cin >> adres;
					foutcheck.open(adres, ios::in);
				}
				if (file_exist(adres) == false) {
					foutcheck.close();
					save_source_data(adres, text, rewrite);
				}
				else {
					foutcheck.close();
					if (file_check_size(adres) == true) {
						save_source_data(adres, text, rewrite);
					}
					else {
						save_source_data(adres, text, wtdw_file(adres));
					}
				}
			}
			break;
		}
		case del_from_end: {
			int line = 0, number = 0; 
			size_t lines = distance(text.begin(), text.end());
			static_cast<int>(lines);
			cout << "Введите номер строки для редактирования:" << endl;
			line = number_check();
			while (line >= 1 && line <= lines) {
				if (text[line - 1].length() == 0) {
					cout << "Эта строка уже пуста! Укажите другую строку:" << endl;
					line = number_check();
					while (line < 1 || line > lines) {
						cout << "Указана не существующая строка! Пожалуйста введите номер строки еще раз: " << endl;
						line = number_check();
						if (line >= 1 && line <= lines) {
							if (text[line - 1].length() == 0) {
								cout << "Эта строка уже пуста! Укажите другую строку:" << endl;
								line = number_check();
							}
						}
					}
				}
				else
					break;
			}
			while (line < 1 || line > lines) {
				cout << "Указана не существующая строка! Пожалуйста введите номер строки еще раз: " << endl;
				line = number_check();
				while (line >= 1 && line <= lines) {
					if (text[line - 1].length() == 0) {
						cout << "Эта строка уже пуста! Укажите другую строку:" << endl;
						line = number_check();
					}
				}
			}
			cout << "Введите количество символов для удаления:" << endl;
			number = number_check();
			if (number > text[line - 1].length()) {
				cout << "В строке нет столько символов, сколько необходимо удалить. Пожалуйста попробуйте еще раз:" << endl;
				cout << "Символов в строке: " << text[line - 1].length() << endl;
				cout << "Введите количество символов, которые необходимо удалить:" << endl;
				number = number_check();
				while ((number <= 0) || (number > text[line - 1].length())) {
					cout << "Некорректно введенные данные. Пожалуйста попробуйте еще раз:" << endl;
					number = number_check();
				}
			}
			delete_from_end(text, line, number);
			print_text(text);
			break;
		}
		case change_letters: {
			change_letters_in_text(text, text.size());
			print_text(text);
			break;
		}
		}
		if (var != 1) {
			cout << "Выберите вариант:" << endl;
			cout << "Сохранить результат в файл? " << endl;

			if (save_result_q() == 1) {
				string adres;
				ifstream foutcheck;
				cout << "Введите путь к файлу для сохранения результата. " << endl;
				cin >> adres;
				foutcheck.open(adres, ios::in);
				while (!check_read_only(adres)) {
					foutcheck.close();
					cout << "Введите путь к файлу: " << endl;
					cin >> adres;
					foutcheck.open(adres);
				}
				while (file_name_check(adres)) {
					foutcheck.close();
					cout << "Ошибка! Некорректное путь или имя файла." << endl;
					cout << "Введите путь к файлу: " << endl;;
					cin >> adres;
					foutcheck.open(adres, ios::in);
				}
				if (file_exist(adres) == false) {
					foutcheck.close();
					save_source(adres, text, rewrite);
				}
				else {
					foutcheck.close();
					if (file_check_size(adres) == true) {
						save_source(adres, text, rewrite);
					}
					else {
						save_source(adres, text, wtdw_file(adres));
					}
				}
			}
		}
	}
}
const int ignor = 32767;
void file_way() {
	string inpath;
	string buffer;
	count_ev_in_text count = {};
	ifstream fin;
	vector<string> text;
	cout << "Укажите путь к файлу: " << endl;
	cin >> inpath;
	fin.open(inpath);
	while (file_name_check(inpath)) {
		fin.close();
		cout << "Ошибка! Введен неккоректный путь к файлу! \nВведите путь к файлу: " << endl;
		cin >> inpath;
		fin.open(inpath);
	}
	if (!fin.is_open()) {
		cout << "Ошибка! Не удаётся открыть файл!" << endl;
		cin.clear();
		cin.ignore(ignor, '\n');
		main_menu();
	}
	else {
		if (file_check_size(inpath) == true) {
			cout << "Ошибка! Файл пуст!" << endl;
			cin.clear();
			cin.ignore(ignor, '\n');
			fin.close();
			main_menu();
		}
		fin.close();
		fin.open(inpath, ios::in);
		size_t lines = distance(text.begin(), text.end());
		while (!fin.eof()) {
			while (getline(fin, buffer)) {
				text.push_back(buffer);
			}
		}	
		print_text(text);
	}
	while (true) {
		int var = menu_text_work();
		switch (var) {
		case count_sym: {
			count = counting(text);
			cout << endl;
			cout << "Количество символов: " << count.symbols << endl;
			cout << "Количество слов: " << count.words << endl;
			cout << "Количество строк: " << count.lines << endl;
			cout << "Количество абзацев: " << count.paragraphs << endl;
			cout << endl;
			cout << "Выберите вариант:" << endl;
			cout << "Сохранить результат в файл? " << endl;
			if (save_result_q() == 1) {
				string adres;
				ifstream foutcheck;
				cout << "Введите путь к файлу для сохранения результата. " << endl;
				cin >> adres;
				foutcheck.open(adres, ios::in);
				while (!check_read_only(adres)) {
					foutcheck.close();
					cout << "Введите путь к файлу: " << endl;
					cin >> adres;
					foutcheck.open(adres);
				}
				while (file_name_check(adres)) {
					foutcheck.close();
					cout << "Ошибка! Некорректное путь или имя файла." << endl;
					cout << "Введите путь к файлу: " << endl;;
					cin >> adres;
					foutcheck.open(adres, ios::in);
				}
				if (file_exist(adres) == false) {
					foutcheck.close();
					save_source_data(adres, text, rewrite);
				}
				else {
					foutcheck.close();
					if (file_check_size(adres) == true) {
						save_source_data(adres, text, rewrite);
					}
					else {
						save_source_data(adres, text, wtdw_file(adres));
					}
				}
			}
			break;
		}
		case del_from_end: {
			int line = 0, number = 0;
			size_t lines = distance(text.begin(), text.end());
			static_cast<int>(lines);
			cout << "Введите номер строки для редактирования:" << endl;
			line = number_check();
			int last_line = line - 1;
			while (line >= 1 && line <= lines) {
				if (text[last_line].length() == 0) {
					cout << "Эта строка уже пуста! Укажите другую строку:" << endl;
					line = number_check();
					while (line < 1 || line > lines) {
						cout << "Указана не существующая строка! Пожалуйста введите номер строки еще раз: " << endl;
						line = number_check();
						if (line >= 1 && line <= lines) {
							if (text[last_line].length() == 0) {
								cout << "Эта строка уже пуста! Укажите другую строку:" << endl;
								line = number_check();
							}
						}
					}
				}
				else
					break;
			}
			while (line < 1 || line > lines) {
				cout << "Указана не существующая строка! Пожалуйста введите номер строки еще раз: " << endl;
				line = number_check();
				while (line >= 1 && line <= lines) {
					if (text[line - 1].length() == 0) {
						cout << "Эта строка уже пуста! Укажите другую строку:" << endl;
						line = number_check();
					}
				}
			}			
			cout << "Введите количество символов для удаления:" << endl;
			number = number_check();
			if (number > text[line - 1].length()) {
				cout << "В строке нет столько символов, сколько необходимо удалить. Пожалуйста попробуйте еще раз:" << endl;
				cout << "Символов в строке: " << text[line - 1].length() << endl;
				cout << "Введите количество символов, которые необходимо удалить:" << endl;
				number = number_check();
				while (number <= 0 || number > text[line - 1].length()) {
					cout << "Некорректно введенные данные. Пожалуйста попробуйте еще раз:" << endl;
					number = number_check();
				}
			}			
			delete_from_end(text, line, number);
			print_text(text);
			break;
		}
		case change_letters: {
			change_letters_in_text(text, text.size());
			print_text(text);
			break;
		}
		}
		if (var != 1) {
			cout << "Выберите вариант:" << endl;
			cout << "Сохранить результат в файл? " << endl;

			if (save_result_q() == 1) {
				string adres;
				ifstream foutcheck;
				cout << "Введите путь к файлу для сохранения результата. " << endl;
				cin >> adres;
				foutcheck.open(adres, ios::in);
				while (!check_read_only(adres)) {
					foutcheck.close();
					cout << "Введите путь к файлу: " << endl;
					cin >> adres;
					foutcheck.open(adres);
				}
				while (file_name_check(adres)) {
					foutcheck.close();
					cout << "Ошибка! Некорректное путь или имя файла." << endl;
					cout << "Введите путь к файлу: " << endl;;
					cin >> adres;
					foutcheck.open(adres, ios::in);
				}
				if (file_exist(adres) == false) {
					foutcheck.close();
					save_source(adres, text, rewrite);
				}
				else {
					foutcheck.close();
					if (file_check_size(adres) == true) {
						save_source(adres, text, rewrite);
					}
					else {
						save_source(adres, text, wtdw_file(adres));
					}
				}
			}
		}
	}
}

