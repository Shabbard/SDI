#include "GUI.h"

int main()
{
    auto browser = new Browser;
	FileHandler fileHandler(browser);
	fileHandler.LoadFile("../data/Film_Info_backup.txt");
	GUI cli(browser);
	system("clear");
	cli.GUI_Templates("Load_Main_Menu");
    cli.CLI(fileHandler, "../data/Film_Info.txt");
}