#include "GUI.h"

int main()
{
    auto browser = new Browser;
	FileHandler fileHandler(browser);
	fileHandler.LoadFile();
	GUI cli(browser);
	system("clear");
	cli.GUI_Templates("Load_Main_Menu");
    cli.CLI(fileHandler);
}