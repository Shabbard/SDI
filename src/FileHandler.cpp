#include "FileHandler.h"

FileHandler::FileHandler(Browser *input)
{
	browser = input;
}

void FileHandler::LoadFilmProjects()
{
	std::ifstream infile;
    infile.open(FilmDataRead);
	FilmProject* film = new FilmProject();
	std::string str;

	while (std::getline(infile, str))
	{
		std::vector<std::string> LineData = SeparateCommasIntoData(str);

		if (LineData.at(0) == "ID")
		{
			film->ID = std::stoi(LineData.at(1));
		}
		else if (LineData.at(0) == "Status")
		{
			film->Status = std::stoi(LineData.at(1));
		}
		else if (LineData.at(0) == "Title")
		{
			film->Title = LineData.at(1);
		}
		else if (LineData.at(0) == "Summary")
		{
			film->Summary = LineData.at(1);
		}
		else if (LineData.at(0) == "Genre")
		{
			LineData.erase(LineData.begin());
			film->Genre = LineData;
		}
		else if (LineData.at(0) == "Release_Date")
		{
			film->ReleaseDate = LineData.at(1);
		}
		else if (LineData.at(0) == "Filming_Loc")
		{
			LineData.erase(LineData.begin());
			film->Filming_Locations = LineData;
		}
		else if (LineData.at(0) == "Language")
		{
			LineData.erase(LineData.begin());
			film->Languages = LineData;
		}
		else if (LineData.at(0) == "Runtime")
		{
			film->Runtime = std::stoi(LineData.at(1));
		}
		else if (LineData.at(0) == "Keywords")
		{
			LineData.erase(LineData.begin());
			film->KeyWords = LineData;
		}
		else if (LineData.at(0) == "Weekly Ticket Sales")
		{
			LineData.erase(LineData.begin());
			for (auto it = LineData.begin(); it != LineData.end(); ++it)
			{
				film->WeeklyTicketSales.push_back(std::stoi(*it));
			}
		}
		else if (LineData.at(0) == "Crew_Members")
		{
			LineData.erase(LineData.begin());

            for (auto it = LineData.begin(); it != LineData.end(); ++it)
			{
				Crew new_crew;
				new_crew.ID = std::stoi(*it);
				new_crew = LoadCrew(new_crew);
				if (new_crew.ID != 0)
				{
					film->CrewMembers.push_back(new_crew);
				}
			}
			std::sort(film->CrewMembers.begin(), film->CrewMembers.end());	
		}
		else if (LineData.at(0) == "Material_ID")
		{
			LineData.erase(LineData.begin());
			auto mat = new Material();

			for (auto it = LineData.begin(); it != LineData.end(); ++it)
			{
                mat = GetMaterialType(mat, std::stoi(*it));
				LoadMaterial(mat, std::stoi(*it));
				film->Materials.push_back(mat);
				mat = nullptr;
			}
			browser->insert_tail(film);
            film = nullptr;
			film = new FilmProject();
		}
		LineData.clear();
	}

    insertionSort(&browser->current);

	delete film;
	film = nullptr;
}

std::vector<Crew> FileHandler::LoadEntireCrew()
{
	std::ifstream infile;
	infile.open(CrewData);
	std::string str;
	std::vector<Crew> crewVec;

	while (std::getline(infile, str))
	{
		std::vector<std::string> LineData = SeparateCommasIntoData(str);
		Crew new_crew;
		new_crew.ID = std::stoi(LineData.at(0));
		new_crew.Name = LineData.at(1);
		new_crew.Job = LineData.at(2);
		crewVec.push_back(new_crew);
	}
	std::sort(crewVec.begin(), crewVec.end());
	return crewVec;
}

Crew FileHandler::LoadCrew(Crew CrewMember)
{
	std::ifstream infile;
    infile.open(CrewData);
	std::string str;

	while (std::getline(infile, str))
	{
		std::vector<std::string> LineData = SeparateCommasIntoData(str);
		if (std::stoi(LineData.at(0)) == CrewMember.ID)
		{
			CrewMember.Name = LineData.at(1);
			CrewMember.Job = LineData.at(2);
            return CrewMember;
		}
		else if (std::stoi(LineData.at(0)) > CrewMember.ID)
		{
            CrewMember.ID = 0;
			return CrewMember;
		}
		LineData.clear();
	}
	return CrewMember;
}

