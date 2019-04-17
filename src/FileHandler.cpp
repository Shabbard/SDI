#include "FileHandler.h"

FileHandler::FileHandler(Browser *input)
{
	browser = input;
}

void FileHandler::LoadFile()
{
	std::ifstream infile;
	infile.open(FilmData);

	FilmProject *film = new FilmProject;

	std::string str;

	std::string values[10] = {"ID", "Title", "Summary", "Genre", "Release Date", "Filming Locations", "Language", "Runtime", "Keywords", "Weekly Ticket Sales"};
	std::vector<std::string> LineData;

	while (std::getline(infile, str))
	{
		std::regex data("([^,]+)"); // finds all of the data values between the commas and includes spaces for empty data values
		std::smatch data_match;

		if (std::regex_search(str, data_match, data)) // if there are data values to enter
		{
			for (std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), data); i != std::sregex_iterator(); ++i)
			{
				data_match = *i;
				LineData.push_back(data_match.str()); // loops through the values between commas (including whitespace) and adds them to a vector
			}
		}

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
			film->WeeklyTicketSales = std::stoi(LineData.at(1));
		}
		else if (LineData.at(0) == "Crew_Members")
		{
			LineData.erase(LineData.begin());
			for (std::vector<std::string>::iterator it = LineData.begin(); it != LineData.end(); it++)
			{
				Crew temp;
				temp.ID = std::stoi(*it);
				temp = LoadCrew(temp);
				if (!temp.ID == 0)
				{
					film->CrewMembers.push_back(temp);
				}
			}
		}
        else if (LineData.at(0) == "Material_ID")
		{
			LineData.erase(LineData.begin());
			std::vector<int> matIDVec;
			std::vector<std::string> matTypeVec;
			for (std::vector<std::string>::iterator it = LineData.begin(); it != LineData.end(); ++it)
			{
				matIDVec.push_back(std::stoi(*it));
			}

			std::ifstream MatFile;
			MatFile.open("../data/Material_Data.txt");
			std::string readline;
            auto mat = new Material();
            int currentID = 0;
			
            for (size_t it = 0; it != matIDVec.size(); ++it)
			{
				while (std::getline(MatFile, readline))
				{
					std::regex type("(Type)");
					std::regex ID("(ID)");
					std::smatch data_match;
					if (std::regex_search(readline, data_match, type) && (std::find(matIDVec.begin(), matIDVec.end(), currentID) != matIDVec.end()))
					{
						std::regex data("([^,]+)");

						if (std::regex_search(readline, data_match, data))
						{
                            for (std::sregex_iterator i = std::sregex_iterator(readline.begin(), readline.end(), data); i != std::sregex_iterator(); ++i)
							{
								data_match = *i;
								matTypeVec.push_back(data_match.str());
							}
						}

						if (matTypeVec.at(1) == "ComboBox")
						{
							mat = new ComboBox();
						}
						else if (matTypeVec.at(1) == "VHS")
						{
							mat = new VHS();
						}
						else if (matTypeVec.at(1) == "DVD")
						{
							mat = new DVD();
						}
						else if (matTypeVec.at(1) == "DoubleSidedDVD")
						{
							mat = new DoubleSidedDVD();
						}
						else if (matTypeVec.at(1) == "BluRay")
						{
							mat = new BluRay();
						}

						mat->ID = matIDVec.at(it);
                		mat->Type = matTypeVec.at(1);
                        mat = LoadMaterial(mat, currentID);
						film->Materials.push_back(mat);
                		mat = new Material();
                        matTypeVec.clear();
								
					}	
					else if (std::regex_search(readline, data_match, ID))
					{
						std::regex data("([^,]+)");

						if (std::regex_search(readline, data_match, data))
						{
                            std::vector<std::string> temp;
                            for (std::sregex_iterator i = std::sregex_iterator(readline.begin(), readline.end(), data); i != std::sregex_iterator(); ++i)
							{
								data_match = *i;

                                temp.push_back(data_match.str());
							}
                            currentID = std::stoi(temp.at(1));
						}
					}
				}   
			}
			browser->insert_tail(film);
			film = new FilmProject();
		}
		LineData.clear();
	}
	film = nullptr;
}


Crew FileHandler::LoadCrew(Crew CrewMember)
{
	std::ifstream infile;
	infile.open(CrewData);

	std::string str;

	std::vector<std::string> LineData;

	while (std::getline(infile, str))
	{
		std::regex data("([^,]+)"); // finds all of the data values between the commas and includes spaces for empty data values
		std::smatch data_match;

		if (std::regex_search(str, data_match, data)) // if there are data values to enter
		{
			for (std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), data); i != std::sregex_iterator(); ++i)
			{
				data_match = *i;
				LineData.push_back(data_match.str()); // loops through the values between commas (including whitespace) and adds them to a vector
			}
		}

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

template<typename T>
T FileHandler::LoadMaterial(T mat, int currentID)
{
	std::ifstream MaterialFile;
	MaterialFile.open(MaterialData);
	std::string str;
    int currID = 0;

	std::vector<std::string> LineData;

	while (std::getline(MaterialFile, str))
	{
		std::regex data("([^,]+)"); // finds all of the data values between the commas and includes spaces for empty data values
		std::smatch data_match;

		if (std::regex_search(str, data_match, data)) // if there are data values to enter
		{
            for (std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), data); i != std::sregex_iterator(); ++i)
			{
				data_match = *i;
				LineData.push_back(data_match.str()); // loops through the values between commas (including whitespace) and adds them to a vector
			}
		}

        if((LineData.at(0) == "ID" && std::stoi(LineData.at(1)) == currentID) || currID == currentID)
		{
            if (LineData.at(0) == "ID" && std::stoi(LineData.at(1)) == currentID)
            {
               currID = std::stoi(LineData.at(1));
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
				if (LineData.size() > 1)
				{
					mat->Languages = LineData;
				}
				else
				{
					//mat->Languages = LineData.at(0);
				}
			}
			else if (LineData.at(0) == "Retail_Price")
			{
				mat->RetailPrice = std::stoi(LineData.at(1));
			}
			else if (LineData.at(0) == "Subtitles")
			{
				LineData.erase(LineData.begin());
				if (LineData.size() > 1)
				{
					mat->Subtitles = LineData;
				}
				else
				{
					//mat->Subtitles = LineData.at(0);
				}
			}
			else if (LineData.at(0) == "Frame_Aspect")
			{
				mat->FrameAspect = LineData.at(1);
			}
			else if (LineData.at(0) == "Packaging")
			{
				mat->Packaging = LineData.at(1);
				return mat;
			}
			else if (LineData.at(0) == "Stored")
			{
				//std::string s = typeid(mat).name();
				if (mat->Type == "ComboBox")
				{
					//std::ifstream 
					// we are storing other materials
	               //mat->DVDs.emplace_back();
				}
				else if (mat->Type == "DoubleSidedDVD")
				{
					// we are storing other materials
					// store two DVD's that each have films
				}
			}
		}

		LineData.clear();
	}

	return mat;
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
