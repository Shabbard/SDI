#include "GUI.h"

GUI::GUI(Browser *input, FileHandler *file)
{
	browser = input;
	fileHandler = file;
}

GUI::~GUI()
{
}

void GUI::LoadCrew()
{
	crewVector = fileHandler->LoadEntireCrew();
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
	DisplayCurrentFilmProject();
}
void GUI::MM_Templates()
{
	std::cout << "\n     Welcome to Maintenace Mode" << std::endl;
	std::cout << "______________________________________________" << std::endl;
	std::cout << "\nPlease Enter in a Value" << std::endl;
	std::cout << "\nNext                               Enter Next" << std::endl;
	std::cout << "Back                                 Enter Back" << std::endl;
	std::cout << "View Crew                            Enter Crew" << std::endl;
	std::cout << "View Material Info                   Enter MI\n" << std::endl;
	std::cout << "Create New Project                   Enter CNP" << std::endl;
	std::cout << "Create New Crew                      Enter CNC" << std::endl;
	std::cout << "Edit                                 Enter EDIT" << std::endl;
	std::cout << "Delete Project                       Enter DP\n" << std::endl;
	std::cout << "Reports Mode                         Enter R\n" << std::endl;
	std::cout << "Return to Menu                       Enter RTM\n" << std::endl;
	std::cout << "______________________________________________\n" << std::endl;
	DisplayCurrentFilmProject();
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
	std::string user_input = "";

	do
	{
		system("clear");
		Main_Menu_Templates();

		std::getline(std::cin, user_input);
		std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);

		if (user_input == "save")
		{
			system("clear");
			Main_Menu_Templates();
			SaveAllFiles();
			std::cout << " Projects Saved   " << std::endl;
		}
		if (user_input == "bm")
		{
			system("clear");
			BM_Templates();
			Browser_Menu();
		}
		if (user_input == "mm")
		{
			system("clear");
			MM_Templates();
			Maintenance_Menu();
		}

	} while (user_input != "exit");
	SaveAllFiles();
}

void GUI::SaveAllFiles()
{
	fileHandler->UpdateProjectFile();
	fileHandler->WriteCrewToFile(crewVector);
	browser->setHead();
}

void GUI::Browser_Menu()
{
	std::string user_input = "";

	do
	{
		std::getline(std::cin, user_input);

		std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);

		Basic_User_Input(user_input);

		system("clear");
		BM_Templates();

		if (user_input == "crew")
		{
			DisplayCrew();
		}
		else if (user_input == "mi")
		{
			DisplayMaterials();
		}

	} while (user_input != "rtm");
}

void GUI::Maintenance_Menu()
{
	std::string user_input;

	do
	{
		std::getline(std::cin, user_input);

		std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);

		Basic_User_Input(user_input);

		system("clear");
		MM_Templates();

		if (user_input == "crew")
		{
			DisplayCrew();
		}

		if (user_input == "mi")
		{
			DisplayMaterials();
		}

		if (user_input == "edit")
		{
			Edit_Menu();
		}

		if (user_input == "dp")
		{
			MM_Templates();
			std::cout << "\nProject Deleted" << std::endl;
			browser->delete_current();
			system("clear");
			MM_Templates();
		}

		if (user_input == "cnp")
		{
			Create_New_Project_Menu();
		}

		if (user_input == "cnc")
		{
			CreateNewCrew();
		}

	} while (user_input != "rtm");
	user_input = "";
}

void GUI::Edit_Menu()
{

	std::string user_input = "";

	do
	{
		system("clear");
		Edit_Templates();

		std::cout << "Please enter the section you would like to edit " << std::endl;
		std::cout << "          (project,crew or material)            \n"
				  << std::endl;
		std::cout << "- ";

		std::getline(std::cin, user_input);
		std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);

		if (user_input == "project")
		{
			project_edit();
		}

		if (user_input == "crew")
		{
			crew_edit();
		}

		if (user_input == "material" || user_input == "materials")
		{
			material_edit();
		}

	} while (user_input != "rtm");
}

