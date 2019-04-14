#include "Browser.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>
#include <stdlib.h>

void LoadFile(Browser* browser);
void UpdateFile(Browser* browser);
void WriteToFile(Browser* browser, std::ofstream& file);
void GUI(Browser* browser);
void GUI_Templates(std::string GUI_ID);

int main()
{
    Browser* browser = new Browser;
	LoadFile(browser);
	GUI_Templates("Load_Main_Menu");
    GUI(browser);
}

void LoadFile(Browser* browser)
{
	std::ifstream infile;
    infile.open("../data/Film_Info.txt");

	Film* film = new Film;

	std::string str;

	std::string values[10] = {"ID","Title", "Summary", "Genre", "Release Date", "Filming Locations", "Language", "Runtime", "Keywords", "Weekly Ticket Sales"};
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

		if(LineData.at(0)== "ID")
		{
			film->ID = std::stoi(LineData.at(1));
		}
		else if(LineData.at(0)== "Status")
		{
			film->Status = std::stoi(LineData.at(1));
		}
		else if(LineData.at(0)== "Title")
		{
			film->Title = LineData.at(1);
		}
		else if(LineData.at(0)== "Summary")
		{
			film->Summary = LineData.at(1);
		}
		else if(LineData.at(0)== "Genre")
		{
			LineData.erase(LineData.begin());
			film->Genre = LineData;
		}
		else if(LineData.at(0)== "Release_Date")
		{
			film->ReleaseDate = LineData.at(1);
		}
		else if(LineData.at(0)== "Filming_Loc")
		{
            LineData.erase(LineData.begin());
			film->Filming_Locations = LineData;
		}
		else if(LineData.at(0)== "Language")
		{
			LineData.erase(LineData.begin());
			film->Languages = LineData;
		}
		else if(LineData.at(0)== "Runtime")
		{
			film->Runtime = std::stoi(LineData.at(1));
		}
		else if(LineData.at(0)== "Keywords")
		{
			LineData.erase(LineData.begin());
			film->KeyWords = LineData;
		}
		else if(LineData.at(0)== "Weekly Ticket Sales")
		{
			film->WeeklyTicketSales = std::stoi(LineData.at(1));
		}
		else if(LineData.at(0)== "Crew_Members")
		{
			LineData.erase(LineData.begin());
            film->Crew_Members_String = LineData;
            browser->insert_tail(film);
			film = new Film();
		}
		
		LineData.clear();
	}
	film = nullptr;
} 

