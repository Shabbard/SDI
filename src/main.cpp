#include "GUI.h"

int main()
{
    auto browser = new Browser;
	FileHandler fileHandler(browser);
	fileHandler.LoadFile("../data/Film_Info_backup.txt");
	GUI cli(browser);
    cli.Main_Menu(fileHandler, "../data/Film_Info.txt");
}