void GUI::project_edit()
{
	std::string edit_input = "";

	do
	{
		system("clear");
		Edit_Templates();

		std::cout << "\nNext                                Enter Next" << std::endl;
		std::cout << "Back                                Enter Back\n"
				  << std::endl;
		std::cout << "Return to Menu                       Enter RTM\n"
				  << std::endl;
		std::cout << "________________________________________________" << std::endl;

		DisplayCurrentFilmProject();

		std::cout << "Please enter in the datatype you want to edit\n"
				  << std::endl;

		std::getline(std::cin, edit_input);

		std::transform(edit_input.begin(), edit_input.end(), edit_input.begin(), ::tolower);

		if (edit_input == "next" || edit_input == "previous" || edit_input == "rtm")
		{
			Basic_User_Input(edit_input);
		}
		else
		{

			if (edit_input == "status")
			{
				std::cout << "\nUnreleased 1, Now_Playing 2, Released 3";
				std::cout << "\nPlease insert a Status Number : ";
				std::string strStatus;
				std::getline(std::cin, strStatus);
				int status = std::stoi(strStatus);

				browser->current->data->Status = status;
			}

			if (edit_input == "title")
			{
				std::cout << "\nPlease Insert a project title : ";
				std::string title = "";
				std::getline(std::cin, title);

				browser->current->data->Title = title;
			}

			if (edit_input == "keywords")
			{
				std::cout << "\n";
				int counter = 0;

				for (auto it = browser->current->data->KeyWords.begin(); it != browser->current->data->KeyWords.end(); ++it)
				{
					std::cout << counter << " - " << *it << "\n";
					counter++;
				}

				std::cout << "\n"
						  << counter << " - "
						  << "Enter in this number to add a new value " << std::endl;
				std::cout << "000"
						  << " - "
						  << "Enter in this number to delete a value " << std::endl;

				std::cout << "\nPlease Enter in a keywords number you want to edit\n";

				std::string strKeywords;
				std::getline(std::cin, strKeywords);
				int keywords = std::stoi(strKeywords);

				if (keywords == counter)
				{
					std::cout << "\nPlease enter in the new keyword\n";

					std::string new_val;
					std::getline(std::cin, new_val);

					browser->current->data->KeyWords.push_back(new_val);
				}
				if (counter == 000)
				{

					std::cout << "\nPlease enter in the keyword number you want to delete\n";

					std::string strNew_val;
					std::getline(std::cin, strNew_val);
					int new_val = std::stoi(strNew_val);

					browser->current->data->KeyWords.erase(browser->current->data->KeyWords.begin() + new_val);
				}
				else
				{
					std::cout << "\nPlease enter in the edited keyword\n";

					std::string replace;
					std::getline(std::cin, replace);

					browser->current->data->KeyWords.at(keywords) = replace;
				}
			}

			if (edit_input == "summary")
			{
				std::cout << "\nPlease Insert a project summary : ";
				std::string summary = "";
				std::getline(std::cin, summary);

				browser->current->data->Summary = summary;
			}

			if (edit_input == "genres")
			{
				std::cout << "\n";
				int counter = 0;

				for (auto it = browser->current->data->Genre.begin(); it != browser->current->data->Genre.end(); ++it)
				{
					std::cout << counter << " - " << *it << "\n";
					counter++;
				}

				std::cout << "\n"
						  << counter << " - "
						  << "Enter in this number to add a new value " << std::endl;
				std::cout << "000"
						  << " - "
						  << "Enter in this number to delete a value " << std::endl;

				std::cout << "\nPlease Enter in a Genre number you want to edit\n";

				std::string strGenre;
				std::getline(std::cin, strGenre);
				int Genre = std::stoi(strGenre);

				if (Genre == counter)
				{
					std::cout << "\nPlease enter in the new Genre\n";

					std::string new_val;
					std::getline(std::cin, new_val);

					browser->current->data->Genre.push_back(new_val);
				}
				if (Genre == 000)
				{

					std::cout << "\nPlease enter in the Genre number you want to delete\n";

					std::string strNew_val;
					std::getline(std::cin, strNew_val);
					int new_val = std::stoi(strNew_val);

					browser->current->data->Genre.erase(browser->current->data->Genre.begin() + new_val);
				}
				else
				{
					std::cout << "\nPlease enter in the edited Genre\n";
					std::string replace;
					std::getline(std::cin, replace);

					browser->current->data->Genre.at(Genre) = replace;
				}
			}

			if (edit_input == "release date")
			{
				std::cout << "\nPlease Insert a project release date : ";
				std::string title = "";
				std::getline(std::cin, title);

				browser->current->data->ReleaseDate = title;
			}

			if (edit_input == "filming locations")
			{
				std::cout << "\n";
				int counter = 0;

				for (auto it = browser->current->data->Filming_Locations.begin(); it != browser->current->data->Filming_Locations.end(); ++it)
				{
					std::cout << counter << " - " << *it << "\n";
					counter++;
				}

				std::cout << "\n"
						  << counter << " - "
						  << "Enter in this number to add a new value " << std::endl;
				std::cout << "000"
						  << " - "
						  << "Enter in this number to delete a value " << std::endl;

				std::cout << "\nPlease Enter in a Location number you want to edit\n";

				std::string strLocation;
				std::getline(std::cin, strLocation);
				int Location = std::stoi(strLocation);

				if (Location == counter)
				{
					std::cout << "\nPlease enter in the new keyword\n";

					std::string new_val;
					std::getline(std::cin, new_val);

					browser->current->data->Filming_Locations.push_back(new_val);
				}
				if (Location == 000)
				{

					std::cout << "\nPlease enter in the keyword number you want to delete\n";

					std::string strNew_val;
					std::getline(std::cin, strNew_val);
					int new_val = std::stoi(strNew_val);

					browser->current->data->Filming_Locations.erase(browser->current->data->Filming_Locations.begin() + new_val);
				}
				else
				{
					std::cout << "\nPlease enter in the edited keyword\n";

					std::string replace;
					std::getline(std::cin, replace);

					browser->current->data->Filming_Locations.at(Location) = replace;
				}
			}

			if (edit_input == "runtime")
			{
				std::cout << "\nPlease insert a runtime : ";
				std::string strRuntime;
				std::getline(std::cin, strRuntime);
				int Runtime = std::stoi(strRuntime);
				browser->current->data->Runtime = Runtime;
			}

			if (edit_input == "languages")
			{

				std::cout << "\n";
				int counter = 0;

				for (auto it = browser->current->data->Languages.begin(); it != browser->current->data->Languages.end(); ++it)
				{
					std::cout << counter << " - " << *it << "\n";
					counter++;
				}

				std::cout << "\n"
						  << counter << " - "
						  << "Enter in this number to add a new value " << std::endl;
				std::cout << "000"
						  << " - "
						  << "Enter in this number to delete a value " << std::endl;

				std::cout << "\nPlease Enter in a Location number you want to edit\n";

				std::string strLanguages;
				std::getline(std::cin, strLanguages);
				int Languages = std::stoi(strLanguages);

				if (Languages == counter)
				{
					std::cout << "\nPlease enter in the new keyword\n";

					std::string new_val;
					std::getline(std::cin, new_val);

					browser->current->data->Languages.push_back(new_val);
				}
				if (Languages == 000)
				{

					std::cout << "\nPlease enter in the keyword number you want to delete\n";

					std::string strNew_val;
					std::getline(std::cin, strNew_val);
					int new_val = std::stoi(strNew_val);

					browser->current->data->Languages.erase(browser->current->data->Languages.begin() + new_val);
				}
				else
				{
					std::cout << "\nPlease enter in the edited keyword\n";

					std::string replace;
					std::getline(std::cin, replace);

					browser->current->data->Languages.at(Languages) = replace;
				}
			}

			if (edit_input == "weekly box office")
			{
				std::cout << "\nPlease insert a runtime : ";
				std::string strWeeklyTicketSales;
				std::getline(std::cin, strWeeklyTicketSales);
				int WeeklyTicketSales = std::stoi(strWeeklyTicketSales);

				browser->current->data->WeeklyTicketSales.push_back(WeeklyTicketSales);
			}

			if (edit_input == "crew member ID")
			{
			}
		}

	} while (edit_input != "rtm");
}


