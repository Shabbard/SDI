#include "GUI.h"

GUI::GUI(Browser *input, FileHandler* file)
{
	browser = input;
	fileHandler = file;
}

GUI::~GUI()
{

}

void GUI::Main_Menu_Templates()
{

	std::cout << "\n           TrekStar Production Log" << std::endl;
	std::cout << "______________________________________________" << std::endl;
	std::cout << "\n            Please Enter in a Value" << std::endl;		
	std::cout << "\nBrowser Mode                        Enter BM" << std::endl;
	std::cout << "Maintenance Mode                    Enter MM\n" << std::endl;
	std::cout << "Save                                Enter Save\n" << std::endl;
	std::cout << "Exit                                Enter Exit\n" << std::endl;
	std::cout << "______________________________________________\n" << std::endl;
}
void GUI::BM_Templates()
{
	std::cout << "\n          Welcome to Browser Mode" << std::endl;
	std::cout << "______________________________________________" << std::endl;		
	std::cout << "\n    Please Enter in a Value" << std::endl;		
	std::cout << "\nNext                                Enter Next" << std::endl;
	std::cout << "Back                                Enter Back" << std::endl;
	std::cout << "View Crew                           Enter Crew" << std::endl;
	std::cout << "View Material Info                  Enter MI" << std::endl;
	std::cout << "Search                              Enter Search\n" << std::endl; // Develop Search Engine to complete criteria of mojoo
	std::cout << "Return to Menu                      Enter RTM\n" << std::endl;
	std::cout << "______________________________________________\n" << std::endl;
	browser->display();
}
void GUI::MM_Templates()
{
	std::cout << "\n     Welcome to Maintenace Mode" << std::endl;
	std::cout << "______________________________________________" << std::endl;
	std::cout << "\nPlease Enter in a Value" << std::endl;		
	std::cout << "\nNext                                 Enter Next" << std::endl;
	std::cout << "Back                                 Enter Back" << std::endl;
	std::cout << "View Crew                            Enter Crew" << std::endl;
	std::cout << "View Material Info                   Enter MI\n" << std::endl;
	std::cout << "Create New Project                   Enter CNP" << std::endl;
	std::cout << "Edit                                 Enter EDIT" << std::endl;
	std::cout << "Delete Project                       Enter DP\n" << std::endl;
	std::cout << "Reports Mode                         Enter R\n" << std::endl;
	std::cout << "Return to Menu                       Enter RTM\n" << std::endl;
	std::cout << "______________________________________________\n" << std::endl;
	browser->display();
}

void GUI::CNP_Templates()
{
	std::cout << "\n              Add New Project" << std::endl;
	std::cout << "______________________________________________" << std::endl;
	std::cout << "\n   Please follow the instructions below" << std::endl;
	std::cout << "\n  Enter in the values as they are listed" << std::endl;
	std::cout << "\n        You may edit this later on" << std::endl;
	std::cout << "______________________________________________\n" << std::endl;
}

void GUI::Edit_Templates()
{
	std::cout << "\n           Welcome to Edit Mode" << std::endl;
	std::cout << "______________________________________________\n" << std::endl;
	std::cout << "Step 1: Enter in the database you want to edit\n" << std::endl;
	std::cout << "Step 2: Enter in the ID you want to edit\n" << std::endl;
	std::cout << "Step 3: Enter in the datatype you want ot edit\n " << std::endl;
	std::cout << "______________________________________________\n" << std::endl;
}

void GUI::Main_Menu()
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
			fileHandler->UpdateFile();
			browser->setHead();
		}

		if (strinput == "bm")
		{
			system("clear");
			BM_Templates();

			Browser_Menu();
		}

		if (strinput == "mm")
		{

			system("clear");
			MM_Templates();

			Maintenance_Menu();
		}

	} while (strinput != "exit");
}

void GUI::Browser_Menu()
{
	std::string strinput = "";

	do
	{
		std::cin >> strinput;

		std::transform(strinput.begin(), strinput.end(), strinput.begin(), ::tolower);

		Basic_User_Input(strinput);

		system("clear");
		BM_Templates();

		if (strinput == "crew")
		{
			browser->display_crew();
		}
		

	} while (strinput != "rtm");
}

void GUI::Maintenance_Menu()
{
	std::string strinput = "";

	do
	{

		std::cin >> strinput;

		std::transform(strinput.begin(), strinput.end(), strinput.begin(), ::tolower);

		Basic_User_Input(strinput);

		system("clear");
		MM_Templates();

		if (strinput == "crew")
		{
			browser->display_crew();
		}

		if (strinput == "mi")
		{
			browser->display_mat();
		}

		if (strinput == "edit")
		{
			Edit_Menu();
		}

		if (strinput == "dp")
		{
			MM_Templates();
			std::cout << "\nProject Deleted" << std::endl;
			browser->delete_current();
			system("clear");
			MM_Templates();
		}

		if (strinput == "cnp")
		{
			Create_New_Project_Menu();
		}

	} while (strinput != "rtm");
}

