#include "Controller.h"

Controller::Controller()
{
	browser = new Browser();
    fileHandler = FileHandler(browser);
    fileHandler.LoadFilmProjects();
	LoadCrew();
	LoadMaterials();
}

Controller::~Controller()
{
}

void Controller::LoadCrew()
{
	crewVector = fileHandler.LoadEntireCrew();
}

void Controller::LoadMaterials()

{
	matVector = fileHandler.LoadAllMaterials();
}

void Controller::SaveAllFiles()
{
	fileHandler.UpdateProjectFile();
	fileHandler.WriteCrewToFile(crewVector);
	browser->setHead();
}

int Controller::unique_id_check_project()
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

int Controller::unique_id_check_material()
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

int Controller::unique_id_check_crew()
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

void Controller::DisplayMaterials(std::vector<Material*> matVec)
{
	view.DisplayMaterial();

	for (std::vector<Material *>::iterator it = matVec.begin(); it != matVec.end(); ++it)
	{
		view.LoadMatData(*it, "");
		Material *mat = *it;
		if (mat->Type == "ComboBox")
		{
			for (auto iter = mat->GetDVDs().begin(); iter != mat->GetDVDs().end(); ++iter)
			{
				view.LoadMatData((*iter), "\t\t");
			}
		}
	}

	std::cout << "\n";
}

void Controller::Main_Menu()
{
	std::string user_input = "";

	do
	{
		system("clear");
		view.Main_Menu_Templates();

		std::getline(std::cin, user_input);
		std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);

		if (user_input == "save")
		{
			system("clear");
			view.Main_Menu_Templates();
			SaveAllFiles();
			std::cout << " Projects Saved   " << std::endl;
		}
		if (user_input == "bm")
		{
			system("clear");
			view.BM_Templates();
			Browser_Menu();
		}
		if (user_input == "mm")
		{
			system("clear");
			view.MM_Templates();
			Maintenance_Menu();
		}

	} while (user_input != "exit");
	SaveAllFiles();

}

void Controller::Browser_Menu()
{
	std::string user_input = "";

	do
	{
		std::getline(std::cin, user_input);

		std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);

		inputHandler.Basic_User_Input(user_input);

		system("clear");
		view.BM_Templates();

		if (user_input == "crew")
		{
			view.DisplayCrew();
		}
		else if (user_input == "mi")
		{
			DisplayMaterials();
		}

	} while (user_input != "rtm");
}

void Controller::Maintenance_Menu()
{

	do
	{
		

		inputHandler.Basic_User_Input();

		view.MM_Templates();

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
		if (user_input == "cnm")
		{
			SaveAllFiles();
			matVector.push_back(CreateNewMaterial());
			system("clear");
			MM_Templates();
		}

	} while (user_input != "rtm");
	user_input = "";
}

void Controller::Edit_Menu()
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

void Controller::project_edit()
{
	std::string edit_input = "";

	do
	{
		system("clear");
		Edit_Templates();

		Next_Back_Instructions();

		DisplayCurrentFilmProject();

		std::cout << "Please enter in the datatype you want to edit\n"
				  << std::endl;

		std::getline(std::cin, edit_input);

		std::transform(edit_input.begin(), edit_input.end(), edit_input.begin(), ::tolower);

		if (edit_input == "next" || edit_input == "back" || edit_input == "rtm")
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

			if (edit_input == "crew member id")
			{
				
				DisplayCrew();
				
				
				
				std::cout << "\nPlease insert a crew member ID: ";
				
				
				
				// display crew members
				// request ID
				// Link ID and data
			}

			if (edit_input == "material id" && browser->current->data->Status == 2)
			{
				std::cout << "\nPlease insert a material ID : ";
				DisplayMaterials();
				std::string strMaterialID;
				std::getline(std::cin, strMaterialID);
				//Material* new_mat
				std::stoi(strMaterialID);

				//browser->current->data->Materials.push_back();

			}
		}

	} while (edit_input != "rtm");
}