void GUI::crew_edit()
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
		
		//browser->display_all_crew();

		std::cin >> edit_input;

	}while(edit_input != "rtm");

	// Display all crew maybe in increments?? With Scrubbing 
	// Request ID for change
	// Request Datatype to change
	// Offer Delete, Edit
	// Return to edit menu

	// Crew Member ID , Name , Job 

}

void GUI::material_edit()
{

	system("clear");

	std::string edit_input = "";

	do
	{

		system("clear");
		Edit_Templates();
		
		std::cout << "\nNext                                Enter Next" << std::endl;
		std::cout << "Back                                Enter Back\n" << std::endl;
		std::cout << "Return to Menu                       Enter RTM\n" << std::endl;
		
		DisplayMaterials();

		std::cout << "Please enter in the ID of the material\n" << std::endl;	

		std::cin >> edit_input;

		bool interger_val, string_val = false;

		for(auto it = edit_input.begin(); it != edit_input.end(); ++it)
		{
			if (isalpha(*it))
			{
				string_val = true;
			}

			if (isdigit(*it))
			{
				interger_val = true;
			}
		}

		if(interger_val == true && string_val == false)
		{
			int material_ID = std::stoi(edit_input);
			material_edit_management(material_ID);
		}

		if(interger_val == false  && string_val == true)
		{

			std::transform(edit_input.begin(), edit_input.end(), edit_input.begin(), ::tolower);

			if( edit_input == "next" ||  edit_input == "previous" ||  edit_input == "rtm" )
			{
				Basic_User_Input(edit_input);
			}
		}

		std::cin >> edit_input;

	}while(edit_input != "rtm");
}

