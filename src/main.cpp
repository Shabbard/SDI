#include "Browser.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>

int main()
{
	Browser browser;

	int input = 0;

	for (int i = 0; i < 6; i++)
	{
		std::cin >> input;

		browser.insert(input);
	}

	do while(/* condition */)
	{
		/* code */
	}
	

	
	

	return 0;
}


void LoadFile()
{
	std::ifstream infile;
	infile.open("Database_Data.txt");

	std::string str;

	while (std::getline(infile, str))
	{
		std::regex Film_Test("<Film>");

		if (!regex_search(str, Film_Test))
		{
			//return false;
		}

        std::regex Title_Test("<Title>");
        std::regex Data("(? <= >).*$");

		if (regex_search(str, Film_Test)) 
		{
						
			//return false;
		}
	}

}
