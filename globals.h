#pragma once

#define WIDTH 70
#define HEIGHT 34
#define FONT_X 20
#define FONT_Y 20
#define VK_C 0x43
#define VK_S 0x53
#define VK_A 0x41
#define TITLE "PixelArt creation tool"

enum COLOUR
{
	FG_BLACK = 0x0000,
	FG_DARK_BLUE = 0x0001,
	FG_DARK_GREEN = 0x0002,
	FG_DARK_CYAN = 0x0003,
	FG_DARK_RED = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW = 0x0006,
	FG_GREY = 0x0007, // Thanks MS :-/
	FG_DARK_GREY = 0x0008,
	FG_BLUE = 0x0009,
	FG_GREEN = 0x000A,
	FG_CYAN = 0x000B,
	FG_RED = 0x000C,
	FG_MAGENTA = 0x000D,
	FG_YELLOW = 0x000E,
	FG_WHITE = 0x000F,
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,
};

enum PIXEL {
	SOLID = 0x2588,
	THREEQUARTERS = 0x2593,
	HALF = 0x2592,
	QUARTER = 0x2591,
};

struct Mouse {
	int x = 0;
	int y = 0;
	bool leftButton = false;
	bool rightButton = false;
};

struct Key {
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool escape = false;
	bool c = false;
	bool s = false;
	bool a = false;
};

enum BORDER {
	D_VERT = 0x2551,
	D_HOR = 0x2550,
	D_BR_COR = 0x255D,
	D_BL_COR = 0x255A,
	D_TL_COR = 0x2554,
	D_TR_COR = 0x2557
};
