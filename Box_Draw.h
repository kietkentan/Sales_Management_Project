#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <conio.h>

using namespace std;

class Box_Draw {
public:
	void gotoxy(int x, int y);
	int whereX();
	int whereY();
	void DrawOption(int x, int y, int w, int h, int y_temp, vector<string>& listOption);
	int SelectOption(string title, vector<string> option, int temp);
	void TextColorDarkBlue();
	void TextColorDarkWhite();

	Box_Draw();
	~Box_Draw();
};