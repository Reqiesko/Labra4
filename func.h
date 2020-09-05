#pragma once
#include "ui.h"

struct count_ev_in_text {
	int symbols, words, lines, paragraphs;
};



enum Symbol { number = 1, 
	separator, 
	words
};

bool error_check();

int number_check();

count_ev_in_text counting(vector<string>& text);

void delete_from_end(vector<string>& text, int line, int number);

void change_letters_in_text(vector<string>& text, int text_size);

bool file_name_check(string filename);

void print_text(vector<string> text);

void save_source(string inpath, vector<string> text, int modout);

void save_source_data(string inpath, vector<string> text, int modout);

bool file_check_size(string pFile);

bool check_read_only(string filename);

bool file_exist(string path);