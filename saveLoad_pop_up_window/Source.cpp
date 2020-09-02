#include<\Users\dexte\source\repos\file_console_experiment\file_console_experiment\ConsoleWindowr.h>
#include<fstream>

using namespace std;

void saveFrameToFileThenOpenFileAndPrintToCanvas() {
	ConsoleWindow cWindow = ConsoleWindow();

	Frame f = Frame(10, 10, 0, 0);

	ofstream out("outFile.txt");

	ifstream in("outFile.txt");

	for (int i = 0; i < f.width * f.height; i++) {
		f.colours[i] = COLOUR(BG_DARK_GREEN);
		f.characters[i] = 0x2191;
		out << f.colours[i] << " ";
		out << f.characters[i] << " ";
	}
	out.close();

	int colour = 0;
	int chr = 0x0;

	Frame f2 = Frame(10, 10, 11, 0);

	for (int i = 0; i < f.width * f.height; i++) {
		in >> colour >> chr;
		f2.colours[i] = colour;
		f2.characters[i] = chr;
	}


	cWindow.clearBuffer();
	cWindow.setWrite(true);
	cWindow.writeFrame(f);
	cWindow.setWrite(true);
	cWindow.writeFrame(f2);
	cWindow.upDateWindow();

	while (!cWindow.key.escape) {
		cWindow.getInput();
	}
}

int main() {
	saveFrameToFileThenOpenFileAndPrintToCanvas();

	ConsoleWindow cWindow = ConsoleWindow();

	Frame f = Frame(10, 10, 0, 0);



	
	cWindow.clearBuffer();
	cWindow.setWrite(true);
	cWindow.writeFrame(f);
	cWindow.upDateWindow();

	while (!cWindow.key.escape) {
		cWindow.getInput();
	}

	return 0;
}