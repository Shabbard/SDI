#include "GUI.h"

GUI::GUI(Browser* input)
{
    browser = input;
}

GUI::~GUI()
{

}

void GUI::GUI_Templates(std::string GUI_ID)
{
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

void GUI::CLI(FileHandler fileHandler, std::string filePath)
{
		std::string strinput = "";

		bool menu_restriction = true;
		int menu_ID;

	do 
	{
        std::cin >> strinput;

		std::transform(strinput.begin(), strinput.end(), strinput.begin(), ::tolower);

		if ((strinput == "bm")&&(menu_restriction == true))
		{
			system("clear");
			GUI_Templates("B_Mode");
			menu_restriction = false;
			browser->display();
			menu_ID = 1;
		}

		if ((strinput == "mm")&&(menu_restriction == true))
		{
			system("clear");
			GUI_Templates("M_Mode");
			menu_restriction = false;
			browser->display();
			menu_ID = 2;
		}

		if (strinput == "rtm")
		{
			system("clear");
			GUI_Templates("Load_Main_Menu");
			menu_restriction = true;
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
			fileHandler.UpdateFile(filePath);
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
