#include "Controller.h"
#include <fstream>

Controller::Controller()
{
	browser = new Browser();
	Init();
}

Controller::~Controller()
{
    delete browser;
	for (auto it = crewVector->begin(); it != crewVector->end(); ++it)
	{
		delete (*it);
	}
	delete crewVector;
	for (auto it = matVector->begin(); it != matVector->end(); ++it)
	{
		delete (*it);
	}
	delete matVector;
}

void Controller::Init()
{
	fileHandler = FileHandler(browser, crewVector, matVector);
	LoadCrew();
	LoadMaterials();
    fileHandler.LoadFilmProjects();
	Main_Menu();
}

void Controller::LoadCrew()
{
	fileHandler.LoadEntireCrew();
}

void Controller::LoadMaterials()

{
	fileHandler.LoadAllMaterials();
}

void Controller::SaveAllFiles()
{
	fileHandler.UpdateProjectFile();
	fileHandler.WriteCrewToFile();
	fileHandler.WriteMaterialToFile();
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

	for (auto it = crewVector->begin(); it != crewVector->end(); ++it)
	{
		if ((*it)->ID > new_id)
		{
			new_id = (*it)->ID;
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
        if (mat->Type == "combobox")
		{
			std::vector<Material*> boxContents = mat->GetDVDs();
			for (auto iter = boxContents.begin(); iter != boxContents.end(); ++iter)
			{
				view.LoadMatData((*iter), "\t\t");
			}
		}
	}
	std::cout << "\n";
}

void Controller::Main_Menu()
{
	bool running = true;
	while(running)
	{
		view.Main_Menu_Templates();
		std::string input = inputHandler.Basic_User_Input("casestring");

		if (input == "bm")
		{
			view.BM_Templates();
			Browser_Menu();
		}
		if (input == "mm")
		{
			view.MM_Templates();
			Maintenance_Menu();
		}
		if (input == "exit")
		{
			running = false;
		}
	}
	SaveAllFiles();
}

void Controller::Browser_Menu()
{
	view.BM_Templates();
	view.DisplayCurrentFilmProject(browser->current->data);
	bool running = true;
	while(running)
	{
        std::string input = inputHandler.Basic_User_Input("casestring");
		view.BM_Templates();
		view.DisplayCurrentFilmProject(browser->current->data);
        running = BasicUserInput(input, "bm");
		
		if (input == "search")
		{
			searchEngine();	
		}
	}
}

bool Controller::BasicUserInput(std::string input, std::string currMenu)
{
	if (input == "next")
	{
		browser->nextNode();
		if (currMenu == "bm")
		{
			view.BM_Templates();
		}
		if (currMenu == "mm")
		{
			view.MM_Templates();
		}
		view.DisplayCurrentFilmProject(browser->current->data);
	}
	if (input == "back")
	{
		browser->previousNode();
		if (currMenu == "bm")
		{
			view.BM_Templates();
		}
		if (currMenu == "mm")
		{
			view.MM_Templates();
		}
		view.DisplayCurrentFilmProject(browser->current->data);
	}
	if (input == "rtm")
	{
		return false;
	}
	if (input == "crew")
	{
		view.DisplayCrew(browser->current->data->CrewMembers);
	}
	else if (input == "mi" && browser->current->data->Status == 2)
	{
		DisplayMaterials(browser->current->data->Materials);
    }
    return true;
}

void Controller::Maintenance_Menu()
{
	view.MM_Templates();
	view.DisplayCurrentFilmProject(browser->current->data);
	bool running = true;
	while(running)
	{
		std::string input = inputHandler.Basic_User_Input("casestring");
		running = BasicUserInput(input, "mm");
        if (input == "edit")
		{
			Edit_Menu();
            view.MM_Templates();
            view.DisplayCurrentFilmProject(browser->current->data);
		}
		if (input == "cnp")
		{
			Create_New_Project_Menu();
            view.MM_Templates();
            view.DisplayCurrentFilmProject(browser->current->data);
		}
		if (input == "dp")
		{
			std::cout << "\nProject Deleted" << std::endl;
			browser->delete_current();
            view.MM_Templates();
            view.DisplayCurrentFilmProject(browser->current->data);
		}
		if (input == "cnc")
		{
			CreateNewCrew();
            view.MM_Templates();
            view.DisplayCurrentFilmProject(browser->current->data);
		}
		if (input == "cnm")
		{
			//SaveAllFiles();
			matVector->push_back(CreateNewMaterial());
            view.MM_Templates();
            view.DisplayCurrentFilmProject(browser->current->data);
		}
		if (input == "reports")
		{
			Reports();
            view.MM_Templates();
            view.DisplayCurrentFilmProject(browser->current->data);
		}

	}
}

void Controller::Create_New_Project_Menu()
{
	view.CNP_Templates();

	FilmProject* new_film = new FilmProject();
	std::string user_input;
	bool running = true;

	new_film->ID = unique_id_check_project();

	view.ShowStatusMeaning();
	view.ShowInsertStatus();
	user_input = inputHandler.Basic_User_Input("number");
	new_film->Status = std::stoi(user_input);

	view.ShowInsertTitle();
	new_film->Title = inputHandler.Basic_User_Input("string");
	
	view.ShowInsertKeywords();
	view.Vector_Instructions();
	while (user_input != "Q")
	{
		user_input = inputHandler.Basic_User_Input("string");
		if (user_input != "Q") { new_film->KeyWords.push_back(user_input); }
	}
	user_input = "";

	view.ShowInsertSummary();
	new_film->Summary = inputHandler.Basic_User_Input("string");
	
	view.ShowInsertGenre();
	view.Vector_Instructions();
	while (user_input != "Q")
	{
		std::getline(std::cin, user_input);
		if (user_input != "Q") { new_film->Genre.push_back(user_input); }
	}
	user_input = "";
	
	view.ShowInsertReleaseDate();
	new_film->ReleaseDate = inputHandler.Basic_User_Input("string");
	
	view.ShowInsertFilmingLocations();
	view.Vector_Instructions();
	while (user_input != "Q")
	{
		user_input = inputHandler.Basic_User_Input("string");
		if (user_input != "Q") { new_film->Filming_Locations.push_back(user_input); }
	}

	view.ShowInsertRuntime();
	user_input = inputHandler.Basic_User_Input("number");
	new_film->Runtime = std::stoi(user_input);
	
	view.ShowInsertLanguages();
	view.Vector_Instructions();
	while (user_input != "Q")
	{
		user_input = inputHandler.Basic_User_Input("string");
		if (user_input != "Q") { new_film->Languages.push_back(user_input); }
	}
	
	if (new_film->Status == 1)
	{
		view.ShowInsertWeeklyTicketSale();
		user_input = inputHandler.Basic_User_Input("number");
		new_film->WeeklyTicketSales.push_back(std::stoi(user_input));
	}
	browser->insert_tail(new_film);

	view.DisplayCrew(*crewVector);
	
	system("clear");
	int crew_id_input;

	while (crew_id_input != 00)
	{
		Crew* new_crew = fileHandler.LoadCrew(stoi(inputHandler.Basic_User_Input("number")));
		if (crew_id_input != 00) { new_film->CrewMembers.push_back(new_crew); }
	}
	fileHandler.Tracking(1);
}

void Controller::CreateNewCrew()
{
	view.DisplayCreateNewCrew();

	Crew* new_crew = new Crew();

	new_crew->ID = unique_id_check_crew();

	view.ShowInsertCrewName();
	new_crew->Name = inputHandler.Basic_User_Input("string");

	view.ShowInsertCrewJob();
	new_crew->Job = inputHandler.Basic_User_Input("string");
	
	crewVector->push_back(new_crew);
}

void Controller::Edit_Menu()
{
	view.Edit_Templates();
	
	bool running = true;
	while(running)
	{
        std::string user_input = inputHandler.Basic_User_Input("casestring");
        if (user_input == "project")
		{
			project_edit();
			running = false;
		}
        else if (user_input == "crew")
		{
			crew_edit();
			running = false;
		}
        else if (user_input == "material" || user_input == "materials")
		{
			material_edit();
			running = false;
		}
		else if (user_input == "rtm")
		{
			running = false;
		}
	}
}

void Controller::project_edit()
{
	bool running = true;
	while(running)
	{
		view.Edit_Templates();
		view.Next_Back_Instructions();
		view.DisplayCurrentFilmProject(browser->current->data);
		view.ShowInsertDataType();

		std::string user_input =  inputHandler.Basic_User_Input("casestring");

		if (user_input == "status")
		{
			view.ShowStatusMeaning();
			view.ShowInsertStatus();
			browser->current->data->Status = std::stoi(inputHandler.Basic_User_Input("number"));
		}
		if (user_input == "title")
		{
			view.ShowInsertTitle();
			browser->current->data->Title = inputHandler.Basic_User_Input("string");
		}
		if (user_input == "keywords")
		{
			view.ShowVectorEdit(browser->current->data->KeyWords);
			size_t selectedItem = std::stoi(inputHandler.Basic_User_Input("number"));

			if (selectedItem == selectedItem == browser->current->data->KeyWords.size())
			{
				view.ShowInsertKeywords();
				browser->current->data->KeyWords.push_back(inputHandler.Basic_User_Input("string"));
			}
			if (selectedItem == 000)
			{
				view.ShowDeleteKeywords();
				browser->current->data->KeyWords.erase(browser->current->data->KeyWords.begin() + std::stoi(inputHandler.Basic_User_Input("number")));
			}
			else
			{
				view.ShowInsertKeywords();
				browser->current->data->KeyWords.at(selectedItem) = inputHandler.Basic_User_Input("string");
			}
		}
		if (user_input == "summary")
		{
			view.ShowInsertSummary();
			browser->current->data->Summary = inputHandler.Basic_User_Input("string");
		}
		if (user_input == "genres")
		{
			view.ShowVectorEdit(browser->current->data->Genre);
			size_t selectedItem = std::stoi(inputHandler.Basic_User_Input("number"));

			if (selectedItem == browser->current->data->Genre.size())
			{
				view.ShowInsertGenre();
				browser->current->data->Genre.push_back(inputHandler.Basic_User_Input("string"));
			}
			if (selectedItem == 000)
			{
				view.ShowDeleteGenre();
				browser->current->data->Genre.erase(browser->current->data->Genre.begin() + std::stoi(inputHandler.Basic_User_Input("number")));
			}
			else
			{
				view.ShowInsertGenre();
				browser->current->data->Genre.at(selectedItem) = inputHandler.Basic_User_Input("string");
			}
		}
		if (user_input == "release date")
		{
			view.ShowInsertReleaseDate();
			browser->current->data->ReleaseDate = inputHandler.Basic_User_Input("string");
		}
		if (user_input == "filming locations")
		{
			view.ShowVectorEdit(browser->current->data->Filming_Locations);
			size_t selectedItem = std::stoi(inputHandler.Basic_User_Input("number"));

			if (selectedItem == browser->current->data->Filming_Locations.size())
			{
				view.ShowInsertFilmingLocations();
				browser->current->data->Filming_Locations.push_back(inputHandler.Basic_User_Input("string"));
			}
			if (selectedItem == 000)
			{
				view.ShowDeleteFilmingLocations();
				browser->current->data->Filming_Locations.erase(browser->current->data->Filming_Locations.begin() + std::stoi(inputHandler.Basic_User_Input("number")));
			}
			else
			{
				view.ShowInsertFilmingLocations();
				browser->current->data->Filming_Locations.at(selectedItem) = inputHandler.Basic_User_Input("string");
			}
		}
		if (user_input == "runtime")
		{
			view.ShowInsertRuntime();
			browser->current->data->Runtime = std::stoi(inputHandler.Basic_User_Input("number"));
		}
		if (user_input == "languages")
		{
			view.ShowVectorEdit(browser->current->data->Languages);
			size_t selectedItem = std::stoi(inputHandler.Basic_User_Input("number"));

			if (selectedItem == browser->current->data->Languages.size())
			{
				view.ShowInsertLanguages();
				browser->current->data->Languages.push_back(inputHandler.Basic_User_Input("string"));
			}
			if (selectedItem == 000)
			{
				view.ShowDeleteLanguages();
				browser->current->data->Languages.erase(browser->current->data->Languages.begin() + std::stoi(inputHandler.Basic_User_Input("number")));
			}
			else
			{
				view.ShowInsertLanguages();
				browser->current->data->Languages.at(selectedItem) = inputHandler.Basic_User_Input("string");
			}
		}
		if (user_input == "weekly box office" && browser->current->data->Status == 1)
		{
			view.ShowInsertWeeklyTicketSale();
			browser->current->data->WeeklyTicketSales.push_back(std::stod(inputHandler.Basic_User_Input("number")));		
		}
		if (user_input == "crew")
		{
            view.ShowAddDeleteCrew();
			std::string user_input = inputHandler.Basic_User_Input("string");
			if (user_input == "delete")
			{
				view.DisplayCrew(browser->current->data->CrewMembers);
				view.ShowDeleteCrew();
				int currentCrew = std::stoi(inputHandler.Basic_User_Input("number"));
				
				for (auto it = browser->current->data->CrewMembers.begin(); it != browser->current->data->CrewMembers.end(); ++it)
				{
                    if ((*it)->ID == currentCrew)
					{
						browser->current->data->CrewMembers.erase(it);
					}
				}
			}
			if (user_input == "add")
			{
				view.DisplayCrew(*crewVector);
				view.ShowAddCrew();
				int currentCrew = std::stoi(inputHandler.Basic_User_Input("number"));

				for (auto it = crewVector->begin(); it != crewVector->end(); ++it)
				{
                    if ((*it)->ID == currentCrew)
					{
						browser->current->data->CrewMembers.push_back(*it);
					}
				}
			}

		}
		if (user_input == "material" && browser->current->data->Status == 2)
		{
			view.ShowAddDeleteMaterial();
			std::string user_input = inputHandler.Basic_User_Input("string");
			if (user_input == "delete")
			{
				view.DisplayCrew(browser->current->data->CrewMembers);
				view.ShowDeleteMaterial();
				int currentCrew = std::stoi(inputHandler.Basic_User_Input("number"));
				
				for (auto it = browser->current->data->Materials.begin(); it != browser->current->data->Materials.end(); ++it)
				{
                    if ((*it)->ID == currentCrew)
					{
						//delete *it;
						browser->current->data->Materials.erase(it);
					}
				}
			}
			if (user_input == "add")
			{
				DisplayMaterials(*matVector);
				view.ShowAddMaterial();
				int currentMaterial = std::stoi(inputHandler.Basic_User_Input("number"));

				for (auto it = matVector->begin(); it != matVector->end(); ++it)
				{
                    if ((*it)->ID == currentMaterial)
					{
						browser->current->data->Materials.push_back(*it);
					}
				}
			}
		}
		if (user_input == "next") { browser->nextNode(); }
		if (user_input == "back") { browser->previousNode(); }
		if (user_input == "rtm") { running = false; }
	} 
}

Material* Controller::CreateNewMaterial()
{
	Material* new_mat = new Material();
	new_mat->ID = unique_id_check_material();

	bool isCorrectType = false;
	do
	{
		view.DisplayCreateNewMaterial();
		std::string user_input = inputHandler.Basic_User_Input("string");

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
		
	} while (isCorrectType == false);

	view.ShowInsertTitle();
	new_mat->Title = inputHandler.Basic_User_Input("string");

	view.ShowInsertDescription();
	new_mat->Description = inputHandler.Basic_User_Input("string");

	view.ShowInsertVideoFormat();
	new_mat->VideoFormat = inputHandler.Basic_User_Input("string");

	view.ShowInsertAudioFormat();
	new_mat->AudioFormat = inputHandler.Basic_User_Input("string");
	
	view.ShowInsertRuntime();
	new_mat->Runtime = std::stoi(inputHandler.Basic_User_Input("number"));
	
	if (new_mat->Type == "vhs")
	{
		view.ShowInsertLanguages();
		std::vector<std::string> language;
		language.push_back(inputHandler.Basic_User_Input("string"));
		new_mat->SetLanguages(language);
	}
	else
	{
		std::vector<std::string> languages;
		view.ShowInsertLanguages();
		std::string user_input;
		while (user_input != "Q")
		{
			user_input = inputHandler.Basic_User_Input("string");
			if (user_input != "Q") { languages.push_back(user_input); }
		}
		new_mat->SetLanguages(languages);
	}
	
	view.ShowInsertRetailPrice();
	new_mat->RetailPrice = std::stoi(inputHandler.Basic_User_Input("number"));

	if (new_mat->Type == "vhs")
	{
		view.ShowInsertSubtitles();
		std::vector<std::string> subtitle;
		subtitle.push_back(inputHandler.Basic_User_Input("string"));
		new_mat->SetLanguages(subtitle);
	}
	else
	{
		std::vector<std::string> subtitles;
		view.ShowInsertSubtitles();
		view.Vector_Instructions();
		std::string user_input;
		while (user_input != "Q")
		{
			user_input = inputHandler.Basic_User_Input("string");
			if (user_input != "Q") { subtitles.push_back(user_input); }
		}
		new_mat->SetLanguages(subtitles);
	}

	std::cout << "\nPlease insert the Frame Aspect\n"<< std::endl;
	new_mat->FrameAspect = inputHandler.Basic_User_Input("string");

	if (new_mat->Type == "combobox")
	{
		for (auto i = 0; i != std::stoi(inputHandler.Basic_User_Input("number")); ++i)
		{
			new_mat->SetDVDVector(CreateNewMaterial());
		}
	}
	else
	{
		browser->setHead();
		bool running = true;
		while(running)
		{
			system("clear");
			view.Next_Back_Instructions();
			view.DisplayCurrentFilmProject(browser->current->data);

			std::string user_input = inputHandler.Basic_User_Input("casestring");

			if (user_input == "next" || user_input == "back")
			{
				BasicUserInput(user_input, "");
			}
			else if (user_input == "id")
			{
				view.ShowInsertFilmIDs(); 
				Film new_film;
				new_film.ID = std::stoi(inputHandler.Basic_User_Input("number"));
				new_film = fileHandler.LoadFilm(new_film.ID);
				if (new_film.Title == "") { running = true; }
				else
				{	
					new_mat->SetFilm(new_film);
					running = false;
				}
			}
		}	 
	}

	fileHandler.Tracking(2);

	return new_mat;
}

void Controller::crew_edit()
{
	bool running = true;
	while (running)
	{
		view.Edit_Templates();
		view.DisplayCrew(*crewVector);
		view.ShowEditDeleteCrew();

		std::string user_input = inputHandler.Basic_User_Input("casestring");

		if (user_input == "edit")
		{
			view.ShowRequestCrewID();
			int currentCrew = std::stoi(inputHandler.Basic_User_Input("number"));

			for (auto it = crewVector->begin(); it != crewVector->end(); ++it)
			{
				if ((*it)->ID == currentCrew)
				{
					view.ShowInsertCrewName();
					(*it)->Name = inputHandler.Basic_User_Input("string");

					view.ShowInsertCrewJob();
					(*it)->Job = inputHandler.Basic_User_Input("string");
				}
			}
		}
		if (user_input == "delete")
		{
			view.ShowDeleteCrew();
			int currentCrew = std::stoi(inputHandler.Basic_User_Input("number"));
		}
		if (user_input == "rtm") { running = false; }
	}
}

void Controller::material_edit()
{
	bool running = true;
	while (running)
	{
		DisplayMaterials(*matVector);
		std::string input;
		view.ShowRequestMaterialID();
		int currentMaterial = std::stoi(inputHandler.Basic_User_Input("number"));

		if (currentMaterial == 000) { running = false; }

		for (auto it = matVector->begin(); it != matVector->end(); ++it)
		{
			if ((*it)->ID == currentMaterial)
			{
				view.ShowInsertDataType();
				input = inputHandler.Basic_User_Input("casestring");
				
				if (input == "title")
				{
					view.ShowInsertTitle();
					(*it)->Title = inputHandler.Basic_User_Input("string");
				}
				if (input == "description")
				{
					view.ShowInsertDescription();
					(*it)->Description = inputHandler.Basic_User_Input("string");
				}
				if (input == "video format")
				{
					view.ShowInsertVideoFormat();
					(*it)->VideoFormat = inputHandler.Basic_User_Input("string");
				}
				if (input == "audio format")
				{
					view.ShowInsertAudioFormat();
					(*it)->AudioFormat = inputHandler.Basic_User_Input("string");
				}
				if (input == "runtime")
				{
					view.ShowInsertRuntime();
					(*it)->Runtime = std::stoi(inputHandler.Basic_User_Input("number"));
				}
				if (input == "language" || input == "languages")
				{
					if ((*it)->Type == "VHS")
					{
						view.ShowInsertLanguages();
						std::vector<std::string> language;
						language.push_back(inputHandler.Basic_User_Input("string"));
						(*it)->SetLanguages(language);
					}
					else
					{
						std::vector<std::string> languages;
						for (auto i = 0; i != (*it)->GetNumLanguages(); ++i)
						{
							languages.push_back((*it)->GetLanguage(i));
						}
						view.ShowVectorEdit(languages);
						size_t selectedItem = std::stoi(inputHandler.Basic_User_Input("number"));

						if (selectedItem == languages.size())
						{
							view.ShowInsertLanguages();
							languages.push_back(inputHandler.Basic_User_Input("string"));
						}
						if (selectedItem == 000)
						{
							view.ShowDeleteLanguages();
							languages.erase(languages.begin() + std::stoi(inputHandler.Basic_User_Input("number")));
						}
						else
						{
							view.ShowInsertLanguages();
							languages.at(selectedItem) = inputHandler.Basic_User_Input("string");
						}
					}
				}
				if (input == "retail price")
				{
					view.ShowInsertRetailPrice();
					(*it)->RetailPrice = std::stoi(inputHandler.Basic_User_Input("number"));
				}
				if (input == "subtitle" || input == "subtitles")
				{
					if ((*it)->Type == "vhs")
					{
						view.ShowInsertLanguages();
						std::vector<std::string> subtitle;
						subtitle.push_back(inputHandler.Basic_User_Input("string"));
						(*it)->SetLanguages(subtitle);
					}
					else
					{
						std::vector<std::string> subtitles;
						for (auto i = 0; i != (*it)->GetNumLanguages(); ++i)
						{
							subtitles.push_back((*it)->GetLanguage(i));
						}
						view.ShowVectorEdit(subtitles);
						size_t selectedItem = std::stoi(inputHandler.Basic_User_Input("number"));

						if (selectedItem == subtitles.size())
						{
							view.ShowInsertSubtitles();
							subtitles.push_back(inputHandler.Basic_User_Input("string"));
						}
						if (selectedItem == 000)
						{
							view.ShowDeleteSubtitles();
							subtitles.erase(subtitles.begin() + std::stoi(inputHandler.Basic_User_Input("number")));
						}
						else
						{
							view.ShowInsertSubtitles();
							subtitles.at(selectedItem) = inputHandler.Basic_User_Input("string");
						}
					}
				}
				if (input == "frame aspect")
				{
					view.ShowInsertFrameAspect();
					(*it)->FrameAspect = inputHandler.Basic_User_Input("string");
				}
				if ((*it)->Type == "vhs")
				{
					if (input == "packaging")
                    {			view.DisplayEarningsReport();

						view.ShowInsertPackaging();
						(*it)->Packaging = inputHandler.Basic_User_Input("packaging");
					}
				}
				// maybe stored
				view.DisplayMaterial();
				DisplayMaterials(*matVector);				
			}
		}
	}	
}

void Controller::searchEngine()
{
	std::string search = "";
	bool run = true;

	while (run == true)
	{
        view.ShowSearchRequest();
		std::string search = inputHandler.Basic_User_Input("casestring");

		if (search == "actor") {
			view.ShowEnterActorName();
			std::string search = inputHandler.Basic_User_Input("string");
            view.DisplayFilmTitles(SearchActor(search), search);
			run = false;
		}
		else if (search == "title")
		{
			view.ShowEnterProjectTitle();
			std::string search = inputHandler.Basic_User_Input("string");
            SearchProjectTitle(search);
			run = false;
		}
	}
}

Node* Controller::SearchProjectTitle(std::string search)
{
	browser->setHead();
    while (browser->current->next != nullptr)
	{
        if (browser->current->data->Title == search)
        {
            return browser->current;
        }
		browser->nextNode();
	}
    if (browser->current->data->Title == search)
    {
        return browser->current;
    }
    return nullptr;
}

std::vector<std::string> Controller::SearchActor(std::string search)
{
	browser->setHead();
    std::vector<std::string> FilmTitles;

    auto CheckIfFilmContainsActor = [&FilmTitles, search](Browser* browser)
    {
        std::vector<std::string> CurrentFilmCrewNames;
        for (auto it = browser->current->data->CrewMembers.begin(); it != browser->current->data->CrewMembers.end(); ++it)
        {
            CurrentFilmCrewNames.push_back((*it)->Name);
        }
        if(std::find(CurrentFilmCrewNames.begin(), CurrentFilmCrewNames.end(), search) != CurrentFilmCrewNames.end())
        {
            FilmTitles.push_back(browser->current->data->Title);
        }
        browser->nextNode();
    };
	while (browser->current->next != nullptr)
	{
        CheckIfFilmContainsActor(browser);
	}
    CheckIfFilmContainsActor(browser);
    return FilmTitles;
}

void Controller::Reports()
{
	bool running = true;
	while (running)
	{
		system("clear");
		view.ReportsOptions();
		std::string user_option = inputHandler.Basic_User_Input("casestring");
		if (user_option == "data report")
		{
			view.New_data_report();			
			inputHandler.Basic_User_Input("");
		}
        if (user_option == "earnings report")
		{		
			view.DisplayEarningsReport();	
            int thresholdValue = std::stoi(inputHandler.Basic_User_Input("number"));

			while (browser->current->next != nullptr)
			{
				double totalEarnings = std::accumulate(browser->current->data->WeeklyTicketSales.begin(), browser->current->data->WeeklyTicketSales.end(), 0);
                if (totalEarnings > thresholdValue)
				{
					view.Total_Earnings_report(browser->current->data);
				}
                browser->nextNode();
			}
            double totalEarnings = std::accumulate(browser->current->data->WeeklyTicketSales.begin(), browser->current->data->WeeklyTicketSales.end(), 0);
            if (totalEarnings > thresholdValue)
            {
                view.Total_Earnings_report(browser->current->data);
            }
		}
		if (user_option == "rtm")
		{
			running = false;
		}
	}
}