void Controller::crew_edit()
{
	std::string edit_input = "";

	do
	{

		system("clear");
		Edit_Templates();
		
		Next_Back_Instructions();
		
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

void Controller::material_edit()
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
		std::getline(std::cin, edit_input);

		std::pair<bool, bool> string_int_vals = string_int_check(edit_input);

		if(string_int_vals.second == true && string_int_vals.first == false)
		{
			int material_ID = std::stoi(edit_input);
			material_edit_management(material_ID);
		}
		else if(string_int_vals.second == false  && string_int_vals.first == true)
		{
			std::transform(edit_input.begin(), edit_input.end(), edit_input.begin(), ::tolower);
			if( edit_input == "next" ||  edit_input == "back" ||  edit_input == "rtm" )
			{
				Basic_User_Input(edit_input);
			}
		}

	}while(edit_input != "rtm");
}

void Controller::material_edit_management(int material_ID)
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

void Controller::CreateNewCrew()
{
	std::cout << "________________________________________________\n\n" << std::endl;
	std::cout << "           Create New Crew Member                 " << "\n" << std::endl;

	Crew new_crew;
	new_crew.ID = unique_id_check_crew();

	std::string user_input;
	std::cout << "\nPlease insert the Crew Members Name: ";
	user_input = inputHandler.Basic_User_Input("string");
	if (user_input == "")
	{

	}
	std::cout << "\nPlease insert the Crew Members Job: ";
	std::getline(std::cin, new_crew.Job);
	crewVector.push_back(new_crew);

	system("clear");
	MM_Templates();
}

