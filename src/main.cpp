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
      			DecomposedSentence.second.push_back(data_match.str()); // loops through the values between commas (including whitespace) and adds them to a vector
    		}
		}	
	}

		



std::regex Title_Test("<Title>");
std::regex Data(".*> ");


	

	
}



