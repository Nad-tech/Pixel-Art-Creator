#pragma once

#include<\Users\dexte\source\repos\file_console_experiment\file_console_experiment\globals.h>

class Frame {
public:
	int *colours;
	short *characters;
	int width;
	int height;
	int x;
	int y;

	Frame(int w = 10, int h = 10, int x = 0, int y = 0) {
		width = w;
		height = h;
		this->x = x;
		this->y = y;
		colours = new int[w * h];
		characters = new short[w * h];
		for (int i = 0; i < width * height; i++) {
			colours[i] = COLOUR(FG_WHITE) | COLOUR(BG_BLACK);
			characters[i] = 'F';
		}
	}

	void setChar(int i, int c) {
		characters[i] = c;
	}

	void setColour(int i, int c) {
		colours[i] = c;
	}
};