Material* Controller::CreateNewMaterial()
{
	Material* new_mat = new Material();

	new_mat->ID = unique_id_check_material();

	std::string user_input;
	
	bool isCorrectType = false;
	do
	{
		system("clear");
		std::cout << "________________________________________________\n\n" << std::endl;
		std::cout << "              Create New Material                 " << "\n" << std::endl;
		std::cout << "\nPlease insert the type of Material:";
		std::cout << "\nTypes are: VHS, DVD(SingleSided), BluRay, ComboBox, DoubleSidedDVD\n";
		std::getline(std::cin, user_input);
		std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);
		
		if(user_input == "vhs")
		{
			new_mat->Type = "vhs";
			isCorrectType = true;
			new_mat = new VHS();
		}
		else if(user_input == "dvd")
		{
			new_mat->Type = "dvd";
			isCorrectType = true;
			new_mat = new DVD();
		}
		else if(user_input == "bluray")
		{
			new_mat->Type = "bluray";
			isCorrectType = true;
			new_mat = new BluRay();
		}
		else if(user_input == "combobox")
		{
			new_mat->Type = "combobox";
			isCorrectType = true;
			new_mat = new ComboBox();
		}
		else if(user_input == "doublesideddvd")
		{
			new_mat->Type = "doublesideddvd";
			isCorrectType = true;
			new_mat = new DoubleSidedDVD();
		}
		else
		{
			std::cout << "\n Please enter a valid material type \n";
		}
		
	} while (isCorrectType == false);

		// Type,ComboBox
		// Title,Avatar - The complete collection.
		// DVD_Description,The complete Avatar film collection.
		// Video_Format,1080p
		// Audio_Format,WAV
		// Run_Time,438
		// Languages,English,French,Spanish
		// Retail_Price,25
		// Subtitles,English,French,Spanish
		// Frame_Aspect,16:9
		// Packaging,Cardboard
		// Stored,2,5

	std::cout << "\nPlease insert the Title:\n"<< std::endl;
	std::getline(std::cin, new_mat->Title);
	
	std::cout << "\nPlease insert the Description:\n"<< std::endl;
	std::getline(std::cin, new_mat->Description);

	std::cout << "\nPlease insert the Video Format:\n"<< std::endl; 
	std::getline(std::cin, new_mat->Description);

	std::cout << "\nPlease insert the Audio Format:\n"<< std::endl; 
	std::getline(std::cin, new_mat->Description);
	
	bool isNum = false;
	while (isNum == false)
	{
		std::cout << "\nPlease insert the Runtime:\n";
		std::getline(std::cin, user_input);
		try
		{
			new_mat->Runtime = std::stoi(user_input);
			isNum = true;
		}
		catch(const std::exception& e)
		{
			std::cout << "Please enter a number" << '\n';
			isNum = false;
		}
	}
	if (new_mat->Type == "vhs")
	{
		std::cout << "\nPlease insert the Language:\n"<< std::endl;
		std::getline(std::cin, user_input);
		std::vector<std::string> language;
		language.push_back(user_input);
		new_mat->SetLanguages(language);
	}
	else
	{
		std::vector<std::string> languages;
		std::cout << "\nPlease insert the Languages:\n"<< std::endl;
		Vector_Instructions();
		do
		{
			std::getline(std::cin, user_input);
			languages.push_back(user_input);
		} while (user_input != "Q");
		new_mat->SetLanguages(languages);
	}
	
	isNum = false;
	while (isNum == false)
	{
		std::cout << "\nPlease insert the Retail Price:\n";
		std::getline(std::cin, user_input);
		try
		{
			new_mat->RetailPrice = std::stod(user_input);
			isNum = true;
		}
		catch(const std::exception& e)
		{
			std::cout << "Please enter a number" << '\n';
			isNum = false;
		}
	}

	if (new_mat->Type == "vhs")
	{
		std::cout << "\nPlease insert the Subtitle Language:\n"<< std::endl;
		std::getline(std::cin, user_input);
		std::vector<std::string> subtitle;
		subtitle.push_back(user_input);
		new_mat->SetLanguages(subtitle);
	}
	else
	{
		std::vector<std::string> subtitles;
		std::cout << "\nPlease insert the Subtitle Languages:\n"<< std::endl;
		Vector_Instructions();
		do
		{
			std::getline(std::cin, user_input);
			subtitles.push_back(user_input);
		} while (user_input != "Q");
		new_mat->SetLanguages(subtitles);
	}

	std::cout << "\nPlease insert the Frame Aspect\n"<< std::endl;
	std::getline(std::cin, new_mat->FrameAspect);

	if (new_mat->Type == "combobox")
	{
		int numOfStoredMats = 0;
		isNum = false;
		while (isNum == false)
		{
			std::cout << "\nEnter the number of materials stored in the combo box\n"<< std::endl;
			std::getline(std::cin, user_input);
			try
			{
				numOfStoredMats = std::stoi(user_input);
				isNum = true;
			}
			catch(const std::exception& e)
			{
				std::cout << "Please enter a number" << '\n';
				isNum = false;
			}
		}

		for (auto i = 0; i != numOfStoredMats; ++i)
		{
			new_mat->SetDVDVector(CreateNewMaterial());
		}
	}
	else
	{
        browser->setHead();
		isNum = false;
		int film_ID = 0;
		while (isNum == false)
		{
			Next_Back_Instructions();

			DisplayCurrentFilmProject();
			user_input = "";
			std::cout << "\nEnter the ID's of the films to store on this material\n"<< std::endl;
			std::getline(std::cin, user_input);

			std::pair<bool, bool> string_int_vals = string_int_check(user_input);

			if(string_int_vals.first == false && string_int_vals.second == true)
			{
				film_ID = std::stoi(user_input);
                Film new_film;
                new_film.ID = film_ID;
                new_film = fileHandler.LoadFilm(new_film.ID);
				if (new_film.Title == "")
				{
					isNum = false;
				}
				else
				{	
                	new_mat->SetFilm(new_film);
                	isNum = true;
				}
			}
			else if(string_int_vals.first == true  && string_int_vals.second == false)
			{
				std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);

				if( user_input == "next" ||  user_input == "back")
				{
					Basic_User_Input(user_input);
				}
			}
		}
	}
	return new_mat;
}

