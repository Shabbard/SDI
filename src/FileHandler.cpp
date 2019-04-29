#include "FileHandler.h"

FileHandler::FileHandler(Browser *browserinput, std::vector<Crew*>* crewinput, std::vector<Material*>* matinput)
{
	browser = browserinput;
	crewVector = crewinput;
	matVector = matinput;
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
				if (LoadCrew(std::stoi(*it)) != nullptr)
				{
					film->CrewMembers.push_back(LoadCrew(std::stoi(*it)));
				}
			}
			std::sort(film->CrewMembers.begin(), film->CrewMembers.end());	
		}
		else if (LineData.at(0) == "Material_ID")
		{
			LineData.erase(LineData.begin());
			for (auto it = LineData.begin(); it != LineData.end(); ++it)
			{
				if(LoadProjectMaterial(std::stoi(*it)) != nullptr)
				{
					film->Materials.push_back(LoadProjectMaterial(std::stoi(*it)));
				}
			}
			browser->insert_tail(film);
            film = nullptr;
			film = new FilmProject();
		}
		LineData.clear();
	}

    browser->insertionSort();

	delete film;
	film = nullptr;
}

void FileHandler::LoadEntireCrew()
{
	std::ifstream infile;
	infile.open(CrewData);
	std::string str;

	while (std::getline(infile, str))
	{
		std::vector<std::string> LineData = SeparateCommasIntoData(str);
		Crew* new_crew = new Crew();
		new_crew->ID = std::stoi(LineData.at(0));
		new_crew->Name = LineData.at(1);
		new_crew->Job = LineData.at(2);
		crewVector->push_back(new_crew);
	}
    std::sort(crewVector->begin(), crewVector->end());
}

void FileHandler::LoadAllMaterials()
{
	std::ifstream materialFile;
	materialFile.open(MaterialData);
	std::string str;

	while (std::getline(materialFile, str))
	{
		std::vector<std::string> LineData = SeparateCommasIntoData(str);
		if (LineData.at(0) == "ID")
		{
			if (LoadProjectMaterial(std::stoi(LineData.at(1))) == nullptr)
			{
				Material* new_mat = new Material();
				new_mat->ID = std::stoi(LineData.at(1));
				new_mat = GetMaterialType(new_mat, new_mat->ID);
				LoadMaterial(new_mat, new_mat->ID);
				matVector->push_back(new_mat);
			}
		}
	}
}

Crew* FileHandler::LoadCrew(int idToFind)
{
	for (auto it = crewVector->begin(); it != crewVector->end(); ++it) { if ((*it)->ID == idToFind) { return (*it); } }	
	return nullptr;
}

template <typename T>
T FileHandler::GetMaterialType(T mat, int idToFind)
{
	std::ifstream MatFile;
	MatFile.open(MaterialData);
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

			std::transform(matTypeVec.at(1).begin(), matTypeVec.at(1).end(), matTypeVec.at(1).begin(), ::tolower);

			if (matTypeVec.at(1) == "combobox")
			{
				delete mat;
				mat = new ComboBox();
			}
			else if (matTypeVec.at(1) == "vhs")
			{
				delete mat;
				mat = new VHS();
			}
			else if (matTypeVec.at(1) == "dvd")
			{
				delete mat;
				mat = new DVD();
			}
			else if (matTypeVec.at(1) == "doublesideddvd")
			{
				delete mat;
				mat = new DoubleSidedDVD();
			}
			else if (matTypeVec.at(1) == "bluray")
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
				if (mat->Type == "combobox")
				{
					for (auto it = LineData.begin(); it != LineData.end(); ++it)
					{
						if (LoadProjectMaterial(std::stoi(*it)) == nullptr)
						{
							auto new_mat = new Material();
							new_mat = GetMaterialType(new_mat, std::stoi(*it));
							LoadMaterial(new_mat, std::stoi(*it));
							mat->SetDVDVector(new_mat);
							matVector->push_back(new_mat);
							new_mat = nullptr;
						}
						else
						{
							mat->SetDVDVector(LoadProjectMaterial(std::stoi(*it)));
						}
					}
				}
				else if (mat->Type == "doublesideddvd")
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
				else if (mat->Type == "dvd" || mat->Type == "vhs" || mat->Type == "bluray")
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

Material* FileHandler::LoadProjectMaterial(int idToFind)
{
	for (auto it = matVector->begin(); it != matVector->end(); ++it) {if ((*it)->ID == idToFind) {return (*it);}}
	return nullptr;
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
		file << (*it)->ID << ",";
	}
	file << std::endl;
	file << "Material_ID,";
	for (auto it = browser->current->data->Materials.begin(); it != browser->current->data->Materials.end(); ++it)
	{
		file << (*it)->ID << ",";
	}
	file << std::endl;
}

