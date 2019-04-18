#include "GUI.h"

int main()
{
    auto browser = new Browser;
	FileHandler fileHandler(browser);
	fileHandler.LoadFilmProjects();
	GUI cli(browser);
    cli.Main_Menu(fileHandler);
}