void GUI::material_edit_management(int material_ID)
{

	system("clear");

	std::string edit_input = "";

	do
	{
		std::cout << "________________________________________________" << std::endl;
		std::cout << "\n         Please Enter in the value " << std::endl;
		std::cout << "           you would like to change  " << std::endl;

		int id;

		for (auto it = browser->current->data->Materials.begin(); it != browser->current->data->Materials.end(); ++it)
		{
			//id = (*it).ID;

			std::cout << id;
		}

		
	} while (edit_input != "rtm");
	
}


// ID,3
// Type,DVD
// Title,Avatar - End Game.
// DVD_Description,Dead Avatar.
// Video_Format,1080p
// Audio_Format,WAV
// Run_Time,160
// Languages,English,French,Spanish
// Retail_Price,30
// Subtitles,English,French,Spanish
// Frame_Aspect,16:9
// Bonus_Features,Directors Cut
// Packaging,Plastic
// Stored,4
		

void GUI::LoadMatData(Material* mat, std::string strvar)
{
	std::cout << strvar << "________________________________________________\n"
			  << std::endl;
	std::cout << strvar << "ID"
			  << "\t\t\t" << mat->ID << "\n"
			  << std::endl;
	std::cout << strvar << "Title"
			  << "\t\t\t" << mat->Title << std::endl;
	std::cout << strvar << "Type"
			  << "\t\t\t" << mat->Type << std::endl;
	std::cout << strvar << "DVD Description"
			  << "\t\t" << mat->Description << std::endl;
	std::cout << strvar << "Video Format"
			  << "\t\t" << mat->VideoFormat << std::endl;
	std::cout << strvar << "Audio Format"
			  << "\t\t" << mat->AudioFormat << std::endl;
	std::cout << strvar << "Runtime"
			  << "\t\t\t" << mat->Runtime << std::endl;
	std::cout << strvar << "Languages"
			  << "\t\t";
	if (mat->Type == "VHS")
	{
		std::cout << strvar << mat->GetLanguage(0);
	}
	else
	{
		for (size_t i = 0; i != mat->GetNumLanguages(); i++)
		{
			std::cout << mat->GetLanguage(i) << ",";
		}
		std::cout << std::endl;
	}
	std::cout << strvar << "Retail Price"
			  << "\t\t" << mat->RetailPrice << std::endl;
	std::cout << strvar << "Subtitles"
			  << "\t\t";
	if (mat->Type == "VHS")
	{
		std::cout << strvar << mat->GetSubtitle(0);
	}
	else
	{
		for (size_t i = 0; i != mat->GetNumSubtitles(); i++)
		{
			std::cout << mat->GetSubtitle(i) << ",";
		}
		std::cout << std::endl;
	}
	std::cout << strvar << "Frame Aspect"
			  << "\t\t" << mat->FrameAspect << std::endl;
	if (mat->Type == "DVD" || mat->Type == "BluRay")
	{
		std::cout << strvar << "Bonus Features"
				  << "\t\t";
		for (size_t i = 0; i != mat->GetNumBonusFeatures(); i++)
		{
			std::cout << mat->GetBonusFeature(i) << ",";
		}
		std::cout << std::endl;
	}
	std::cout << strvar << "Packaging"
			  << "\t\t" << mat->Packaging << std::endl;
	std::cout << std::endl;

	if (mat->Type == "DoubleSidedDVD")
	{
		std::pair<Material *, Material *> DoubleDVD = mat->GetDVDPair();
		LoadMatData(DoubleDVD.first, "\t\t\t\t");
		LoadMatData(DoubleDVD.second, "\t\t\t\t");
	}
}

