#include "Browser.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>

void LoadFile(Browser* browser);
void UpdateFile(Browser* browser);

int main()
{
    Browser* browser = new Browser;


	// for (int i = 0; i < 6; i++)
    // {
    //     browser->insert_tail(i);
	// }

	std::string strinput = "";
    //int input = 0;

	LoadFile(browser);

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
		// if (striput == "")
		// {

		// }

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
    infile.open("../Film_Info.txt");

	Film film;

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

		if(LineData.at(0)== "ID")
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

		if(LineData.at(0)== "Crew_Members")
		{
			LineData.erase(LineData.begin());
			film.Crew_Members_String = LineData;
		}
		
		LineData.clear();
	}
} 



void UpdateFile(Browser* browser){

	browser->setHead();
	
	std::ofstream newfile("../test.txt");

	std::string str;

	while(browser->current->next != NULL)
	{
		newfile << "ID," << browser->current->data.ID << std::endl;
	} 


}
