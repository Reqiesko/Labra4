#include "ui.h"
#include "func.h"
#include "test.h"

void module_tests() {
	const int count_of_tests = 6;
	vector<string> source_text, expected_text;
	count_ev_in_text count = {};
	int expected_sym1 = 27, expected_words1 = 4, expected_lines1 = 4, expected_paragraphs1 = 0, success_tests = 0;
	int expected_sym2 = 25, expected_words2 = 5, expected_lines2 = 4, expected_paragraphs2 = 1;
	source_text = { "symbols", "words", "lines", "paragraphs" };
	count = counting(source_text);
	if (count.symbols == expected_sym1 && count.words == expected_words1 && count.lines == expected_lines1 && count.paragraphs == expected_paragraphs1) {
		success_tests++;
	}
	else {
		cout << "Тест №1 Провалился!" << endl;
	}
	source_text = { "I", "love", "writing", "	hello world!" };
	count = counting(source_text);
	if (count.symbols == expected_sym2 && count.words == expected_words2 && count.lines == expected_lines2 && count.paragraphs == expected_paragraphs2) {
		success_tests++;
	}
	else {
		cout << "Тест №2 Провалился!" << endl;
	}
	source_text = { "I", "love", "writing", "	hello world!666999" };
	expected_text = { "I", "love", "writing", "	hello world!" };
	delete_from_end(source_text, 4, 6);
	if (source_text == expected_text) {
		success_tests++;
	}
	else {
		cout << "Тест №3 Провалился!" << endl;
	}
	source_text = { "Текст состоящий", "из", "нескольких строк и", "двух цифр 2,2.666" };
	expected_text = { "Текст состоящий", "из", "нескольких строк и", "двух цифр 2,2." };
	delete_from_end(source_text, 4, 3);
	if (source_text == expected_text) {
		success_tests++;
	}
	else {
		cout << "Тест №4 Провалился!" << endl;
	}
	source_text = { "i", "love", "writing", "hello world!" };
	expected_text = { "I", "Love", "Writing", "Hello World!" };
	change_letters_in_text(source_text, source_text.size());

	if (source_text == expected_text) {
		success_tests++;
	}
	else {
		cout << "Тест №5 Провалился!" << endl;
		print_text(source_text);
	}
	source_text = { "текст состоящий", "из", "нескольких строк и", "двух цифр 2,2." };
	expected_text = { "Текст Состоящий", "Из", "Нескольких Строк И", "Двух Цифр 2,2." };
	change_letters_in_text(source_text, source_text.size());
	if (source_text == expected_text) {
		success_tests++;
	}
	else {
		cout << "Тест №6 Провалился!" << endl;
	}
	if (count_of_tests == success_tests) {
		cout << "Тест успешно пройден!" << endl;
	}
	else {
		cout << "Тест провален!" << endl;
	}
	system("pause");
	system("cls");
}