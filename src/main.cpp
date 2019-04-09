#include "Browser.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>

int main()
{
    Browser browser;

	for (int i = 0; i < 6; i++)
    {
        browser.insert(i);
	}

	std::string strinput = "";

	do 
	{
		std::cin >> strinput;

		if (strinput == "next")
		{
			browser.nextNode();
            std::cout << "gone to next node" << std::endl;
		}
		if (strinput == "previous")
		{
			browser.previousNode();
            std::cout << "gone to previous node" << std::endl;
		}
		if (strinput == "display")
		{
            browser.display();
		}
	} while(strinput != "exit");
	
}


void LoadFile()
{
	std::ifstream infile;
	infile.open("Database_Data.txt");

	Film starwars;

	starwars.ID=2;
	starwars.FilmingLocations;

	std::string str;

	std::string values[10] = {"ID","Title", "Summary", "Genre", "Release Date", "Filming Locations", "Language", "Runtime", "Keywords", "Weekly Ticket Sales"};
	std::vector<std::string> LineData;

	while (std::getline(infile, str))
	{
		std::regex data("([^,]+)|[\s]"); // finds all of the data values between the commas and includes spaces for empty data values
  		std::smatch data_match;

  		if (std::regex_search(str, data_match, data)) // if there are data values to enter
  		{
    		for (std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), data); i != std::sregex_iterator(); ++i)
    		{
      			data_match = *i;
      			LineData.push_back(data_match.str()); // loops through the values between commas (including whitespace) and adds them to a vector
    		}
		}	
	}
}
