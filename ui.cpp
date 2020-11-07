#include "ui.h"
#include "func.h"
#include "ex_work.h"
#include "test.h"


void greeting() { // ����������
	system("cls");
	cout << "��� ��������� ������������ ���������� ��������, ����, �����, ������� � ������, " << endl;
	cout << "������� ������� � ����� �������� ������, " << endl;
	cout << "�������� ��� ������ �������� ����� ���� ����������." << endl;
	cout << endl;
	cout << "�����: ����������� �������" << endl;
	cout << "������: 494" << endl;
	cout << "������������ ������ �4" << endl;
	cout << "������� 12" << endl;
	cout << endl;
}

void main_menu() {
	int var;
	const int ignor = 32767;
	cout << endl;
	while (true) {
		cout << "Menu" << endl;
		cout << "�������� �������: " << endl;
		cout << "1. ������ ����� �������." << endl;
		cout << "2. ������� ����� �� �����." << endl;
		cout << "3. ������� ���������� � ��������� � ������." << endl;
		cout << "4. ��������� �����. " << endl;
		cout << "5. ����� �� ���������. " << endl;
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
				cout << "��������� ���������." << endl;
				exit(0);
			}
			default: {
				cout << "���������� ������� ����� �� ���� ���������! " << endl;
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
		cout << "��� ������� � �������? " << endl;
		cout << "1. ���������� ���������� ��������, ����, �����, ������� � ������" << endl;
		cout << "2. ������� ������� � ����� �������� ������." << endl;
		cout << "3. �������� ��� ������ �������� ����� ���� ����������." << endl;
		cout << "4. ����� � ����." << endl;
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
				cout << "���������� ������� ����� �� ��������� ����!" << endl;
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
		cout << "���� �� ����! �������� �������." << endl;
		cout << "1. ������������." << endl;
		cout << "2. �������� � �����." << endl;
		cout << "3. ������� ������ ����." << endl;
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
					cout << "������� ���� � �����. " << endl;
					cin >> pFile;
					foutcheck.open(pFile, ios::in);
					while (file_name_check(pFile)) {
						foutcheck.close();
						cout << "������! ������������ ���� ��� ��� �����." << endl;
						cout << "������� ���� � �����: " << endl;
						cin >> pFile;
						foutcheck.open(pFile, ios::in);
					}
					while (!check_read_only(pFile)) {
						foutcheck.close();
						cout << "������� ���� � �����: " << endl;
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
				cout << "���������� ������� ����� 1, 2 ��� 3. " << endl;
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
		cout << "1. �� " << endl;
		cout << "2. ��� " << endl;
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
				cout << "���������� ������� ����� 1 ��� 2. " << endl;
			}
		}
		cin.clear();
	}
	return 0;
}