template <typename T>
T FileHandler::GetMaterialType(T mat, int idToFind)
{
	std::ifstream MatFile;
	MatFile.open("../data/Material_Data.txt");
	std::string readline;
	int currentID = 0;

	while (std::getline(MatFile, readline))
	{
		std::regex type("(Type)");
		std::regex ID("(ID)");
		std::smatch data_match;
		if (std::regex_search(readline, data_match, type) && idToFind == currentID)
		{
			std::vector<std::string> matTypeVec = SeparateCommasIntoData(readline);

			if (matTypeVec.at(1) == "ComboBox")
			{
				delete mat;
				mat = new ComboBox();
			}
			else if (matTypeVec.at(1) == "VHS")
			{
				delete mat;
				mat = new VHS();
			}
			else if (matTypeVec.at(1) == "DVD")
			{
				delete mat;
				mat = new DVD();
			}
			else if (matTypeVec.at(1) == "DoubleSidedDVD")
			{
				delete mat;
				mat = new DoubleSidedDVD();
			}
			else if (matTypeVec.at(1) == "BluRay")
			{
				delete mat;
				mat = new BluRay();
			}
			mat->ID = idToFind;
			return mat;
		}
		else if (std::regex_search(readline, data_match, ID))
		{
			std::vector<std::string> LineData = SeparateCommasIntoData(readline);
			currentID = std::stoi(LineData.at(1));
		}
	}
	return mat;
}

template <typename T>
T FileHandler::LoadMaterial(T mat, int idToLoad)
{
	std::ifstream MaterialFile;
	MaterialFile.open(MaterialData);
	std::string str;
	int currentID = 0;

	while (std::getline(MaterialFile, str))
	{
		std::vector<std::string> LineData = SeparateCommasIntoData(str);

		if ((LineData.at(0) == "ID" && std::stoi(LineData.at(1)) == idToLoad) || currentID == idToLoad)
		{
			if (LineData.at(0) == "ID" && std::stoi(LineData.at(1)) == idToLoad)
			{
				currentID = std::stoi(LineData.at(1));
			}
			if (LineData.at(0) == "Title")
			{
				mat->Title = LineData.at(1);
			}
			else if (LineData.at(0) == "DVD_Description")
			{
				mat->Description = LineData.at(1);
			}
			else if (LineData.at(0) == "Video_Format")
			{
				mat->VideoFormat = LineData.at(1);
			}
			else if (LineData.at(0) == "Audio_Format")
			{
				mat->AudioFormat = LineData.at(1);
			}
			else if (LineData.at(0) == "Run_Time")
			{
				mat->Runtime = std::stoi(LineData.at(1));
			}
			else if (LineData.at(0) == "Languages")
			{
				LineData.erase(LineData.begin());
                mat->SetLanguages(LineData);
			}
			else if (LineData.at(0) == "Retail_Price")
			{
				mat->RetailPrice = std::stoi(LineData.at(1));
			}
			else if (LineData.at(0) == "Subtitles")
			{
				LineData.erase(LineData.begin());
				mat->SetSubtitles(LineData);
			}
			else if (LineData.at(0) == "Frame_Aspect")
			{
				mat->FrameAspect = LineData.at(1);
			}
			else if (LineData.at(0) == "Bonus_Features")
			{
				LineData.erase(LineData.begin());
				mat->SetBonusFeatures(LineData);
			}
			else if (LineData.at(0) == "Packaging")
			{
				mat->Packaging = LineData.at(1);
			}
			else if (LineData.at(0) == "Stored")
			{
				LineData.erase(LineData.begin());
				if (mat->Type == "ComboBox")
				{
					for (auto it = LineData.begin(); it != LineData.end(); ++it)
					{
						auto new_mat = new Material();
						new_mat = GetMaterialType(new_mat, std::stoi(*it));
						LoadMaterial(new_mat, std::stoi(*it));
						mat->SetDVDVector(new_mat);
						new_mat = nullptr;
					}
				}
				else if (mat->Type == "DoubleSidedDVD")
				{
					auto new_mat1 = new Material();
					auto new_mat2 = new Material();
                    new_mat1 = GetMaterialType(new_mat1, std::stoi(LineData.at(0)));
                    LoadMaterial(new_mat1, std::stoi(LineData.at(0)));
                    new_mat2 = GetMaterialType(new_mat2, std::stoi(LineData.at(1)));
                    LoadMaterial(new_mat2, std::stoi(LineData.at(1)));
					mat->SetDoubleDVD(new_mat1, new_mat2);
					new_mat1 = nullptr;
					new_mat2 = nullptr;
				}
				else if (mat->Type == "DVD" || mat->Type == "VHS" || mat->Type == "BluRay")
				{
					mat->SetFilm(LoadFilm(std::stoi(LineData.at(0))));
				}
				return mat;
			}
		}
		LineData.clear();
	}

	return mat;
}

