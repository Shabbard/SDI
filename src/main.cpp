#include "Film.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>

int main()
{

	std::ifstream infile;
	infile.open("Database_Data.txt");

	std::string str;

	while (std::getline(infile, str))
	{
		std::regex Film_Test("<Film>");

		if (!regex_search(str, Film_Test))
		{
			return false;
		}

		std::regex Film_Test("<Title>");
		std::regex Film_Test("(? <= >).*$");

		if (regex_search(str, Film_Test)) 
		{
						
			return false;
		}
	}

	return 0;
}



