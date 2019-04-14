# include "FileHandler.h"

FileHandler::FileHandler(Browser* input)
{
    browser = input;
}

FileHandler::~FileHandler()
{

}

void FileHandler::LoadFile(std::string filePath)
{
	std::ifstream infile;
    infile.open(filePath);

	Film* film = new Film;

	std::string str;

	std::string values[10] = {"ID","Title", "Summary", "Genre", "Release Date", "Filming Locations", "Language", "Runtime", "Keywords", "Weekly Ticket Sales"};
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

		if(LineData.at(0)== "ID")
		{
			film->ID = std::stoi(LineData.at(1));
		}
		else if(LineData.at(0)== "Status")
		{
			film->Status = std::stoi(LineData.at(1));
		}
		else if(LineData.at(0)== "Title")
		{
			film->Title = LineData.at(1);
		}
		else if(LineData.at(0)== "Summary")
		{
			film->Summary = LineData.at(1);
		}
		else if(LineData.at(0)== "Genre")
		{
			LineData.erase(LineData.begin());
			film->Genre = LineData;
		}
		else if(LineData.at(0)== "Release_Date")
		{
			film->ReleaseDate = LineData.at(1);
		}
		else if(LineData.at(0)== "Filming_Loc")
		{
            LineData.erase(LineData.begin());
			film->Filming_Locations = LineData;
		}
		else if(LineData.at(0)== "Language")
		{
			LineData.erase(LineData.begin());
			film->Languages = LineData;
		}
		else if(LineData.at(0)== "Runtime")
		{
			film->Runtime = std::stoi(LineData.at(1));
		}
		else if(LineData.at(0)== "Keywords")
		{
			LineData.erase(LineData.begin());
			film->KeyWords = LineData;
		}
		else if(LineData.at(0)== "Weekly Ticket Sales")
		{
			film->WeeklyTicketSales = std::stoi(LineData.at(1));
		}
		else if(LineData.at(0)== "Crew_Members")
		{
			LineData.erase(LineData.begin());
            film->Crew_Members_String = LineData;
            browser->insert_tail(film);
			film = new Film();
		}
		
		LineData.clear();
	}
	film = nullptr;
} 

void FileHandler::UpdateFile(std::string filePath)
{
	browser->setHead();
	
	std::ofstream newfile(filePath);

	std::string str;

	while(browser->current != nullptr)
	{		
		WriteToFile(newfile);

		if(browser->current->next == nullptr) // please find a better way of doing this
		{
			browser->nextNode();
			WriteToFile(newfile);
		}
	}
}

void FileHandler::WriteToFile(std::ofstream& file)
{
	file << "ID," << browser->current->data->ID << std::endl;
	file << "Status," << browser->current->data->Status << std::endl;
	file << "Title," << browser->current->data->Title << std::endl;
	file << "Keywords,";
	for(std::vector<std::string>::iterator it = browser->current->data->KeyWords.begin(); it != browser->current->data->KeyWords.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Summary," << browser->current->data->Summary << std::endl;
	file << "Genre,";
	for(std::vector<std::string>::iterator it = browser->current->data->Genre.begin(); it != browser->current->data->Genre.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Release_Date," << browser->current->data->ReleaseDate << std::endl;
	file << "Filming_Loc,";
	for(std::vector<std::string>::iterator it = browser->current->data->Filming_Locations.begin(); it != browser->current->data->Filming_Locations.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Runtime," << browser->current->data->Runtime << std::endl;
	file << "Language,";
	for(std::vector<std::string>::iterator it = browser->current->data->Languages.begin(); it != browser->current->data->Languages.end(); it++)
	{
		file << *it << ",";
	}
	file << std::endl;
	file << "Weekly Ticket Sales," << browser->current->data->WeeklyTicketSales << std::endl;
}