void Controller::Create_New_Project_Menu()
{
	system("clear");
	CNP_Templates();

	//std::string values[12] = {"Status", "Title", "Keywords", "Summary", "Genre", "Release Date", "Filming Locations", "Runtime", "Language", "Weekly Ticket Sales", "Crew Members"};

	FilmProject new_film;

	new_film.ID = unique_id_check_project();

	std::string user_input;
	bool isNum;
	std::cout << "\nUnreleased 1, Now_Playing 2, Released 3\n";
	isNum = false;
	while (isNum == false)
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
				isNum = true;
			}
		}
		catch(const std::exception& e)
		{
			std::cout << "Please enter a correct number" << '\n';
			isNum = false;
		}
	}
	std::cout << "\nPlease insert a Title: ";
	std::getline(std::cin, new_film.Title);
	std::cout << "\nPlease insert the Keywords: " << std::endl;
	Vector_Instructions();
	do
	{
		std::getline(std::cin, user_input);
		new_film.KeyWords.push_back(user_input);
	} while (user_input != "Q");
	std::cout << "\nPlease insert a Summary: ";
	std::getline(std::cin, new_film.Summary);
	std::cout << "\nPlease insert the Genres: " << std::endl;
	Vector_Instructions();
	do
	{
		std::getline(std::cin, user_input);
		new_film.Genre.push_back(user_input);
	} while (user_input != "Q");
	std::cout << "\nPlease insert a Release Date: ";
	std::getline(std::cin, new_film.ReleaseDate);
	std::cout << "\nPlease insert the Filming Locations: " << std::endl;
	Vector_Instructions();
	do
	{
		std::getline(std::cin, user_input);
		new_film.Filming_Locations.push_back(user_input);
	} while (user_input != "Q");
	isNum = false;
	while (isNum == false)
	{
		std::cout << "\nPlease insert the Runtime: ";
		std::getline(std::cin, user_input);
		try
		{
			new_film.Runtime = std::stoi(user_input);
			isNum = true;
		}
		catch(const std::exception& e)
		{
			std::cout << "Please enter a number" << '\n';
			isNum = false;
		}
	}	
	std::cout << "\nPlease insert the Languages: " << std::endl;
	Vector_Instructions();
	do
	{
		std::getline(std::cin, user_input);
		new_film.Languages.push_back(user_input);
	} while (user_input != "Q");
	if (new_film.Status == 1)
	{
		isNum = false;
		while (isNum == false)
		{
			std::cout << "\nPlease insert the Weekly Ticket Sale: ";
			std::getline(std::cin, user_input);
			try
			{
				new_film.WeeklyTicketSales.push_back(std::stod(user_input));
				isNum = true;
			}
			catch(const std::exception& e)
			{
				std::cout << "Please enter a number" << '\n';
				isNum = false;
			}
		}
	}

	DisplayAllCrew();

	std::cout << "\nPlease insert Crew Memeber IDs" << std::endl;
	Vector_Instructions();
	std::string tempStr;
	do
	{
		Crew new_crew;
		std::getline(std::cin, tempStr);
		if (tempStr != "Q")
		{
			new_crew.ID = std::stoi(tempStr);
			new_crew = fileHandler.LoadCrew(new_crew);
			new_film.CrewMembers.push_back(new_crew);
		}
	} while (tempStr != "Q");
	// if (new_film.Status == 2)
	// {	
	// 	std::cout << "\nPlease insert the Material IDs" << std::endl;
	// 	std::cout << "Type in the value then press enter to add another value" << std::endl;
	// 	std::cout << "When you have finihed enter in - Q" << std::endl;
	// 	tempStr = "";
	// 	do
	// 	{
	// 		Material* new_mat = new Material();
	// 		//std::getline(std::cin, )>> tempStr;
	// 		if (tempStr != "Q")
	// 		{
	// 			new_mat = fileHandler.GetMaterialType(new_mat, std::stoi(tempStr));
	// 			new_mat = fileHandler.LoadMaterial(new_mat, new_mat->ID);
	// 			new_film.Materials.push_back(new_mat);
	// 		}
	// 	} while (tempStr != "Q");
	// }
	
	FilmProject *filmToPass = &new_film;
	browser->insert_tail(filmToPass);
	system("clear");
	MM_Templates();
}