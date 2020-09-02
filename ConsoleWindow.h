#pragma once

#include<windows.h>
#include<\Users\dexte\source\repos\PixelArtCreationTool\PixelArtCreationTool\globals.h>
#include<\Users\dexte\source\repos\PixelArtCreationTool\PixelArtCreationTool\Frame.h>

class ConsoleWindow {
public:
	Mouse mouse;
	Key key;

	ConsoleWindow() {
		//Window size dimensions
		windowSize = { 0, 0, WIDTH - 1, HEIGHT - 1 };

		//Screen buffer dimensions
		bufferSize = { WIDTH , HEIGHT };

		// Setting up different variables for passing to WriteConsoleOutput
		characterBufferSize = { WIDTH, HEIGHT };
		characterPosition = { 0, 0 };
		consoleWriteArea = { 0, 0, WIDTH - 1, HEIGHT - 1 };

		//A CHAR_INFO structure containing data about a single character 
		consoleBuffer[WIDTH * HEIGHT];

		//Initialise handles
		h_out = GetStdHandle(STD_OUTPUT_HANDLE);
		h_in = GetStdHandle(STD_INPUT_HANDLE);

		//Set console Title
		
		const char *title = TITLE;
		size_t size = strlen(title) + 1;
		wchar_t* w_title = new wchar_t[size];
		size_t outSize;
		mbstowcs_s(&outSize, w_title, size, title, size - 1);
		SetConsoleTitle(w_title);

		//SetConsoleTitle(TITLE);
		

		//Set window size
		SetConsoleWindowInfo(h_out, true, &windowSize);

		//Set screen buffer size
		SetConsoleScreenBufferSize(h_out, bufferSize);

		//Set font attributes
		//SetConsoleOutputCP(CP_UTF8);
		font.cbSize = sizeof(font);
		font.nFont = 0;
		font.dwFontSize.X = FONT_X;
		font.dwFontSize.Y = FONT_Y;
		font.FontFamily = FF_DONTCARE;
		font.FontWeight = FW_NORMAL;
		wcscpy_s(font.FaceName, L"Consolas");
		SetCurrentConsoleFontEx(h_out, false, &font);
		

		//Turn off text cursor
		cursorInfo;
		GetConsoleCursorInfo(h_out, &cursorInfo);
		cursorInfo.bVisible = false; // set the cursor visibility
		SetConsoleCursorInfo(h_out, &cursorInfo);

		//Turn off mouse select (quick edit select) but enable mouse input
		GetConsoleMode(h_in, &prev_mode);
		SetConsoleMode(h_in, prev_mode & ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

		//Full screen mode variables and setter
		//COORD fullScreen = GetLargestConsoleWindowSize(h_out);
		//PCOORD fulScreen = &fullScreen;
		//SetConsoleDisplayMode(h_out, CONSOLE_FULLSCREEN_MODE, fulScreen);

		write = false;

		clearBuffer();
	}

	void clearBuffer(int c = COLOUR(FG_DARK_GREY) | COLOUR(BG_DARK_GREY)) {
		for (int j = 0; j < WIDTH * HEIGHT; j++) {
			setPixel(j, 'c', c);
		}
	}

	void upDateWindow() {
		if (write == true) {
			WriteConsoleOutput(h_out, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
			write = false;
		}
	}

	void setPixel(int idx, short chr, int col) {
		consoleBuffer[idx].Attributes = col;
		consoleBuffer[idx].Char.UnicodeChar = chr;
	}

	void setWrite(bool b) { write = b; }
	bool getWrite() { return write; }

	void getInput() {
		DWORD numEvents = 0;
		DWORD numEventsRead = 0;

		GetNumberOfConsoleInputEvents(h_in, &numEvents);

		if (numEvents) {
			eventBuffer = new INPUT_RECORD[sizeof(INPUT_RECORD) * numEvents];
			ReadConsoleInput(h_in, eventBuffer, numEvents, &numEventsRead);
		}

		if (numEventsRead) {
			for (DWORD i = 0; i < numEventsRead; i++) {

				//Handle mouse events
				if (eventBuffer[i].EventType == MOUSE_EVENT) {
					mouse.x = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					mouse.y = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;

					if (eventBuffer[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
						mouse.leftButton = true;
					}
					else { mouse.leftButton = false; }

					if (eventBuffer[i].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
						mouse.rightButton = true;
					}
					else { mouse.rightButton = false; }
				}

				//Handle keys
				if (eventBuffer[i].EventType == KEY_EVENT) {

					//Arrow keys
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_UP) {
						if (eventBuffer[i].Event.KeyEvent.bKeyDown) key.up = true;
						else key.up = false;
					}
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN) {
						if (eventBuffer[i].Event.KeyEvent.bKeyDown) key.down = true;
						else key.down = false;
					}
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_LEFT) {
						if (eventBuffer[i].Event.KeyEvent.bKeyDown) key.left = true;
						else key.left = false;
					}
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) {
						if (eventBuffer[i].Event.KeyEvent.bKeyDown) key.right = true;
						else key.right = false;
					}

					//Control keys
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
						if (eventBuffer[i].Event.KeyEvent.bKeyDown) key.escape = true;
						else key.escape = false;
					}

					//Character keys
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_C) {
						if (eventBuffer[i].Event.KeyEvent.bKeyDown) key.c = true;
						else key.c = false;
					}

					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_S) {
						if (eventBuffer[i].Event.KeyEvent.bKeyDown) key.s = true;
						else key.s = false;
					}

					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_A) {
						if (eventBuffer[i].Event.KeyEvent.bKeyDown) key.a = true;
						else key.a = false;
					}
				}
			}

			free(eventBuffer);
		}
	}

	void writeFrame(Frame frame) {
		int Xoffset = frame.x;
		int Yoffset = frame.y;

		for (int x = 0; x < frame.width; x++) {
			for (int y = 0; y < frame.height; y++) {
				setPixel((y + Yoffset) * WIDTH + (x + Xoffset),
					frame.characters[y * frame.width + x],
					frame.colours[y * frame.width + x]);
			}
		}
	}

private:
	SMALL_RECT windowSize;
	COORD bufferSize;
	COORD characterBufferSize;
	COORD characterPosition;
	SMALL_RECT consoleWriteArea;
	CHAR_INFO consoleBuffer[WIDTH * HEIGHT];
	CONSOLE_FONT_INFOEX font;
	CONSOLE_CURSOR_INFO cursorInfo;
	DWORD prev_mode;
	DWORD numEventsRead;
	INPUT_RECORD *eventBuffer;
	bool write;
	HANDLE h_out;
	HANDLE h_in;
};



