#include "ui.h"
#include "func.h"
#include "ex_work.h"


void keyboard_way() {
	vector<string> text;
	count_ev_in_text count = {};
	string buffer = "\0";
	const int null_size = 0;
	cout << "������� �����." << endl;
	cout << "�� ��������� ����� ������� ������ ������." << endl;
	while (true) {
		getline(cin, buffer);
		if (buffer != "\0") {
			text.push_back(buffer);
		}
		else {
			if (text.size() == null_size) {
				cout << "�� �� ����� �����." << endl;
				cout << "������� �����: " << endl;
				cout << endl;
			}
			else {
				break;
			}
		}
	}
	cout << "��� �����:" << endl;
	cout << endl;
	for (int i = 0; i < text.size(); i++) {
		cout << i + 1 << ". " << text[i] << endl;
	}
	cout << "�������� �������:" << endl;
	cout << "��������� �������� ������ � ����? " << endl;

	if (save_result_q() == yes) {
		string adres;
		ifstream foutcheck;
		cout << "������� ���� � ����� ��� ���������� �������� ������. " << endl;
		cin >> adres;
		foutcheck.open(adres, ios::in);
		while (!check_read_only(adres)) {
			foutcheck.close();
			cout << "������� ���� � �����: " << endl;
			cin >> adres;
			foutcheck.open(adres);
		}
		while (file_name_check(adres)) {
			foutcheck.close();
			cout << "������! ������������ ���� ��� ��� �����." << endl;
			cout << "������� ���� � �����: " << endl;;
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
			cout << "���������� ��������: " << count.symbols << endl;
			cout << "���������� ����: " << count.words << endl;
			cout << "���������� �����: " << count.lines << endl;
			cout << "���������� �������: " << count.paragraphs << endl;
			cout << endl;
			cout << "�������� �������:" << endl;
			cout << "��������� ��������� � ����? " << endl;
			if (save_result_q() == yes) {
				string adres;
				ifstream foutcheck;
				cout << "������� ���� � ����� ��� ���������� ����������. " << endl;
				cin >> adres;
				foutcheck.open(adres, ios::in);
				while (!check_read_only(adres)) {
					foutcheck.close();
					cout << "������� ���� � �����: " << endl;
					cin >> adres;
					foutcheck.open(adres);
				}
				while (file_name_check(adres)) {
					foutcheck.close();
					cout << "������! ������������ ���� ��� ��� �����." << endl;
					cout << "������� ���� � �����: " << endl;;
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
			const int first_line = 1;
			size_t lines = distance(text.begin(), text.end());
			static_cast<int>(lines);
			cout << "������� ����� ������ ��� ��������������:" << endl;
			line = number_check();
			while (line >= first_line && line <= lines) {
				if (text[line - 1].length() == null_size) {
					cout << "��� ������ ��� �����! ������� ������ ������:" << endl;
					line = number_check();
					while (line < first_line || line > lines) {
						cout << "������� �� ������������ ������! ���������� ������� ����� ������ ��� ���: " << endl;
						line = number_check();
						if (line >= first_line && line <= lines) {
							if (text[line - 1].length() == null_size) {
								cout << "��� ������ ��� �����! ������� ������ ������:" << endl;
								line = number_check();
							}
						}
					}
				}
				else
					break;
			}
			while (line < first_line || line > lines) {
				cout << "������� �� ������������ ������! ���������� ������� ����� ������ ��� ���: " << endl;
				line = number_check();
				while (line >= first_line && line <= lines) {
					if (text[line - 1].length() == null_size) {
						cout << "��� ������ ��� �����! ������� ������ ������:" << endl;
						line = number_check();
					}
					else
						break;
				}
			}
			cout << "������� ���������� �������� ��� ��������:" << endl;
			number = number_check();
			if (number > text[line - 1].length()) {
				cout << "� ������ ��� ������� ��������, ������� ���������� �������. ���������� ���������� ��� ���:" << endl;
				cout << "�������� � ������: " << text[line - 1].length() << endl;
				cout << "������� ���������� ��������, ������� ���������� �������:" << endl;
				number = number_check();
				while ((number <= null_size) || (number > text[line - 1].length())) {
					cout << "����������� ��������� ������. ���������� ���������� ��� ���:" << endl;
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
		case back_in_menu: {
			break;
		}		
		}
		if (var == back_in_menu)
			break;
		if (var != count_sym && var != back_in_menu) {
			cout << "�������� �������:" << endl;
			cout << "��������� ��������� � ����? " << endl;
			if (save_result_q() == yes) {
				string adres;
				ifstream foutcheck;
				cout << "������� ���� � ����� ��� ���������� ����������. " << endl;
				cin >> adres;
				foutcheck.open(adres, ios::in);
				while (!check_read_only(adres)) {
					foutcheck.close();
					cout << "������� ���� � �����: " << endl;
					cin >> adres;
					foutcheck.open(adres);
				}
				while (file_name_check(adres)) {
					foutcheck.close();
					cout << "������! ������������ ���� ��� ��� �����." << endl;
					cout << "������� ���� � �����: " << endl;;
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

void file_way() {
	const int null_size = 0;
	string inpath;
	string buffer;
	count_ev_in_text count = {};
	ifstream fin;
	vector<string> text;
	cout << "������� ���� � �����: " << endl;
	cin >> inpath;
	fin.open(inpath);
	while (file_name_check(inpath)) {
		fin.close();
		cout << "������! ������ ������������ ���� � �����! \n������� ���� � �����: " << endl;
		cin >> inpath;
		fin.open(inpath);
	}
	if (!fin.is_open()) {
		cout << "������! �� ������ ������� ����!" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		main_menu();
	}
	else {
		if (file_check_size(inpath) == true) {
			cout << "������! ���� ����!" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			fin.close();
			main_menu();
		}
		fin.close();
		fin.open(inpath, ios::in);
		
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
			cout << "���������� ��������: " << count.symbols << endl;
			cout << "���������� ����: " << count.words << endl;
			cout << "���������� �����: " << count.lines << endl;
			cout << "���������� �������: " << count.paragraphs << endl;
			cout << endl;
			cout << "�������� �������:" << endl;
			cout << "��������� ��������� � ����? " << endl;
			if (save_result_q() == yes) {
				string adres;
				ifstream foutcheck;
				cout << "������� ���� � ����� ��� ���������� ����������. " << endl;
				cin >> adres;
				foutcheck.open(adres, ios::in);
				while (!check_read_only(adres)) {
					foutcheck.close();
					cout << "������� ���� � �����: " << endl;
					cin >> adres;
					foutcheck.open(adres);
				}
				while (file_name_check(adres)) {
					foutcheck.close();
					cout << "������! ������������ ���� ��� ��� �����." << endl;
					cout << "������� ���� � �����: " << endl;;
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
			const int first_line = 1;
			size_t lines = distance(text.begin(), text.end());
			static_cast<int>(lines);
			cout << "������� ����� ������ ��� ��������������:" << endl;
			line = number_check();
			while (line >= first_line && line <= lines) {
				if (text[line - 1].length() == null_size) {
					cout << "��� ������ ��� �����! ������� ������ ������:" << endl;
					line = number_check();
					while (line < first_line || line > lines) {
						cout << "������� �� ������������ ������! ���������� ������� ����� ������ ��� ���: " << endl;
						line = number_check();
						if (line >= first_line && line <= lines) {
							if (text[line - 1].length() == null_size) {
								cout << "��� ������ ��� �����! ������� ������ ������:" << endl;
								line = number_check();
							}
						}
					}
				}
				else
					break;
			}
			while (line < first_line || line > lines) {
				cout << "������� �� ������������ ������! ���������� ������� ����� ������ ��� ���: " << endl;
				line = number_check();
				while (line >= first_line && line <= lines) {
					if (text[line - 1].length() == null_size) {
						cout << "��� ������ ��� �����! ������� ������ ������:" << endl;
						line = number_check();
					}
					else
						break;
				}
			}			
			cout << "������� ���������� �������� ��� ��������:" << endl;
			number = number_check();
			if (number > text[line - 1].length()) {
				cout << "� ������ ��� ������� ��������, ������� ���������� �������. ���������� ���������� ��� ���:" << endl;
				cout << "�������� � ������: " << text[line - 1].length() << endl;
				cout << "������� ���������� ��������, ������� ���������� �������:" << endl;
				number = number_check();
				while (number <= null_size || number > text[line - 1].length()) {
					cout << "����������� ��������� ������. ���������� ���������� ��� ���:" << endl;
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
		if (var == back_in_menu)
			break;
		if (var != count_sym && var != back_in_menu) {
			cout << "�������� �������:" << endl;
			cout << "��������� ��������� � ����? " << endl;
			if (save_result_q() == yes) {
				string adres;
				ifstream foutcheck;
				cout << "������� ���� � ����� ��� ���������� ����������. " << endl;
				cin >> adres;
				foutcheck.open(adres, ios::in);
				while (!check_read_only(adres)) {
					foutcheck.close();
					cout << "������� ���� � �����: " << endl;
					cin >> adres;
					foutcheck.open(adres);
				}
				while (file_name_check(adres)) {
					foutcheck.close();
					cout << "������! ������������ ���� ��� ��� �����." << endl;
					cout << "������� ���� � �����: " << endl;;
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