void GUI::CreateNewCrew()
{
	std::cout << "________________________________________________\n\n" << std::endl;
	std::cout << "           Create New Crew Member                 " << "\n" << std::endl;

	Crew new_crew;
	new_crew.ID = unique_id_check_crew();

	std::string user_input;
	std::cout << "\nPlease insert the Crew Members Name: ";
	std::getline(std::cin, new_crew.Name);
	std::cout << "\nPlease insert the Crew Members Job: ";
	std::getline(std::cin, new_crew.Job);
	crewVector.push_back(new_crew);

	system("clear");
	MM_Templates();
}

void GUI::CreateNewMaterial()
{
	std::cout << "________________________________________________\n\n" << std::endl;
	std::cout << "              Create New Material                 " << "\n" << std::endl;

	Material* new_mat = new Material();

	new_mat->ID = unique_id_check_material();


}

void GUI::DisplayMaterials()
{
	std::cout << "________________________________________________\n\n"
			  << std::endl;
	std::cout << "                     Materials                 "
			  << "\n"
			  << std::endl;

	for (std::vector<Material *>::iterator it = browser->current->data->Materials.begin(); it != browser->current->data->Materials.end(); ++it)
	{
		LoadMatData(*it, "");
		Material *mat = *it;
		if (mat->Type == "ComboBox")
		{
			for (auto iter = mat->GetDVDs().begin(); iter != mat->GetDVDs().end(); ++iter)
			{
				LoadMatData((*iter), "\t\t");
			}
		}
	}

	std::cout << "\n";
}

void GUI::Basic_User_Input(std::string user_input)
{
	if (user_input == "next")
	{
		browser->nextNode();
	}

	if (user_input == "back")
	{
		browser->previousNode();
	}
}

int GUI::unique_id_check_project()
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

int GUI::unique_id_check_material()
{
	int new_id = 0;

	browser->setHead();

	while (browser->current->next != nullptr)
	{

		for (auto it = browser->current->data->Materials.begin(); it != browser->current->data->Materials.end(); ++it)
		{
			if (new_id < (*it)->ID)
			{
				new_id = (*it)->ID;
			}
		}
		browser->nextNode();
	}
	for (auto it = browser->current->data->Materials.begin(); it != browser->current->data->Materials.end(); ++it)
	{
		if (new_id < (*it)->ID)
		{
			new_id = (*it)->ID;
		}
	}
	
	return ++new_id;
}

