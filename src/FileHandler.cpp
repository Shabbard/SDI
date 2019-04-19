#include "FileHandler.h"

FileHandler::FileHandler(Browser *input)
{
	browser = input;
}

void FileHandler::LoadFilmProjects()
{
	std::ifstream infile;
	infile.open(FilmData);
	FilmProject film; // = new FilmProject();
	std::string str;

	while (std::getline(infile, str))
	{
		std::vector<std::string> LineData = SeparateCommasIntoData(str);

		if (LineData.at(0) == "ID")
		{
			film.ID = std::stoi(LineData.at(1));
		}
		else if (LineData.at(0) == "Status")
		{
			film.Status = std::stoi(LineData.at(1));
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
		else if (LineData.at(0) == "Release_Date")
		{
			film.ReleaseDate = LineData.at(1);
		}
		else if (LineData.at(0) == "Filming_Loc")
		{
			LineData.erase(LineData.begin());
			film.Filming_Locations = LineData;
		}
		else if (LineData.at(0) == "Language")
		{
			LineData.erase(LineData.begin());
			film.Languages = LineData;
		}
		else if (LineData.at(0) == "Runtime")
		{
			film.Runtime = std::stoi(LineData.at(1));
		}
		else if (LineData.at(0) == "Keywords")
		{
			LineData.erase(LineData.begin());
			film.KeyWords = LineData;
		}
		else if (LineData.at(0) == "Weekly Ticket Sales")
		{
			film.WeeklyTicketSales = std::stoi(LineData.at(1));
		}
		else if (LineData.at(0) == "Crew_Members")
		{
			LineData.erase(LineData.begin());
			for (std::vector<std::string>::iterator it = LineData.begin(); it != LineData.end(); it++)
			{
				Crew temp;
				temp.ID = std::stoi(*it);
				temp = LoadCrew(temp);
				if (temp.ID != 0)
				{
					film.CrewMembers.push_back(temp);
				}
			}
		}
		else if (LineData.at(0) == "Material_ID")
		{
			LineData.erase(LineData.begin());
			auto mat = new Material();

			for (std::vector<std::string>::iterator it = LineData.begin(); it != LineData.end(); ++it)
			{
                mat = GetMaterialType(mat, std::stoi(*it));
				LoadMaterial(mat, std::stoi(*it));
				film.Materials.push_back(mat);
				mat = nullptr;
			}
			FilmProject* filmToPass = &film;
			browser->insert_tail(filmToPass);
			// film = nullptr;//new FilmProject();
            // film = new FilmProject();
		}
		LineData.clear();
	}
	// film = nullptr;
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
			else if (LineData.at(0) == "Packaging")
			{
				mat->Packaging = LineData.at(1);
			}
			else if (LineData.at(0) == "Stored")
			{
				LineData.erase(LineData.begin());
				if (mat->Type == "ComboBox")
				{
					for (size_t i = 0; i != LineData.size(); i++)
					{
						auto new_mat = new Material();
						new_mat = GetMaterialType(new_mat, std::stoi(LineData.at(i)));
						LoadMaterial(new_mat, std::stoi(LineData.at(i)));
						mat->SetDVDVector(new_mat);
						new_mat = nullptr;
					}
				}
				else if (mat->Type == "DoubleSidedDVD")
				{
					mat->SetDoubleDVD(LoadFilm(std::stoi(LineData.at(0))), LoadFilm(std::stoi(LineData.at(1))));
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
	LoadFilm.open(FilmData);
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

void FileHandler::UpdateFile()
{
	browser->setHead();
	std::ofstream newfile(FilmData);

	while (browser->current->next != nullptr)
	{
		WriteToFile(newfile);
		browser->nextNode();
	}
	WriteToFile(newfile);
}

void FileHandler::WriteToFile(std::ofstream &file)
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
	for (std::vector<std::string>::iterator it = browser->current->data->KeyWords.begin(); it != browser->current->data->KeyWords.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Summary," << browser->current->data->Summary << std::endl;
	file << "Genre,";
	for (std::vector<std::string>::iterator it = browser->current->data->Genre.begin(); it != browser->current->data->Genre.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Release_Date," << browser->current->data->ReleaseDate << std::endl;
	file << "Filming_Loc,";
	for (std::vector<std::string>::iterator it = browser->current->data->Filming_Locations.begin(); it != browser->current->data->Filming_Locations.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Runtime," << browser->current->data->Runtime << std::endl;
	file << "Language,";
	for (std::vector<std::string>::iterator it = browser->current->data->Languages.begin(); it != browser->current->data->Languages.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Weekly Ticket Sales," << browser->current->data->WeeklyTicketSales << std::endl;
	file << "Crew_Members,";
	for (std::vector<Crew>::iterator it = browser->current->data->CrewMembers.begin(); it != browser->current->data->CrewMembers.end(); it++)
	{
		Crew temp = *it;
		file << temp.ID << ",";
	}
	file << std::endl;
}

std::vector<std::string> FileHandler::SeparateCommasIntoData(std::string input)
{
	std::vector<std::string> LineData;
	std::regex data("([^,]+)"); // finds all of the data values between the commas and includes spaces for empty data values
	std::smatch data_match;

	if (std::regex_search(input, data_match, data)) // if there are data values to enter
	{
		for (std::sregex_iterator i = std::sregex_iterator(input.begin(), input.end(), data); i != std::sregex_iterator(); ++i)
		{
			data_match = *i;
			LineData.push_back(data_match.str()); // loops through the values between commas (including whitespace) and adds them to a vector
		}
	}
	return LineData;
}