Film FileHandler::LoadFilm(int idToLoad)
{
	std::ifstream LoadFilm;
    LoadFilm.open(FilmDataRead);
	Film film;
	std::string str;
	int currentID = 0;

	while (std::getline(LoadFilm, str))
	{
		std::vector<std::string> LineData = SeparateCommasIntoData(str);

		if ((LineData.at(0) == "ID" && std::stoi(LineData.at(1)) == idToLoad) || currentID == idToLoad)
		{
			if (LineData.at(0) == "ID")
			{
				currentID = std::stoi(LineData.at(1));
				film.ID = idToLoad;
			}
			else if (LineData.at(0) == "Title")
			{
				film.Title = LineData.at(1);
			}
			else if (LineData.at(0) == "Summary")
			{
				film.Summary = LineData.at(1);
			}
			else if (LineData.at(0) == "Genre")
			{
				LineData.erase(LineData.begin());
				film.Genre = LineData;
			}
			else if (LineData.at(0) == "Language")
			{
				LineData.erase(LineData.begin());
				film.Languages = LineData;
				return film;
			}
			else if (LineData.at(0) == "Release_Date")
			{
				film.ReleaseDate = LineData.at(1);
			}
			else if (LineData.at(0) == "Runtime")
			{
				film.Runtime = std::stoi(LineData.at(1));
			}
		}
		LineData.clear();
	}
	return film;
}

void FileHandler::UpdateProjectFile()
{
	browser->setHead();
    std::ofstream newfile(FilmDataWrite);

	while (browser->current->next != nullptr)
	{
		WriteProjectToFile(newfile);
		browser->nextNode();
	}
	WriteProjectToFile(newfile);
}

void FileHandler::WriteProjectToFile(std::ofstream &file)
{
	file << "ID," << browser->current->data->ID << std::endl;
	switch (browser->current->data->Status)
	{
	case FilmProject::Status::Unreleased:
		file << "Status,"
			 << "0" << std::endl;
		break;
	case FilmProject::Status::Now_Playing:
		file << "Status,"
			 << "1" << std::endl;
		break;
	case FilmProject::Status::Released:
		file << "Status,"
			 << "2" << std::endl;
		break;

	default:
		break;
	}
	file << "Title," << browser->current->data->Title << std::endl;
	file << "Keywords,";
	for (auto it = browser->current->data->KeyWords.begin(); it != browser->current->data->KeyWords.end(); ++it)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Summary," << browser->current->data->Summary << std::endl;
	file << "Genre,";
	for (auto it = browser->current->data->Genre.begin(); it != browser->current->data->Genre.end(); ++it)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Release_Date," << browser->current->data->ReleaseDate << std::endl;
	file << "Filming_Loc,";
	for (auto it = browser->current->data->Filming_Locations.begin(); it != browser->current->data->Filming_Locations.end(); ++it)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Runtime," << browser->current->data->Runtime << std::endl;
	file << "Language,";
	for (auto it = browser->current->data->Languages.begin(); it != browser->current->data->Languages.end(); ++it)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Weekly Ticket Sales,";
	for (auto it = browser->current->data->WeeklyTicketSales.begin(); it != browser->current->data->WeeklyTicketSales.end(); ++it)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Crew_Members,";
	for (auto it = browser->current->data->CrewMembers.begin(); it != browser->current->data->CrewMembers.end(); ++it)
	{
		file << (*it).ID << ",";
	}
	file << std::endl;
}

void FileHandler::WriteCrewToFile(std::vector<Crew> crewVec)
{
	std::ofstream writeToCrewFile(CrewData);

	for (auto it = crewVec.begin(); it != crewVec.end(); ++it)
	{
		writeToCrewFile << (*it).ID << "," << (*it).Name << "," << (*it).Job << std::endl;
	}
}

std::vector<std::string> FileHandler::SeparateCommasIntoData(std::string input)
{
	std::vector<std::string> LineData;
	std::regex data("([^,]+)"); // finds all of the data values between the commas and includes spaces for empty data values
	std::smatch data_match;

	if (std::regex_search(input, data_match, data)) // if there are data values to enter
	{
		for (std::sregex_iterator it = std::sregex_iterator(input.begin(), input.end(), data); it != std::sregex_iterator(); ++it)
        {
			data_match = *it;
			LineData.push_back(data_match.str()); // loops through the values between commas (including whitespace) and adds them to a vector
		}
	}
	return LineData;
}

void FileHandler::sortedInsert(struct Node** head_ref, struct Node* newNode)
{
	struct Node* current;


	if (*head_ref == NULL)
		*head_ref = newNode;


	else if ((*head_ref)->data->ID >= newNode->data->ID) {
		newNode->next = *head_ref;
		newNode->next->back = newNode;
        *head_ref = newNode;

	}

	else {

		current = *head_ref;
        while (current->next != NULL && current->next->data->ID < newNode->data->ID)

			current = current->next;
		newNode->next = current->next;

		if (current->next != NULL)
			newNode->next->back = newNode;

		current->next = newNode;
		newNode->back = current;
	}
}


void FileHandler::insertionSort(struct Node** head_ref)
{
	struct Node* sorted = NULL;
	struct Node* current = *head_ref;

	while (current != NULL) {

		struct Node* next = current->next;
        current->back = current->next = NULL;

		sortedInsert(&sorted, current);
		current = next;
	}

	*head_ref = sorted;
}
