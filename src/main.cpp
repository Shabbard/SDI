#include "GUI.h"

int main()
{
    auto browser = new Browser();
	auto fileHandler = new FileHandler(browser);
	fileHandler->LoadFilmProjects();
	GUI cli(browser, fileHandler);
	cli.LoadCrew();
    cli.Main_Menu();
	delete fileHandler;
	delete browser;	
}