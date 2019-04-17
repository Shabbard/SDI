#include "GUI.h"

GUI::GUI(Browser* input)
{
    browser = input;
}

GUI::~GUI()
{

}

void GUI::Main_Menu_Templates()
{

	std::cout << "\n   TrekStar Production Log" << std::endl;
	std::cout << "______________________________" << std::endl;
	std::cout << "\n  Please Enter in a Value" << std::endl;		
	std::cout << "\nBrowser Mode          Enter BM" << std::endl;
	std::cout << "Maintenance Mode      Enter MM\n" << std::endl;
	std::cout << "Save                  Enter Save\n" << std::endl;
	std::cout << "Exit                  Enter Exit\n" << std::endl;
	std::cout << "______________________________\n" << std::endl;
}
void GUI::BM_Templates()
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
	browser->display();
		
}
void GUI::MM_Templates()
{
	std::cout << "\n     Welcome to Maintenace Mode" << std::endl;
	std::cout << "______________________________________" << std::endl;
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

void GUI::CNP_Templates()
{
	std::cout << "\n          Add New Project" << std::endl;
	std::cout << "_______________________________________" << std::endl;
	std::cout << "\nPlease follow the instructions below" << std::endl;
	std::cout << "\nEnter in the values as they are listed" << std::endl;
	std::cout << "\n      You may edit this later on" << std::endl;
	std::cout << "_______________________________________\n" << std::endl;
}


void GUI::Edit_Templates()
{

}

int GUI::unique_id_check()
{
	int new_id = 0;

	
	browser->setHead();

    while(browser->current->next != nullptr)
	{	
		if (new_id > browser->current->data->ID)
		{
			new_id = browser->current->data->ID;
		}
        
		browser->nextNode();

	}

	return new_id++;
}

void GUI::Main_Menu(FileHandler fileHandler)
{
		
		std::string strinput = "";


	do 
	{
		system("clear");
		Main_Menu_Templates();

        std::cin >> strinput;

		std::transform(strinput.begin(), strinput.end(), strinput.begin(), ::tolower);

		if (strinput == "save")
		{
			system("clear");
			Main_Menu_Templates();
			std::cout << " Projects Saved   " << std::endl;
			fileHandler.UpdateFile();
			browser->setHead();
		}

		if(strinput == "bm")
		{
			Browser_Menu();
		}

		if (strinput == "mm")
		{
			Maintenance_Menu();
		}



	} while(strinput != "exit");
}



void GUI::Browser_Menu()
{
	std::string strinput = "";
	
	system("clear");
	BM_Templates();
	
	do 
	{
		std::cin >> strinput;

		system("clear");
		BM_Templates();
        
		std::transform(strinput.begin(), strinput.end(), strinput.begin(), ::tolower);
		
		Basic_User_Input(strinput);


	} while(strinput != "rtm");
}



void GUI::Maintenance_Menu()
{
	std::string strinput = "";

	system("clear");
	MM_Templates();

	do 
	{
		std::cin >> strinput;

		system("clear");
		MM_Templates();

		std::transform(strinput.begin(), strinput.end(), strinput.begin(), ::tolower);

		Basic_User_Input(strinput);

        if (strinput == "edit")
		{
			Edit_Menu();
		} 

		if (strinput == "dp")
		{
			MM_Templates();
			std::cout << "\nProject Deleted" << std::endl;
			browser->delete_current();	
		}

		if (strinput == "cnp")
		{
			Create_New_Project_Menu();
		}
	
	} while(strinput != "rtm");
}

void GUI::Create_New_Project_Menu()
{
	std::string strinput = "";

	system("clear");
	CNP_Templates();

	std::string values[12] = {"Status", "Title" , "Keywords" ,"Summary", "Genre", "Release Date", "Filming Locations", "Runtime", "Language", "Weekly Ticket Sales", "Crew Members"};

	Film* new_film = new Film;

	new_film->ID = unique_id_check();

	std::cout << "Unreleased 1, Now_Playing 2, Released 3\n";
	std::cout << "\nPlease insert a Status Number: ";
	std::cin >> new_film->Status;
	std::cout << "\nPlease insert a Title: ";
	std::cin >> new_film->Title;
	std::cout << "\nPlease insert the Keywords: " << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finihed enter in (case sensitive) - Q" << std::endl;
	do
	{
		std::cin >> strinput;
		new_film->KeyWords.push_back(strinput);
	} while(strinput != "Q");
	std::cout << "\nPlease insert a Summary: ";
	std::cin >> new_film->Summary;
	std::cout << "\nPlease insert the Genres: " << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finihed enter in (case sensitive) - Q" << std::endl;
	do
	{
		std::cin >> strinput;
		new_film->Genre.push_back(strinput);
	} while(strinput != "Q"); 
	std::cout << "\nPlease insert a Release Date: ";
	std::cin >> new_film->ReleaseDate;
	std::cout << "\nPlease insert the Filming Locations: " << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finihed enter in (case sensitive) - Q" << std::endl;
	do
	{
		std::cin >> strinput;
		new_film->Filming_Locations.push_back(strinput);
	} while(strinput != "Q");
	std::cout << "\nPlease insert the Runtime: ";
	std::cin >> new_film->Runtime;
	std::cout << "\nPlease insert the Languages: " << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finihed enter in (case sensitive) - Q" << std::endl;
	do
	{
		std::cin >> strinput;
		new_film->Languages.push_back(strinput);
	} while(strinput != "Q");
	std::cout << "\nPlease insert the Weekly Ticket Sale: ";
	std::cin >> new_film->WeeklyTicketSales;
	std::cout << "\nPlease insert Crew Memeber IDs" << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finihed enter in - 00" << std::endl;
	std::string tempStr;
	do
	{
		Crew temp;
		std::cin >> tempStr;
		temp.ID= std::stoi(tempStr);
		new_film->CrewMembers.push_back(temp);

	} while(tempStr != "00");

	browser->insert_tail(new_film);

	new_film = nullptr;

	Maintenance_Menu();
}


void GUI::Edit_Menu()
{

	std::string strinput = "";

	do 
	{
		system("clear");
		Edit_Menu();

        std::cin >> strinput;

		std::transform(strinput.begin(), strinput.end(), strinput.begin(), ::tolower);

		Basic_User_Input(strinput);
	
	} while(strinput != "exit");
}



void GUI::Basic_User_Input(std::string user_input)
{
	if (user_input == "rtm")
	{

		Main_Menu_Templates();
	}

	if (user_input == "next")
	{
		browser->nextNode();
	}

	if (user_input == "back")
	{
		browser->previousNode();
	}

	if (user_input == "mi")
	{
		std::cout << "Material View";
	}

	if (user_input == "crew")
	{
		browser->display_crew();
	}

}

