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
	std::cout << "Step 2: Enter in the datatype you want ot edit\n " << std::endl;
	std::cout << "Step 3: Make your changes\n " << std::endl;
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
		else if (strinput == "mi")
		{
			DisplayMaterials();
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
			DisplayMaterials();
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
		
		std::cout << "Please enter in the datatype you want to edit\n" << std::endl;	

		std::cin >> edit_input;
	
		std::transform(edit_input.begin(), edit_input.end(), edit_input.begin(), ::tolower);

		if( edit_input == "next" ||  edit_input == "previous" ||  edit_input == "rtm" )
		{
			Basic_User_Input(edit_input);
		}else
		{

			if(edit_input == "status")
			{
				std::cout << "\nUnreleased 1, Now_Playing 2, Released 3";
				std::cout << "\nPlease insert a Status Number : ";
				int status = 0;
				std::cin >> status;

				browser->current->data->Status = status;

			}

			if(edit_input == "title")
			{
				std::cout << "\nPlease Insert a project title : ";
				std::string title  = "";
				std::cin >> title;

				browser->current->data->Title = title;
			}

			if(edit_input == "keywords")
			{
				std::cout << "\n";
				int counter = 0;
				
				for(std::vector<std::string>::iterator it = browser->current->data->KeyWords.begin(); it != browser->current->data->KeyWords.end(); it++)
				{
					std::cout << counter << " - " << *it << "\n" ;
					counter++;
					
				}

				std::cout << "\n" <<counter <<  " - " << "Enter in this number to add a new value " << std::endl;
				std::cout << "000" <<  " - " << "Enter in this number to delete a value " << std::endl;
				
				std::cout <<"\nPlease Enter in a keywords number you want to edit\n";
				
				int keywords = 0;
				std::cin >> keywords;

				if( keywords == counter)
				{
					std::cout <<"\nPlease enter in the new keyword\n";

					std::string new_val;
					std::cin >> new_val;

					browser->current->data->KeyWords.push_back(new_val);


				}if(counter == 000){

					std::cout <<"\nPlease enter in the keyword number you want to delete\n";

					int new_val;
					std::cin >> new_val;

					browser->current->data->KeyWords.erase (browser->current->data->KeyWords.begin()+new_val);

				}else{
					std::cout <<"\nPlease enter in the edited keyword\n";

					std::string replace;
					std::cin >> replace;

					browser->current->data->KeyWords.at(keywords) = replace;
				}

			}

			if(edit_input == "summary")
			{
				std::cout << "\nPlease Insert a project summary : ";
				std::string summary  = "";
				std::cin >> summary;

				browser->current->data->Summary = summary;
			}

			if(edit_input == "genres")
			{
				std::cout << "\n";
				int counter = 0;
				
				for(std::vector<std::string>::iterator it = browser->current->data->Genre.begin(); it != browser->current->data->Genre.end(); it++)
				{
					std::cout << counter << " - " << *it << "\n" ;
					counter++;
				}

				std::cout << "\n" <<counter <<  " - " << "Enter in this number to add a new value " << std::endl;
				std::cout << "000" <<  " - " << "Enter in this number to delete a value " << std::endl;
				
				std::cout <<"\nPlease Enter in a Genre number you want to edit\n";
				
				int Genre = 0;
				std::cin >> Genre;

				if( Genre == counter)
				{
					std::cout <<"\nPlease enter in the new Genre\n";

					std::string new_val;
					std::cin >> new_val;

					browser->current->data->Genre.push_back(new_val);


				}if(Genre == 000){

					std::cout <<"\nPlease enter in the Genre number you want to delete\n";

					int new_val;
					std::cin >> new_val;

					browser->current->data->Genre.erase (browser->current->data->Genre.begin()+new_val);

				}else{
					std::cout <<"\nPlease enter in the edited Genre\n";

					std::string replace;
					std::cin >> replace;

					browser->current->data->Genre.at(Genre) = replace;
				}
			}

			if(edit_input == "release date")
			{
				std::cout << "\nPlease Insert a project release date : ";
				std::string title  = "";
				std::cin >> title;

				browser->current->data->ReleaseDate = title;
			}

			if(edit_input == "filming locations")
			{
				std::cout << "\n";
				int counter = 0;
				
				for(std::vector<std::string>::iterator it = browser->current->data->Filming_Locations.begin(); it != browser->current->data->Filming_Locations.end(); it++)
				{
					std::cout << counter << " - " << *it << "\n" ;
					counter++;
				}

				std::cout << "\n" <<counter <<  " - " << "Enter in this number to add a new value " << std::endl;
				std::cout << "000" <<  " - " << "Enter in this number to delete a value " << std::endl;
				
				std::cout <<"\nPlease Enter in a Location number you want to edit\n";
				
				int Location = 0;
				std::cin >> Location;

				if( Location == counter)
				{
					std::cout <<"\nPlease enter in the new keyword\n";

					std::string new_val;
					std::cin >> new_val;

					browser->current->data->Filming_Locations.push_back(new_val);


				}if(Location == 000){

					std::cout <<"\nPlease enter in the keyword number you want to delete\n";

					int new_val;
					std::cin >> new_val;

					browser->current->data->Filming_Locations.erase (browser->current->data->Filming_Locations.begin()+new_val);

				}else{
					std::cout <<"\nPlease enter in the edited keyword\n";

					std::string replace;
					std::cin >> replace;

					browser->current->data->Filming_Locations.at(Location) = replace;
				}
			}

			if(edit_input == "runtime")
			{
				std::cout << "\nPlease insert a runtime : ";
				int runtime = 0;
				std::cin >> runtime;

				browser->current->data->Runtime = runtime;
			}

			if(edit_input == "languages")
			{
							
				std::cout << "\n";
				int counter = 0;
				
				for(std::vector<std::string>::iterator it = browser->current->data->Languages.begin(); it != browser->current->data->Languages.end(); it++)
				{
					std::cout << counter << " - " << *it << "\n" ;
					counter++;
				}

				std::cout << "\n" <<counter <<  " - " << "Enter in this number to add a new value " << std::endl;
				std::cout << "000" <<  " - " << "Enter in this number to delete a value " << std::endl;
				
				std::cout <<"\nPlease Enter in a Location number you want to edit\n";
				
				int Languages = 0;
				std::cin >> Languages;

				if( Languages == counter)
				{
					std::cout <<"\nPlease enter in the new keyword\n";

					std::string new_val;
					std::cin >> new_val;

					browser->current->data->Languages.push_back(new_val);


				}if(Languages == 000){

					std::cout <<"\nPlease enter in the keyword number you want to delete\n";

					int new_val;
					std::cin >> new_val;

					browser->current->data->Languages.erase (browser->current->data->Languages.begin()+new_val);

				}else{
					std::cout <<"\nPlease enter in the edited keyword\n";

					std::string replace;
					std::cin >> replace;

					browser->current->data->Languages.at(Languages) = replace;
				}
			
			}

			if(edit_input == "weekly box office")
			{
				std::cout << "\nPlease insert a runtime : ";
				int WeeklyTicketSales = 0;
				std::cin >> WeeklyTicketSales;

				browser->current->data->WeeklyTicketSales.push_back(WeeklyTicketSales);
			}

			if(edit_input == "crew member ID")
			{

			}
		}

	} while (edit_input != "rtm");
}

