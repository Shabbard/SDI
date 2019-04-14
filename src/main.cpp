#include "GUI.h"

int main()
{
    Browser* browser = new Browser;
	FileHandler fileHandler(browser);
	fileHandler.LoadFile("../data/Film_Info.txt");
	GUI cli(browser);
	system("clear");
	cli.GUI_Templates("Load_Main_Menu");
    cli.CLI(fileHandler, "../data/Film_Info.txt");
}