int GUI::unique_id_check_crew()
{
	int new_id = 0;

	for (auto it = crewVector.begin(); it != crewVector.end(); ++it)
	{
		if ((*it).ID > new_id)
		{
			new_id = (*it).ID;
		}
	}
	return ++new_id;
}

void GUI::DisplayCrew()
{
	std::cout << "___________________________________\n" << std::endl;
   	std::cout << "            Crew Members             " << "\n"<< std::endl;
   	std::cout << " ID             Name            Job\n" << std::endl;
   	for(auto it = browser->current->data->CrewMembers.begin(); it != browser->current->data->CrewMembers.end(); ++it)
	{   
      	std::cout << "- " << (*it).ID<< "\t"<< (*it).Name << "\t\t" << (*it).Job << std::endl;
	}
   	std::cout << "\n";
}

void GUI::DisplayCurrentFilmProject()
{
	std::cout << "        Project Data " << std::endl;
   std::cout << "Datatype"<< "\t\t" << "Data\n" << std::endl;
   std::cout << "ID" << "\t\t\t"<< browser->current->data->ID << std::endl;
   switch (browser->current->data->Status)
   {
      case FilmProject::Status::Unreleased:
         std::cout << "Status" << "\t\t\t"<< "Unreleased" << std::endl;
         break;
      case FilmProject::Status::Now_Playing:
         std::cout << "Status" << "\t\t\t"<< "Now Playing" << std::endl;
         break;
      case FilmProject::Status::Released:
         std::cout << "Status" << "\t\t\t"<< "Released" << std::endl;
         break;
   
      default:
         break;
   }
	std::cout << "Title" << "\t\t\t"<< browser->current->data->Title << std::endl;
	std::cout << "Keywords"<< "\t\t";
	for(auto it = browser->current->data->KeyWords.begin(); it != browser->current->data->KeyWords.end(); ++it)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Summary" << "\t\t\t"<< browser->current->data->Summary << std::endl;
	std::cout << "Genre"<< "\t\t\t";
	for(auto it = browser->current->data->Genre.begin(); it != browser->current->data->Genre.end(); ++it)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Release_Date" << "\t\t"<< browser->current->data->ReleaseDate << std::endl;
	std::cout << "Filming_Loc"<< "\t\t";
	for(auto it = browser->current->data->Filming_Locations.begin(); it != browser->current->data->Filming_Locations.end(); ++it)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Runtime" << "\t\t\t"<< browser->current->data->Runtime << " Minutes "<< std::endl;
	std::cout << "Language"<< "\t\t";
	for(auto it = browser->current->data->Languages.begin(); it != browser->current->data->Languages.end(); ++it)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	if (browser->current->data->Status == 1)
	{
		std::cout << "Weekly Ticket Sales," << "\t" << "£";
		for (auto it = browser->current->data->WeeklyTicketSales.begin(); it != browser->current->data->WeeklyTicketSales.end(); ++it)
		{
			std::cout << *it << ",";
		}
		std::cout << std::endl;
	}
   	std::cout << "Crew Member ID's" << "\t";
	for(auto it = browser->current->data->CrewMembers.begin(); it != browser->current->data->CrewMembers.end(); ++it)
	{
		std::cout << (*it).ID << ",";
	}
   	std::cout << std::endl;
	if (browser->current->data->Status == 2)
	{
		std::cout << "Material ID's" << "\t\t";
		for(auto it = browser->current->data->Materials.begin(); it != browser->current->data->Materials.end(); ++it)
		{
			std::cout << (*it)->ID << ",";
		}
		std::cout << std::endl;
	}
   	std::cout << std::endl;
}