void GUI::Edit_Menu()
{

	std::string strinput = "";

	do
	{
		system("clear");
		Edit_Templates();

		std::cout << "Please enter the section you would like to edit " << std::endl;
		std::cout << "          (project,crew or material)            \n" << std::endl;
		std::cout << "- ";
		
		std::cin >> strinput;
		std::transform(strinput.begin(), strinput.end(), strinput.begin(), ::tolower);
	
		if (strinput == "project")
		{
			project_edit();
		}

		if (strinput == "crew")
		{
			crew_edit();
		}

		if (strinput == "material"||strinput == "materials")
		{
			material_edit();
		}
		

	} while (strinput != "rtm");
}

void GUI::project_edit()
{
	std::string edit_input = "";

	do
	{
		system("clear");
		Edit_Templates();
		std::cout << "\nNext                                Enter Next" << std::endl;
		std::cout << "Back                                Enter Back\n" << std::endl;
		std::cout << "Return to Menu                       Enter RTM\n" << std::endl;
		std::cout << "________________________________________________" << std::endl;	
		browser->display();
		
		std::cout << "Please enter in the ID of the project you want to edit\n" << std::endl;	

		std::cin >> edit_input;
		std::transform(edit_input.begin(), edit_input.end(), edit_input.begin(), ::tolower);

		if( edit_input.find_first_of("0987654321")!=std::string::npos )
		{
			Basic_User_Input(edit_input);
		}else{
			int project_ID = std::stoi (edit_input);
		}


	} while (edit_input != "rtm");
}

void GUI::crew_edit()
{
	system("clear");
}

void GUI::material_edit()
{
	system("clear");
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
}

int GUI::unique_id_check()
{
	int new_id = 0;

	browser->setHead();

	while (browser->current->next != nullptr)
	{
		if (new_id < browser->current->data->ID)
		{
			new_id = browser->current->data->ID;
		}

		browser->nextNode();
	}

	if (new_id < browser->current->data->ID)
	{
		new_id = browser->current->data->ID;
	}

    return ++new_id;
}

void GUI::Create_New_Project_Menu()
{
	std::string strinput = "";

	system("clear");
	CNP_Templates();

	std::string values[12] = {"Status", "Title", "Keywords", "Summary", "Genre", "Release Date", "Filming Locations", "Runtime", "Language", "Weekly Ticket Sales", "Crew Members"};

	FilmProject new_film;

	new_film.ID = unique_id_check();

	std::cout << "Unreleased 1, Now_Playing 2, Released 3\n";
	std::cout << "\nPlease insert a Status Number: ";
	std::cin >> new_film.Status;
	std::cout << "\nPlease insert a Title: ";
	std::cin >> new_film.Title;
	std::cout << "\nPlease insert the Keywords: " << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finished enter in (case sensitive) - Q" << std::endl;
	do
	{
		std::cin >> strinput;
		new_film.KeyWords.push_back(strinput);
	} while (strinput != "Q");
	std::cout << "\nPlease insert a Summary: ";
	std::cin >> new_film.Summary;
	std::cout << "\nPlease insert the Genres: " << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finished enter in (case sensitive) - Q" << std::endl;
	do
	{
		std::cin >> strinput;
		new_film.Genre.push_back(strinput);
	} while (strinput != "Q");
	std::cout << "\nPlease insert a Release Date: ";
	std::cin >> new_film.ReleaseDate;
	std::cout << "\nPlease insert the Filming Locations: " << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finished enter in (case sensitive) - Q" << std::endl;
	do
	{
		std::cin >> strinput;
		new_film.Filming_Locations.push_back(strinput);
	} while (strinput != "Q");
	std::cout << "\nPlease insert the Runtime: ";
	std::cin >> new_film.Runtime;
	std::cout << "\nPlease insert the Languages: " << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finished enter in (case sensitive) - Q" << std::endl;
	do
	{
		std::cin >> strinput;
		new_film.Languages.push_back(strinput);
	} while (strinput != "Q");
	std::cout << "\nPlease insert the Weekly Ticket Sale: ";
	std::cin >> new_film.WeeklyTicketSales;
	std::cout << "\nPlease insert Crew Memeber IDs" << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finihed enter in - Q" << std::endl;
	std::string tempStr;
	do
	{
		Crew temp;
		std::cin >> tempStr;
        if (tempStr != "Q")
		{
			temp.ID = std::stoi(tempStr);
			temp = fileHandler->LoadCrew(temp);
			new_film.CrewMembers.push_back(temp);
		}
	} while (tempStr != "Q");
	std::cout << "\nPlease insert the Material IDs" << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finihed enter in - Q" << std::endl;
    tempStr = "";
	do
	{
        Material* temp = new Material();
		std::cin >> tempStr;
        if (tempStr != "Q")
		{
			temp = fileHandler->GetMaterialType(temp, std::stoi(tempStr));
			temp = fileHandler->LoadMaterial(temp, temp->ID);
			new_film.Materials.push_back(temp);
		}
	} while (tempStr != "Q");
	FilmProject* filmToPass = &new_film;
	browser->insert_tail(filmToPass);
	system("clear");
	MM_Templates();

	Maintenance_Menu();
}
