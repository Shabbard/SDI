#include "GUI.h"

int main()
{
    auto browser = new Browser;
	FileHandler fileHandler(browser);
	fileHandler.LoadFile();
	GUI cli(browser);
    cli.Main_Menu(fileHandler, "../data/Film_Info.txt");
}