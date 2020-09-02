#pragma once

#include<\Users\dexte\source\repos\PixelArtCreationTool\PixelArtCreationTool\ConsoleWindow.h>	
#include<\Users\dexte\source\repos\PixelArtCreationTool\PixelArtCreationTool\Frame.h>	
#include<string>

void setPaletteColours(Frame);
void updateSwatch(int, short);
void updateInfoBar();
void setMenuBar();
void setShading();
void updateShadingPalette(short c, int colour);

ConsoleWindow cWindow = ConsoleWindow();
Frame infoBar;
Frame swatch;
Frame menuBar;
Frame toolBarBorder_Vertical;
Frame toolBarBorder_Horizontal_1;
Frame toolBarBorder_Horizontal_2;
Frame toolBarBorder_Horizontal_3;
Frame palette;
Frame shading;
Frame canvas;
Frame shadingPalette;

int main() {
	//#Start - Canvas frame
	canvas = Frame(55, 25, 9, 4);
	for (int i = 0; i < canvas.width * canvas.height; i++) {
		canvas.characters[i] = ' ';
		canvas.colours[i] = COLOUR(BG_WHITE);
	}
	cWindow.writeFrame(canvas);
	//#End - Canvas frame

	//#Start - swatch/palette/shading/shading palette picking frames
	palette = Frame(2, 8, 0, 2);
	setPaletteColours(palette);
	cWindow.writeFrame(palette);

	shading = Frame(2, 2, 0, 11);
	setShading();
	cWindow.writeFrame(shading);

	shadingPalette = Frame(2, 8, 0, 14);
	updateShadingPalette(' ', 0);
	cWindow.writeFrame(shadingPalette);

	swatch = Frame(2, 2, 0, 23);
	//#End - swatch/palette/shading/shading palette picking frames

	//#Start - Controls/Info/menuframes
	infoBar = Frame(WIDTH, 1, 0, HEIGHT - 1);

	menuBar = Frame(WIDTH, 2, 0, 0);
	setMenuBar();
	cWindow.writeFrame(menuBar);
	//#End - Controls/Info/menu frames

	//#Start - Border frames
	//Beside palette/shading/swatch etc
	toolBarBorder_Vertical = Frame(1, HEIGHT - 1, 2, 2);
	for (int i = 0; i < HEIGHT - 3; i++) {
		toolBarBorder_Vertical.setChar(i, BORDER(D_VERT));
		toolBarBorder_Vertical.setColour(i, COLOUR(BG_BLACK) | COLOUR(FG_DARK_GREY));
	}
	cWindow.writeFrame(toolBarBorder_Vertical);

	//Underneath palette
	toolBarBorder_Horizontal_1 = Frame(2, 1, 0, 10);
	for (int i = 0; i < 2; i++) {
		toolBarBorder_Horizontal_1.setChar(i, BORDER(D_HOR));
		toolBarBorder_Horizontal_1.setColour(i, COLOUR(BG_BLACK) | COLOUR(FG_DARK_GREY));
	}
	cWindow.writeFrame(toolBarBorder_Horizontal_1);

	//Underneath shading tool
	toolBarBorder_Horizontal_2 = Frame(2, 1, 0, 13);
	for (int i = 0; i < 2; i++) {
		toolBarBorder_Horizontal_2.setChar(i, BORDER(D_HOR));
		toolBarBorder_Horizontal_2.setColour(i, COLOUR(BG_BLACK) | COLOUR(FG_DARK_GREY));
	}
	cWindow.writeFrame(toolBarBorder_Horizontal_2);

	//Underneath shading palette
	toolBarBorder_Horizontal_3 = Frame(2, 1, 0, 22);
	for (int i = 0; i < 2; i++) {
		toolBarBorder_Horizontal_3.setChar(i, BORDER(D_HOR));
		toolBarBorder_Horizontal_3.setColour(i, COLOUR(BG_BLACK) | COLOUR(FG_DARK_GREY));
	}
	cWindow.writeFrame(toolBarBorder_Horizontal_3);
	//#End - Border frames

	//#Start - Program loop
	cWindow.setWrite(true);
	int colour = COLOUR(BG_BLACK);
	short pixel = 0x0;
	updateSwatch(colour, pixel);


	while (!cWindow.key.escape) {
		cWindow.getInput();

		//get mouse x y
		int mx = cWindow.mouse.x;
		int my = cWindow.mouse.y;

		//#Start - Pick colour
		int px = palette.x;
		int py = palette.y;
		int pw = palette.width;
		int ph = palette.height;

		if (mx >= px && mx < px + pw && my >= py && my < py + ph) {
			if (cWindow.mouse.leftButton) {
				colour = palette.colours[(my - py) * pw + (mx - px)];
				updateSwatch(colour, ' ');
			}
		}
		//#End - Pick colour

		//#Start - paint
		int cx = canvas.x;
		int cy = canvas.y;
		int cw = canvas.width;
		int ch = canvas.height;
		colour = COLOUR(BG_BLACK);

		if (mx >= cx && mx < cx + cw && my >= cy && my < cy + ch) {
			int idx = (my - cy) * cw + (mx - cx);

			//paint
			if (cWindow.mouse.leftButton) {
				colour = swatch.colours[0];
				pixel = swatch.characters[0];
				canvas.setColour(idx, colour);
				canvas.setChar(idx, pixel);

				cWindow.writeFrame(canvas);
				cWindow.setWrite(true);
				cWindow.upDateWindow();
			}

			//erase
			if (cWindow.mouse.rightButton) {
				canvas.setColour(idx, COLOUR(BG_WHITE));
				canvas.setChar(idx, ' ');
				cWindow.writeFrame(canvas);
				cWindow.setWrite(true);
				cWindow.upDateWindow();
			}
		}
		//#End - paint

		//#Start - handle shading picker
		int sx = shading.x;
		int sy = shading.y;
		int sw = shading.width;
		int sh = shading.height;

		if (mx >= sx && mx < sx + sw && my >= sy && my < sy + sh) {
			if (cWindow.mouse.leftButton) {
				colour = swatch.colours[0];
				pixel = shading.characters[(my - sy)*sw + (mx - sx)];
				updateSwatch(colour, pixel);
				updateShadingPalette(pixel, colour);
			}
		}
		//#End - handle shading picker

		//#Start - handle shading colour picker
		int spx = shadingPalette.x;
		int spy = shadingPalette.y;
		int spw = shadingPalette.width;
		int sph = shadingPalette.height;

		if (mx >= spx && mx < spx + spw && my >= spy && my < spy + sph) {
			if (cWindow.mouse.leftButton) {
				int idx = (my - spy) * spw + (mx - spx);
				colour = shadingPalette.colours[idx];
				pixel = shadingPalette.characters[idx];
				updateSwatch(colour, pixel);
			}
		}
		//#End - handle shading colour picker

		//#Start - paint alpha character
		if (cWindow.key.a) {
			canvas.setColour((my - canvas.y) * canvas.width + (mx - canvas.x), COLOUR(BG_WHITE) | COLOUR(FG_BLACK));
			canvas.setChar((my - canvas.y) * canvas.width + (mx - canvas.x), 'a');
			cWindow.writeFrame(canvas);
			cWindow.setWrite(true);
			cWindow.upDateWindow();
		}
		//#End - paint alpha character


		//#Start - Save canvas

		//#End - Save canvas


		//Start - Open canvas

		//End - Open canvas

		updateInfoBar();
	}
	//#End - Program loop

	return 0;
}