void GUI::LoadMatData(Material* mat, std::string strvar)
{

	std::cout << strvar << "ID" << "\t\t\t" << mat->ID << std::endl;
	std::cout << strvar << "Type" << "\t\t\t" << mat->Type << std::endl;
	std::cout << strvar << "Title" << "\t\t\t" << mat->Title << std::endl;
	std::cout << strvar << "DVD Description" << "\t\t" << mat->Description << std::endl;
	std::cout << strvar << "Video Format" << "\t\t" << mat->VideoFormat << std::endl;
	std::cout << strvar << "Audio Format" << "\t\t" << mat->AudioFormat << std::endl;
	std::cout << strvar << "Runtime" << "\t\t\t" << mat->Runtime << std::endl;
	std::cout << strvar << "Languages" << "\t\t";
	if (mat->Type == "VHS")
	{
		std::cout << strvar << mat->GetLanguage(0);
	}
	else
	{
		for(size_t i = 0; i != mat->GetNumLanguages(); i++)
		{
			std::cout << mat->GetLanguage(i) << ",";
		}
		std::cout << std::endl;
	}
	std::cout << strvar << "Retail Price" << "\t\t" << mat->RetailPrice << std::endl;
	std::cout << strvar << "Subtitles" << "\t\t";
	if (mat->Type == "VHS")
	{
		std::cout << strvar << mat->GetSubtitle(0);
	}
	else
	{
		for(size_t i = 0; i != mat->GetNumSubtitles(); i++)
		{
			std::cout << mat->GetSubtitle(i) << ",";
		}
		std::cout << std::endl;
	}
	std::cout << strvar <<"Frame Aspect" << "\t\t" << mat->FrameAspect << std::endl;
	std::cout << strvar <<"Packaging" << "\t\t" << mat->Packaging << std::endl;
	std::cout << std::endl;

	if(mat->Type != "ComboBox")
	{
//		for(size_t i = 0; i != mat->(); i++)
//		{
//			std::cout << mat->GetSubtitle(i) << ",";
//		}
//		std::cout << std::endl;
	}
}

void GUI::DisplayMaterials()
{
	std::cout << "___________________________________\n" << std::endl;
   	std::cout << "              Materials              " << "\n"<< std::endl;
	
   	for(std::vector<Material*>::iterator it = browser->current->data->Materials.begin(); it != browser->current->data->Materials.end(); it++)
	{
		LoadMatData(*it, "");
		Material* mat = *it;
		if (mat->Type == "ComboBox")
		{
			std::vector<Material*> ComboBoxStored = mat->GetDVDs();
			for (size_t i = 0; i != ComboBoxStored.size(); ++i)
			{
				LoadMatData(ComboBoxStored.at(i), "\t\t");
			}
		}
	}


   std::cout << "\n";
}

void GUI::crew_edit()
{
	system("clear");

	// Display all crew maybe in increments?? With Scrubbing 
	// Request ID for change
	// Request Datatype to change
	// Offer Delete, Edit
	// Return to edit menu

	// Crew Member ID , Name , Job 
}

void GUI::material_edit()
{
	// Adams display
	system("clear");
}

void GUI::Basic_User_Input(std::string user_input)
{
	if (user_input == "rtm")
	{
		GUI::Main_Menu();
		system("clear");
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
//	std::cin >> new_film.WeeklyTicketSales;
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