void WriteToFile(Browser* browser, std::ofstream& file)
{
	file << "ID," << browser->current->data->ID << std::endl;
	file << "Status," << browser->current->data->Status << std::endl;
	file << "Title," << browser->current->data->Title << std::endl;
	file << "Keywords,";
	for(std::vector<std::string>::iterator it = browser->current->data->KeyWords.begin(); it != browser->current->data->KeyWords.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Summary," << browser->current->data->Summary << std::endl;
	file << "Genre,";
	for(std::vector<std::string>::iterator it = browser->current->data->Genre.begin(); it != browser->current->data->Genre.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Release_Date," << browser->current->data->ReleaseDate << std::endl;
	file << "Filming_Loc,";
	for(std::vector<std::string>::iterator it = browser->current->data->Filming_Locations.begin(); it != browser->current->data->Filming_Locations.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Runtime," << browser->current->data->Runtime << std::endl;
	file << "Language,";
	for(std::vector<std::string>::iterator it = browser->current->data->Languages.begin(); it != browser->current->data->Languages.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Weekly Ticket Sales," << browser->current->data->WeeklyTicketSales << std::endl;
}

void UpdateFile(Browser* browser){

	browser->setHead();
	
	std::ofstream newfile("../data/test.txt");

	std::string str;

	while(browser->current != nullptr)
	{		
		WriteToFile(browser, newfile);

		if(browser->current->next == nullptr) // please find a better way of doing this
		{
			browser->nextNode();
			WriteToFile(browser, newfile);
		}
	}
}

void GUI( Browser* browser)
{
		std::string strinput = "";

		bool menu_restirction = true;
		int menu_ID;

	do 
	{
        std::cin >> strinput;

		std::transform(strinput.begin(), strinput.end(), strinput.begin(), ::tolower);

		if ((strinput == "bm")&&(menu_restirction == true))
		{
			system("clear");
			GUI_Templates("B_Mode");
			menu_restirction = false;
			browser->display();
			menu_ID = 1;
		}

		if ((strinput == "mm")&&(menu_restirction == true))
		{
			system("clear");
			GUI_Templates("M_Mode");
			menu_restirction = false;
			browser->display();
			menu_ID = 2;
		}

		if (strinput == "rtm")
		{
			system("clear");
			GUI_Templates("Load_Main_Menu");
			menu_restirction = true;
			menu_ID = 0;
		}

		if (strinput == "next")
		{
			switch (menu_ID)
			{
				case 1:
					system("clear");
					GUI_Templates("B_Mode");
					browser->nextNode();
					break;
			
				case 2:
					system("clear");
					GUI_Templates("M_Mode");
					browser->nextNode();
					break;
			}
							
		}
		if (strinput == "back")
		{
			switch (menu_ID)
			{
				case 1:
					system("clear");
					GUI_Templates("B_Mode");
					browser->nextNode();
					break;
			
				case 2:
					system("clear");
					GUI_Templates("M_Mode");
					browser->nextNode();
					break;
			}
			browser->previousNode();
		}

		if (strinput == "delete")
		{
			browser->delete_current();
		}
		// if (strinput == "load")
		// {
		// 	LoadFile(browser);
		// }
		if (strinput == "save")
		{
			UpdateFile(browser);
			browser->setHead();
		}
		if (strinput == "insert")
		{
			Film* new_film = new Film;

			// new_film->ID = 1;
			// new_film->Title = "1";
			// new_film->Status = 1;
			// new_film->KeyWords.push_back("1");
			// new_film->Summary = "1";
			// new_film->Genre.push_back("1");
			// new_film->ReleaseDate = "1";
			// new_film->Filming_Locations.push_back("1");
			// new_film->ReleaseDate = 1;
			// new_film->Languages.push_back("1");
			// new_film->WeeklyTicketSale = 1;
            // new_film->Crew_Members_String.push_back("1");

			std::cout << "Please insert a Title: ";
			std::cin >> new_film->Title;
			std::cout << "Please insert the Keywords: ";
			do
			{
				std::cin >> strinput;
				new_film->KeyWords.push_back(strinput);
			} while(strinput != "exit");
			std::cout << "Please insert a Summary: ";
			std::cin >> new_film->Summary;
			std::cout << "Please insert the Genres: ";
			do
			{
				std::cin >> strinput;
				new_film->Genre.push_back(strinput);
			} while(strinput != "exit"); 
			std::cout << "Please insert a Release Date: ";
			std::cin >> new_film->ReleaseDate;
			std::cout << "Please insert the Filming Locations: ";
			do
			{
				std::cin >> strinput;
				new_film->Filming_Locations.push_back(strinput);
			} while(strinput != "exit");
			std::cout << "Please insert the Runtime: ";
			std::cin >> new_film->Runtime;
			std::cout << "Please insert the Languages: ";
			do
			{
				std::cin >> strinput;
				new_film->Languages.push_back(strinput);
			} while(strinput != "exit");
			std::cout << "Please insert the Weekly Ticket Sale: ";
			std::cin >> new_film->WeeklyTicketSales;

			browser->insert(new_film);

			new_film = nullptr;
		}
	} while(strinput != "exit");
}


void GUI_Templates(std::string GUI_ID){
	if(GUI_ID == "Load_Main_Menu")
	{
		std::cout << "\n   TrekStar Production Log" << std::endl;
		std::cout << "______________________________" << std::endl;
		std::cout << "\n  Please Enter in a Value" << std::endl;		
		std::cout << "\nBrowser Mode          Enter BM" << std::endl;
		std::cout << "Maintenance Mode      Enter MM\n" << std::endl;
		std::cout << "Exit                  Enter Exit\n" << std::endl;
		std::cout << "______________________________\n" << std::endl;
	}

	if(GUI_ID == "B_Mode")
	{
		std::cout << "\n      Welcome to Browser Mode" << std::endl;
		std::cout << "___________________________________" << std::endl;		
		std::cout << "\n    Please Enter in a Value" << std::endl;		
		std::cout << "\nNext                      Enter Next" << std::endl;
		std::cout << "Back                      Enter Back" << std::endl;
		std::cout << "View Crew                 Enter Crew" << std::endl;
		std::cout << "View Material Info        Enter MI" << std::endl;
		std::cout << "Search                    Enter Search\n" << std::endl; // Develop Search Engine to complete criteria of mojoo
		std::cout << "Return to Menu            Enter RTM\n" << std::endl;
		std::cout << "___________________________________\n" << std::endl;
		
	}

	//std::cout << "Search            		Enter Search <Variable> <VariableN0745180	Alexander7 Data> (e.g Search Actor ExampleActorName) " << std::endl;

	if(GUI_ID == "M_Mode")
	{
		std::cout << "\n  Welcome to Maintenace Mode" << std::endl;
		std::cout << "______________________________" << std::endl;
		std::cout << "\nPlease Enter in a Value" << std::endl;		
		std::cout << "\nNext                      Enter Next" << std::endl;
		std::cout << "Back                      Enter Back" << std::endl;
		std::cout << "View Crew                 Enter Crew" << std::endl;
		std::cout << "View Material Info        Enter MI\n" << std::endl;
		std::cout << "Create New Project        Enter CNP" << std::endl;
		std::cout << "Edit                      Enter Edit" << std::endl;
		std::cout << "Delete Project            Enter Edit\n" << std::endl;
		std::cout << "Reports Mode              Enter R\n" << std::endl;
		std::cout << "Return to Menu            Enter RTM\n" << std::endl;
		std::cout << "______________________________\n" << std::endl;
	}

}