void updateInfoBar() {
	std::string s;

	s = "x: " + std::to_string(cWindow.mouse.x) + ", ";
	s += "y: " + std::to_string(cWindow.mouse.y) + " ";
	s += "left: " + std::to_string(cWindow.mouse.leftButton) + " ";
	s += "right: " + std::to_string(cWindow.mouse.rightButton) + "  ";

	if (cWindow.key.up) s += 24;
	else s += " ";

	if (cWindow.key.down) s += 25;
	else s += " ";

	if (cWindow.key.left) s += 27;
	else s += " ";

	if (cWindow.key.right) s += 26;
	else s += " ";

	if (cWindow.key.s) s += 'S';
	else s += " ";

	for (int x = 0; x < int(infoBar.width * infoBar.height); x++) {
		infoBar.setColour(x, COLOUR(BG_DARK_GREEN) | COLOUR(FG_YELLOW));
		infoBar.setChar(x, x < int(s.length()) ? s[x] : ' ');
	}

	cWindow.writeFrame(infoBar);
	cWindow.setWrite(true);
	cWindow.upDateWindow();
}

void setMenuBar() {
	std::string s = " Exit | Open | Save | **PixelArt Creation Tool**  Copyright DanSolo";

	for (int x = 0; x < menuBar.width * menuBar.height; x++) {
		menuBar.setChar(x, x < int(s.length()) ? s[x] : x > menuBar.width - 1 ? BORDER(D_HOR) : ' ');
		menuBar.setColour(x, COLOUR(BG_DARK_BLUE) | COLOUR(FG_GREY));
	}
}

