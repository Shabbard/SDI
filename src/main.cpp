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

	std::string values[10] = {"ID","Title", "Summary", "Genre", "Release Date", "Filming Locations", "Language", "Runtime", "Keywords", "Weekly Ticket Sales"};
	std::vector<std::string> LineData;
	Film Stars;

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

		if(LineData.at(0)== "ID")
		{
			Stars.ID = std::stoi(LineData.at(1));
		}

		if(LineData.at(0)== "Title")
		{
			Stars.Title = LineData.at(1);
		}

		if(LineData.at(0)== "Summary")
		{
			Stars.Summary = LineData.at(1);
		}

		if(LineData.at(0)== "Genre")
		{
			LineData.erase(LineData.begin());
			Stars.Genre = LineData;
		}

		if(LineData.at(0)== "Release_Date")
		{
			Stars.ReleaseDate = LineData.at(1);
		}

		if(LineData.at(0)== "Filming Locations")
		{
			LineData.erase(LineData.begin());
			Stars.Filming_Locations = LineData;
		}

		if(LineData.at(0)== "Language")
		{
			LineData.erase(LineData.begin());
			Stars.Languages = LineData;
		}

		if(LineData.at(0)== "Runtime")
		{
			Stars.Runtime = std::stoi(LineData.at(1));
		}

		if(LineData.at(0)== "Keywords")
		{
			LineData.erase(LineData.begin());
			Stars.KeyWords = LineData;
		}

		if(LineData.at(0)== "Weekly Ticket Sales")
		{
			Stars.WeeklyTicketSale = std::stoi(LineData.at(1));
		}


	}
} 
