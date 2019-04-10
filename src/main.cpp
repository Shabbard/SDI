#include "Browser.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>

void LoadFile(Browser* browser);
void UpdateFile(Browser* browser);
void WriteToFile(Browser* browser, std::ofstream& file);

int main()
{
    Browser* browser = new Browser;

	std::string strinput = "";

	do 
	{
        std::cin >> strinput;

		if (strinput == "next")
		{
			browser->nextNode();
		}
		if (strinput == "previous")
		{
			browser->previousNode();
		}
		if (strinput == "display")
		{
            browser->display();
		}
		if (strinput == "delete")
		{
			browser->delete_current();
		}
		if (strinput == "load")
		{
			LoadFile(browser);
		}
		if (strinput == "save")
		{
			UpdateFile(browser);
			browser->setHead();
		}
		// if (strinput == "insert")
		// {
		// 	std::cout << "Please insert a number: ";
		// 	//std::cin >> input;
		// 	browser->insert(input);
		// }
		// if (strinput == "insert_head")
		// {
		// 	std::cout << "Please insert a number: ";
		// 	std::cin >> input;
		// 	browser->insert_head(input);
		// }
		// if (strinput == "insert_tail")
		// {
		// 	std::cout << "Please insert a number: ";
		// 	std::cin >> input;
		// 	browser->insert_tail(input);
		// }
	} while(strinput != "exit");
	
}

void LoadFile(Browser* browser)
{
	std::ifstream infile;
    infile.open("../data/test.txt");

	Film film;

	std::string str;

	//std::string values[10] = {"ID","Title", "Summary", "Genre", "Release Date", "Filming Locations", "Language", "Runtime", "Keywords", "Weekly Ticket Sales"};
	std::vector<std::string> LineData;
	
	while (std::getline(infile, str))
	{
		std::regex data("([^,]+)"); // finds all of the data values between the commas and includes spaces for empty data values
  		std::smatch data_match;

  		if (std::regex_search(str, data_match, data)) // if there are data values to enter
  		{
    		for (std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), data); i != std::sregex_iterator(); ++i)
    		{
      			data_match = *i;
      			LineData.push_back(data_match.str()); // loops through the values between commas (including whitespace) and adds them to a vector
    		}
		}	

		if(LineData.at(0)== "ID") // find a better way of doing this
		{
			film.ID = std::stoi(LineData.at(1));
		}
		if(LineData.at(0)== "Title")
		{
			film.Title = LineData.at(1);
		}
		if(LineData.at(0)== "Summary")
		{
			film.Summary = LineData.at(1);
		}
		if(LineData.at(0)== "Genre")
		{
			LineData.erase(LineData.begin());
			film.Genre = LineData;
		}
		if(LineData.at(0)== "Release_Date")
		{
			film.ReleaseDate = LineData.at(1);
		}
		if(LineData.at(0)== "Filming_Loc")
		{
			LineData.erase(LineData.begin());
			film.Filming_Locations = LineData;
		}
		if(LineData.at(0)== "Language")
		{
			LineData.erase(LineData.begin());
			film.Languages = LineData;
		}
		if(LineData.at(0)== "Runtime")
		{
			film.Runtime = std::stoi(LineData.at(1));
		}
		if(LineData.at(0)== "Keywords")
		{
			LineData.erase(LineData.begin());
			film.KeyWords = LineData;
		}
		if(LineData.at(0)== "Weekly Ticket Sales")
		{
			film.WeeklyTicketSale = std::stoi(LineData.at(1));
			browser->insert_tail(film);
		}
		LineData.clear();
	}
} 

void UpdateFile(Browser* browser){

	browser->setHead();

	std::string filePath = "../data/test.txt";
	std::ofstream newfile(filePath);

	while(browser->current != browser->tail)
	{		
		WriteToFile(browser, newfile);

		if(browser->current->next == browser->tail) // please find a better way of doing this
		{
			browser->nextNode();
			WriteToFile(browser, newfile);
		}

		browser->nextNode();
	}
}

void WriteToFile(Browser* browser, std::ofstream& file)
{
	file << "ID," << browser->current->data.ID << std::endl;
	file << "Status," << browser->current->data.Status << std::endl;
	file << "Title," << browser->current->data.Title << std::endl;
	file << "Summary," << browser->current->data.Summary << std::endl;
	file << "Genre,";
	for(std::vector<std::string>::iterator it = browser->current->data.Genre.begin(); it != browser->current->data.Genre.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Release_Date," << browser->current->data.ReleaseDate << std::endl;
	file << "Filming_Loc,";
	for(std::vector<std::string>::iterator it = browser->current->data.Filming_Locations.begin(); it != browser->current->data.Filming_Locations.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Language,";
	for(std::vector<std::string>::iterator it = browser->current->data.Languages.begin(); it != browser->current->data.Languages.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Runtime," << browser->current->data.Runtime << std::endl;
	file << "Keywords,";
	for(std::vector<std::string>::iterator it = browser->current->data.KeyWords.begin(); it != browser->current->data.KeyWords.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Weekly Ticket Sales," << browser->current->data.WeeklyTicketSale << std::endl;
}