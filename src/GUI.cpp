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
		system("clear");
		std::cout << "\n   TrekStar Production Log" << std::endl;
		std::cout << "______________________________" << std::endl;
		std::cout << "\n  Please Enter in a Value" << std::endl;		
		std::cout << "\nBrowser Mode          Enter BM" << std::endl;
		std::cout << "Maintenance Mode      Enter MM\n" << std::endl;
		std::cout << "Save                  Enter Save\n" << std::endl;
		std::cout << "Exit                  Enter Exit\n" << std::endl;
		std::cout << "______________________________\n" << std::endl;
	}

	if(GUI_ID == "B_Mode")
	{
		system("clear");
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
		browser->display();
		
	}

	//std::cout << "Search            		Enter Search <Variable> <VariableN0745180	Alexander7 Data> (e.g Search Actor ExampleActorName) " << std::endl;

	if(GUI_ID == "M_Mode")
	{
		system("clear");
		std::cout << "\n  Welcome to Maintenace Mode" << std::endl;
		std::cout << "______________________________" << std::endl;
		std::cout << "\nPlease Enter in a Value" << std::endl;		
		std::cout << "\nNext                      Enter Next" << std::endl;
		std::cout << "Back                      Enter Back" << std::endl;
		std::cout << "View Crew                 Enter Crew" << std::endl;
		std::cout << "View Material Info        Enter MI\n" << std::endl;
		std::cout << "Create New Project        Enter CNP" << std::endl;
		std::cout << "Edit                      Enter EDIT" << std::endl;
		std::cout << "Delete Project            Enter DP\n" << std::endl;
		std::cout << "Reports Mode              Enter R\n" << std::endl;
		std::cout << "Return to Menu            Enter RTM\n" << std::endl;
		std::cout << "______________________________\n" << std::endl;
		browser->display();
	}

	if(GUI_ID == "edit")
	{
		system("clear");
		std::cout << "\n           Welcome to Edit Mode" << std::endl;
		std::cout << "______________________________________________" << std::endl;
		std::cout << "\nNext                                Enter Next" << std::endl;
		std::cout << "Back                                Enter Back\n" << std::endl;
		std::cout << "Step 1: Enter in the database you want to edit\n" << std::endl;
		std::cout << "Step 2: Enter in the ID you want to edit\n" << std::endl;
		std::cout << "Step 3: Enter in the datatype you want ot edit\n " << std::endl;
		std::cout << "______________________________________________\n" << std::endl;
	}

}

void GUI::CLI(FileHandler fileHandler)
{
		std::string strinput = "";

		bool menu_restriction = true;
		int menu_ID = 0;

	do 
	{
        std::cin >> strinput;

		std::transform(strinput.begin(), strinput.end(), strinput.begin(), ::tolower);

		if ((strinput == "bm")&&(menu_restriction == true))
		{
			GUI_Templates("B_Mode");
			menu_restriction = false;
			menu_ID = 1;
		}

		if ((strinput == "mm")&&(menu_restriction == true))
		{
			GUI_Templates("M_Mode");
			menu_restriction = false;
			menu_ID = 2;
		}

		if (strinput == "rtm")
		{
			GUI_Templates("Load_Main_Menu");
			menu_restriction = true;
			menu_ID = 0;
		}

		if (strinput == "next")
		{

			switch (menu_ID)
			{
				case 1:
					GUI_Templates("B_Mode");
					browser->nextNode();
					break;
			
				case 2:
					GUI_Templates("M_Mode");
					browser->nextNode();
					break;
				
				case 3:
					GUI_Templates("edit");
					browser->nextNode();
					break;
			}
							
		}
		if (strinput == "back")
		{
			switch (menu_ID)
			{
				case 1:
					GUI_Templates("B_Mode");
					browser->previousNode();
					break;
			
				case 2:
					GUI_Templates("M_Mode");
					browser->previousNode();
					break;

				case 3:
					GUI_Templates("edit");
					browser->nextNode();
					break;
			}
		}

		if (strinput == "dp")
		{
			if (menu_ID == 2)
			{
				GUI_Templates("M_Mode");
				std::cout << "Project Deleted" << std::endl;
				browser->delete_current();
			}
			
		}

		if (strinput == "crew")
		{
			switch (menu_ID)
			{
				case 1:
					GUI_Templates("B_Mode");
					browser->display_crew();
					break;
			
				case 2:
					GUI_Templates("M_Mode");
					browser->display_crew();
					break;
			}
		}

		if (strinput == "save" && menu_ID == 0)
		{
			GUI_Templates("Load_Main_Menu");
			std::cout << " Projects Saved   " << std::endl;
			fileHandler.UpdateFile();
			browser->setHead();
		}

		if((menu_ID == 3)||(strinput == "edit") && (menu_ID == 2))
		{
			menu_ID = 3;	
			//edit_data();
		}

		if (strinput == "insert")
		{
			FilmProject* new_film = new FilmProject;

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

void GUI::edit_data(std::string input)
{

	GUI_Templates("edit");

	std::cout << "Please enter the section you would like to edit (project,crew or material)";

	std::string edit_input = "";
	std::cin >> edit_input;	
	
	if (edit_input == "project")
	{
		GUI_Templates("edit");
		browser->display();
		std::cout << "Please enter in the ID of the project you want to edit" << std::endl;	
		std::cin >> edit_input;
		int project_ID = std::stoi (edit_input);
	}

	if (edit_input == "crew")
	{
		GUI_Templates("edit");
		browser->display_crew();
		std::cout << "Please enter in the ID of the crew member you want to edit" << std::endl;	
		std::cin >> edit_input;
		int project_ID = std::stoi (edit_input);
		
		


	}

	if (edit_input == "material")
	{
		std::cout << "Incomplete Yeet" << std::endl;
	}

}