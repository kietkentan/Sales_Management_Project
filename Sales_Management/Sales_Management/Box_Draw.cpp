#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <windows.h>
#include "Box_Draw.h"

using namespace std;

void Box_Draw::gotoxy(int x, int y) {
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

//screen: get [x]
int Box_Draw::whereX() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

//screen: get [y]
int Box_Draw::whereY() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

void Box_Draw::DrawOption(int x, int y, int w, int h, int y_temp, vector<string>& listOption) {
	for (int i = 0; i < listOption.size(); i++) {
		gotoxy(x + (w - listOption[i].size()) / 2, y + 1);
		cout << listOption[i];
		for (int ix = x + 1; ix < x + w; ix++) {
			gotoxy(ix, y);
			cout << char(196);
			gotoxy(ix, y + h);
			cout << char(196);
		}

		gotoxy(x, y + 1); cout << char(179);
		gotoxy(x + w, y + 1); cout << char(179);
		gotoxy(x, y);
		(i == 0) ? cout << char(218) : cout << char(195);
		gotoxy(x + w, y);
		(i == 0) ? cout << char(191) : cout << char(180);
		gotoxy(x, y + h); cout << char(192);
		gotoxy(x + w, y + h); cout << char(217);
		y += 2;
	}
}

int Box_Draw::SelectOption(string title, vector<string> option, int temp) {
	int x = 45;
	int y = 5;
	int y_temp = y + ((temp - 1) * 2);
	int w = 40;
	int h = 2;
	bool checkChange = true, checkDraw = true;
	while (true) {
		if (checkDraw) {
			gotoxy(x + (w - title.size()) / 2, y - 1);
			cout << title << endl;
			DrawOption(x, y, w, h, y_temp, option);
			checkDraw = false;
		}

		if (checkChange) {
			gotoxy(x + (w - option[(y_temp - y) / 2].size()) / 2, y_temp + 1);
			TextColorDarkBlue();
			cout << option[(y_temp - y) / 2];
			checkChange = false;
		}

		if (_kbhit()) {
			char c = _getch();
			if (true) {
				gotoxy(x + (w - option[(y_temp - y) / 2].size()) / 2, y_temp + 1);
				TextColorDarkWhite();
				cout << option[(y_temp - y) / 2];
				if (c == 72) {
					y_temp -= 2;
					if (y_temp < y) y_temp = y + 2 * option.size() - 2;
				}
				else if (c == 80) {
					y_temp += 2;
					if (y_temp > y + 2 * option.size() - 2) y_temp = y;
				}
				else if (c == 13) {
					system("cls");
					return 1 + ((y_temp - y) / 2);
				}
			}
			checkChange = true;
		}
	}
}

void Box_Draw::TextColorDarkBlue() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
}

void Box_Draw::TextColorDarkWhite() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

Box_Draw::Box_Draw() {};
Box_Draw::~Box_Draw() {};