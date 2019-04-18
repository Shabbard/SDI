#include "GUI.h"

int main()
{
    auto browser = new Browser;
	FileHandler* fileHandler = new FileHandler(browser);
	fileHandler->LoadFilmProjects();
	GUI cli(browser, fileHandler);
    cli.Main_Menu();
}