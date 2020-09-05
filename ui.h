#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <Windows.h>

using namespace std;

enum input {
	keyboard = 1,
	from_file = 2,
	info = 3,
	test = 4,
	out = 5
};

enum text_work {
	count_sym = 1,
	del_from_end = 2,
	change_letters = 3,
	back_in_menu
};

enum question {
	yes = 1,
	no = 2
};

enum clearfile {
	rewrite = 1,
	add = 2,
	newfile
};

void greeting();

void main_menu();

int menu_text_work();

int wtdw_file(string& pFile);

int save_result_q();