void GUI::Create_New_Project_Menu()
{
	system("clear");
	CNP_Templates();

	//std::string values[12] = {"Status", "Title", "Keywords", "Summary", "Genre", "Release Date", "Filming Locations", "Runtime", "Language", "Weekly Ticket Sales", "Crew Members"};

	FilmProject new_film;

	new_film.ID = unique_id_check_project();

	std::string user_input;
	bool success;
	std::cout << "\nUnreleased 1, Now_Playing 2, Released 3\n";
	success = false;
	while (success == false)
	{
		std::cout << "\nPlease insert a Status Number: ";
		std::getline(std::cin, user_input);
		try
		{
			new_film.Status = std::stoi(user_input);
			if (new_film.Status > 3 || new_film.Status < 0)
			{
				throw std::invalid_argument("Wrong value entered");
			}
			else
			{
				success = true;
			}
		}
		catch(const std::exception& e)
		{
			std::cout << "Please enter a correct number" << '\n';
			success = false;
		}
	}
	std::cout << "\nPlease insert a Title: ";
	std::getline(std::cin, new_film.Title);
	std::cout << "\nPlease insert the Keywords: " << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finished enter in (case sensitive) - Q" << std::endl;
	do
	{
		std::getline(std::cin, user_input);
		new_film.KeyWords.push_back(user_input);
	} while (user_input != "Q");
	std::cout << "\nPlease insert a Summary: ";
	std::getline(std::cin, new_film.Summary);
	std::cout << "\nPlease insert the Genres: " << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finished enter in (case sensitive) - Q" << std::endl;
	do
	{
		std::getline(std::cin, user_input);
		new_film.Genre.push_back(user_input);
	} while (user_input != "Q");
	std::cout << "\nPlease insert a Release Date: ";
	std::getline(std::cin, new_film.ReleaseDate);
	std::cout << "\nPlease insert the Filming Locations: " << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finished enter in (case sensitive) - Q" << std::endl;
	do
	{
		std::getline(std::cin, user_input);
		new_film.Filming_Locations.push_back(user_input);
	} while (user_input != "Q");
	success = false;
	while (success == false)
	{
		std::cout << "\nPlease insert the Runtime: ";
		std::getline(std::cin, user_input);
		try
		{
			new_film.Runtime = std::stoi(user_input);
			success = true;
		}
		catch(const std::exception& e)
		{
			std::cout << "Please enter a number" << '\n';
			success = false;
		}
	}	
	std::cout << "\nPlease insert the Languages: " << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finished enter in (case sensitive) - Q" << std::endl;
	do
	{
		std::getline(std::cin, user_input);
		new_film.Languages.push_back(user_input);
	} while (user_input != "Q");
	if (new_film.Status == 1)
	{
		success = false;
		while (success == false)
		{
			std::cout << "\nPlease insert the Weekly Ticket Sale: ";
			std::getline(std::cin, user_input);
			try
			{
				new_film.WeeklyTicketSales.push_back(std::stod(user_input));
				success = true;
			}
			catch(const std::exception& e)
			{
				std::cout << "Please enter a number" << '\n';
				success = false;
			}
		}
	}
	std::cout << "\nPlease insert Crew Memeber IDs" << std::endl;
	std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finihed enter in - Q" << std::endl;
	std::string tempStr;
	do
	{
		Crew new_crew;
		std::getline(std::cin, tempStr);
		if (tempStr != "Q")
		{
			new_crew.ID = std::stoi(tempStr);
			new_crew = fileHandler->LoadCrew(new_crew);
			new_film.CrewMembers.push_back(new_crew);
		}
	} while (tempStr != "Q");
	if (new_film.Status == 2)
	{	
		std::cout << "\nPlease insert the Material IDs" << std::endl;
		std::cout << "Type in the value then press enter to add another value" << std::endl;
		std::cout << "When you have finihed enter in - Q" << std::endl;
		tempStr = "";
		do
		{
			Material* new_mat = new Material();
			//std::getline(std::cin, )>> tempStr;
			if (tempStr != "Q")
			{
				new_mat = fileHandler->GetMaterialType(new_mat, std::stoi(tempStr));
				new_mat = fileHandler->LoadMaterial(new_mat, new_mat->ID);
				new_film.Materials.push_back(new_mat);
			}
		} while (tempStr != "Q");
	}
	
	FilmProject *filmToPass = &new_film;
	browser->insert_tail(filmToPass);
	system("clear");
	MM_Templates();
}