void setPaletteColours(Frame frame) {
	frame.setColour(0, COLOUR(BG_BLACK));
	frame.setColour(1, COLOUR(BG_DARK_BLUE));
	frame.setColour(2, COLOUR(BG_DARK_GREEN));
	frame.setColour(3, COLOUR(BG_DARK_CYAN));
	frame.setColour(4, COLOUR(BG_DARK_RED));
	frame.setColour(5, COLOUR(BG_DARK_MAGENTA));
	frame.setColour(6, COLOUR(BG_DARK_YELLOW));
	frame.setColour(7, COLOUR(BG_GREY));
	frame.setColour(8, COLOUR(BG_DARK_GREY));
	frame.setColour(9, COLOUR(BG_BLUE));
	frame.setColour(10, COLOUR(BG_GREEN));
	frame.setColour(11, COLOUR(BG_CYAN));
	frame.setColour(12, COLOUR(BG_RED));
	frame.setColour(13, COLOUR(BG_MAGENTA));
	frame.setColour(14, COLOUR(BG_YELLOW));
	frame.setColour(15, COLOUR(BG_WHITE));

	for (int i = 0; i < frame.width * frame.height; i++) {
		frame.characters[i] = ' ';
	}
}

void setShading() {
	int size = shading.width * shading.height;
	shading.characters[size - 4] = PIXEL(QUARTER);
	shading.characters[size - 3] = PIXEL(HALF);
	shading.characters[size - 2] = PIXEL(THREEQUARTERS);
	shading.characters[size - 1] = PIXEL(SOLID);

	shading.colours[size - 4] = COLOUR(FG_WHITE) | COLOUR(BG_BLACK);
	shading.colours[size - 3] = COLOUR(FG_WHITE) | COLOUR(BG_BLACK);
	shading.colours[size - 2] = COLOUR(FG_WHITE) | COLOUR(BG_BLACK);
	shading.colours[size - 1] = COLOUR(FG_WHITE) | COLOUR(BG_BLACK);
}

void updateSwatch(int colour, short c) {
	for (int i = 0; i < swatch.width * swatch.height; i++) {
		swatch.setColour(i, colour);
		swatch.setChar(i, c);
	}

	cWindow.writeFrame(swatch);
	cWindow.setWrite(true);
	cWindow.upDateWindow();
}

void updateShadingPalette(short c, int colour) {
	shadingPalette.setColour(0, COLOUR(FG_BLACK) | colour);
	shadingPalette.setColour(1, COLOUR(FG_DARK_BLUE) | colour);
	shadingPalette.setColour(2, COLOUR(FG_DARK_GREEN) | colour);
	shadingPalette.setColour(3, COLOUR(FG_DARK_CYAN) | colour);
	shadingPalette.setColour(4, COLOUR(FG_DARK_RED) | colour);
	shadingPalette.setColour(5, COLOUR(FG_DARK_MAGENTA) | colour);
	shadingPalette.setColour(6, COLOUR(FG_DARK_YELLOW) | colour);
	shadingPalette.setColour(7, COLOUR(FG_GREY) | colour);
	shadingPalette.setColour(8, COLOUR(FG_DARK_GREY) | colour);
	shadingPalette.setColour(9, COLOUR(FG_BLUE) | colour);
	shadingPalette.setColour(10, COLOUR(FG_GREEN) | colour);
	shadingPalette.setColour(11, COLOUR(FG_CYAN) | colour);
	shadingPalette.setColour(12, COLOUR(FG_RED) | colour);
	shadingPalette.setColour(13, COLOUR(FG_MAGENTA) | colour);
	shadingPalette.setColour(14, COLOUR(FG_YELLOW) | colour);
	shadingPalette.setColour(15, COLOUR(FG_WHITE) | colour);

	for (int i = 0; i < shadingPalette.width * shadingPalette.height; i++) {
		shadingPalette.characters[i] = c;
	}

	cWindow.writeFrame(shadingPalette);
	cWindow.setWrite(true);
	cWindow.upDateWindow();
}