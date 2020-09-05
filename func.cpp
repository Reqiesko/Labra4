#include "func.h"
#include "ui.h"

bool error_check() {
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Пожалуйста введите цифру из ниже указанных! " << endl;
		return 0;
	}
	return 1;
}

int number_check() {
	int a;
	while (!(cin >> a) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка! Пожалуйста введите число! " << endl;
	}
	return a;
}

count_ev_in_text counting(vector<string>& text) {	
  string letters = "qwetryuiopasdfghjklzxcbvnmйцукенгшщзхъфывапрлоджэячсмитьбюQWERTYUIOPASDFGHJKLZXCVBNMЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";
  string numbers = "0123456789";
  int symbols_count, words_count, lines_count, paragraphs_count;
  symbols_count = 0;
  words_count = 0;
  lines_count = 0;
  paragraphs_count = 0;
  lines_count = distance(text.begin(), text.end());
  for (int i = 0; i < text.size(); i++) {
    symbols_count += text[i].length();
    const char* str = text[i].c_str();
    int j = 0;
    int word = 0;
    if (str[0] == '\t')
      paragraphs_count++;
    while (str[j] != '\0') {
      if (str[j] == ' ' || str[j] == '\t' || str[j] == '/') {
        word = separator;
      }
      if (numbers.find(str[j]) != string::npos) {
        word = number;
      }
      if ((str[j] != ' ' || str[j] != '\t' || str[j] != '/') && letters.find(str[j]) != string::npos) {
        word = words;
      }
      if (word == words && ((str[j + 1] == ' ') || (str[j + 1] == '/') || (str[j + 1] == '\t') || (j == text[i].length() - 1))) {
        words_count++;
      }
      j++;
    }
  } 
  return {
    symbols_count, 
    words_count,
    lines_count,
    paragraphs_count
  };
}

void delete_from_end(vector<string>& text, int line, int number) {
	int size_str = text[line - 1].length();
	text[line-1].erase((size_str - number), number);
}

void change_letters_in_text(vector<string>& text, int text_size) {
	char lower = 'я', upper = 'Я';
	for (int i = 0; i < text_size; i++) {
		for (unsigned int j = 0; j < text[i].length(); j++) {
			if ((j == 0) || (text[i][j - 1] == ' ')) {
				text[i][j] = toupper(text[i][j]);
				if (text[i][j] == lower) {
					text[i][j] = upper;
				}
			}
		}
	}
}


bool file_name_check(string filename) {
	size_t found = filename.find_last_of("\\");
	size_t point = filename.find_last_of(".");
	size_t base = point - found - 1;
	string basefilenameStr = filename.substr(found + 1, base);
	const char* basefilenameChar = basefilenameStr.c_str();
	ofstream file(filename, ios::app);
	if (!_strcmpi(basefilenameChar, "con")) return true;
	if (!std::filesystem::is_regular_file(filename)) return true;
	file.close();
	return false;
}

void print_text(vector<string> text) {
	cout << "Отредактированный текст:" << endl;
	cout << endl;
	for (int i = 0; i < text.size(); i++) {
		cout << i + 1 << ". " << text[i] << endl;
	}
}

void save_source(string inpath, vector<string> text, int modout) {
	ofstream fout;
	if (modout == 1) {
		fout.open(inpath, ios::out);
		fout << " " << endl;
	}
	if (modout == 2) {
		fout.open(inpath, ios::app);
		fout << " " << endl;
	}
	for (int i = 0; i < text.size(); i++) {
		fout << text[i] << endl;
	}
	cout << "Данные успешно сохранены! " << endl;
}

void save_source_data(string inpath, vector<string> text, int modout) {
	ofstream fout;
	count_ev_in_text count = {};
	count = counting(text);
	if (modout == 1) {
		fout.open(inpath, ios::out);
		fout << " " << endl;
	}
	if (modout == 2) {
		fout.open(inpath, ios::app);
		fout << " " << endl;
	}
	fout << endl;
	fout << "Количество символов: " << count.symbols << endl;
	fout << "Количество слов: " << count.words << endl;
	fout << "Количество строк: " << count.lines << endl;
	fout << "Количество абзацев: " << count.paragraphs << endl;
	cout << endl;
	cout << "Данные успешно сохранены! " << endl;
}

bool file_check_size(string pFile) {
	ifstream file_check_size;
	file_check_size.open(pFile, ios::in);
	file_check_size.seekg(0, ios::end);
	if (file_check_size.tellg() == 0) {
		file_check_size.close();
		return true;
	}
	else {
		file_check_size.close();
		return false;
	}
}

bool check_read_only(string filename) {
	ofstream file(filename, ios::in);
	LPCSTR name = filename.c_str();
	WIN32_FIND_DATAA findData;
	FindFirstFileA(name, &findData);
	if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
		cerr << "Ошибка! Невозможно сохранить данные в файл, предназначенный только для чтения! " << endl;
		return false;
	}
	else {
		return true;
	}
}


bool file_exist(string path) {
	ifstream file(path);
	file.open(path, ios::in);
	if (file.is_open())
		return true;
	else
		return false;
}