void FileHandler::WriteCrewToFile()
{
	std::ofstream writeToCrewFile(CrewData);

	for (auto it = crewVector->begin(); it != crewVector->end(); ++it)
	{
		writeToCrewFile << (*it)->ID << "," << (*it)->Name << "," << (*it)->Job << std::endl;
	}
}
void FileHandler::WriteMaterialToFile()
{
	std::ofstream writeToMaterialFile(MaterialData);

	for (auto it = matVector->begin(); it != matVector->end(); ++it)
	{
		writeToMaterialFile << "ID," <<  (*it)->ID << std::endl;
		writeToMaterialFile << "Type," << (*it)->Type << std::endl;
		writeToMaterialFile << "Title," << (*it)->Title << std::endl;
		writeToMaterialFile << "DVD_Description," << (*it)->Description << std::endl;
		writeToMaterialFile << "Video_Format," << (*it)->VideoFormat << std::endl;
		writeToMaterialFile << "Audio_Format," << (*it)->AudioFormat << std::endl;
		writeToMaterialFile << "Run_Time," << (*it)->Runtime << std::endl;
		writeToMaterialFile << "Languages,";
		for (auto i = 0; i != (*it)->GetNumLanguages(); ++i)
		{
			writeToMaterialFile << ((*it)->GetLanguage(i)) << ",";
		}
		writeToMaterialFile << std::endl;
		writeToMaterialFile << "Retail_Price," << (*it)->RetailPrice << std::endl;
		writeToMaterialFile << "Subtitles,";
		for (auto i = 0; i != (*it)->GetNumSubtitles(); ++i)
		{
			writeToMaterialFile << ((*it)->GetSubtitle(i)) << ",";
		}
		writeToMaterialFile << std::endl;
		writeToMaterialFile << "Frame_Aspect," << (*it)->FrameAspect << std::endl;
		writeToMaterialFile << "Packaging," << (*it)->Packaging << std::endl;
		writeToMaterialFile << "Stored,";
		if ((*it)->Type == "combobox")
		{	
			auto temp =(*it)->GetDVDs();
			for (auto i = temp.begin(); i != temp.end(); ++i)
			{
				writeToMaterialFile << (*it)->ID << ",";
			}
		}
		else if ((*it)->Type == "doublesideddvd")
		{
			auto temp = (*it)-> GetDVDPair();
			writeToMaterialFile << temp.first->ID << ",";
			writeToMaterialFile << temp.second->ID << ",";			
		}
		else
		{
			auto temp = (*it)->GetFilm();
			writeToMaterialFile << temp.ID;
		}
		writeToMaterialFile << std::endl;
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

void FileHandler::Tracking(int change)
{
	time_t now = time(0);
	char* dt = ctime(&now);

	std::ofstream logFile;
	logFile.open("../data/logFile.txt", std::ios_base::app);

	if(change == 1)
	{
		logFile << "\n" << dt << " Project Created" << std::endl;
		logFile.close();
	}
	if(change == 2)
	{
		logFile << "\n" << dt << " Material Created" << std::endl;
		logFile.close();
	}
}