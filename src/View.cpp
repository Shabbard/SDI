#include "View.h"

View::View(/* args */)
{
}

View::~View()
{
}

void View::Main_Menu_Templates()
{
	system("clear");
	std::cout << "\n           TrekStar Production Log" << std::endl;
	std::cout << "______________________________________________" << std::endl;
	std::cout << "\n            Please Enter in a Value" << std::endl;
	std::cout << "\nBrowser Mode                        Enter BM" << std::endl;
	std::cout << "Maintenance Mode                    Enter MM\n" << std::endl;
	std::cout << "Exit                                Enter Exit\n" << std::endl;
	std::cout << "______________________________________________\n" << std::endl;
}
void View::BM_Templates()
{
	system("clear");
	std::cout << "\n          Welcome to Browser Mode" << std::endl;
	std::cout << "______________________________________________" << std::endl;
	std::cout << "\n    Please Enter in a Value" << std::endl;
	std::cout << "\nNext                                Enter Next" << std::endl;
	std::cout << "Back                                Enter Back" << std::endl;
	std::cout << "View Crew                           Enter Crew" << std::endl;
	std::cout << "View Material Info                  Enter MI" << std::endl;
	std::cout << "Search                              Enter Search\n" << std::endl;
	std::cout << "Return to Menu                      Enter RTM\n" << std::endl;
	std::cout << "______________________________________________\n" << std::endl;
}
void View::MM_Templates()
{
	system("clear");
	std::cout << "\n     Welcome to Maintenace Mode" << std::endl;
	std::cout << "______________________________________________" << std::endl;
	std::cout << "\nPlease Enter in a Value" << std::endl;
	std::cout << "\nNext                                 Enter Next" << std::endl;
	std::cout << "Back                                 Enter Back" << std::endl;
	std::cout << "View Crew                            Enter Crew" << std::endl;
	std::cout << "View Material Info                   Enter MI\n" << std::endl;
	std::cout << "Create New Project                   Enter CNP" << std::endl;
	std::cout << "Create New Crew                      Enter CNC" << std::endl;
	std::cout << "Create New Material                  Enter CNM" << std::endl;
	std::cout << "Edit                                 Enter EDIT" << std::endl;
	std::cout << "Delete Project                       Enter DP\n" << std::endl;
	std::cout << "Reports Mode                         Enter reports\n" << std::endl;
	std::cout << "Return to Menu                       Enter RTM\n" << std::endl;
	std::cout << "______________________________________________\n" << std::endl;
}

void View::CNP_Templates()
{
	system("clear");

	std::cout << "\n              Add New Project" << std::endl;
	std::cout << "______________________________________________" << std::endl;
	std::cout << "\n   Please follow the instructions below" << std::endl;
	std::cout << "\n  Enter in the values as they are listed" << std::endl;
	std::cout << "\n        You may edit this later on" << std::endl;
	std::cout << "______________________________________________\n" << std::endl;
}

void View::Edit_Templates()
{
	system("clear");
	std::cout << "\n           Welcome to Edit Mode" << std::endl;
	std::cout << "______________________________________________\n" << std::endl;
	std::cout << "Step 1: Enter in the database you want to edit\n" << std::endl;
	std::cout << "Step 2: Enter in the datatype you want ot edit\n " << std::endl;
	std::cout << "Step 3: Make your changes\n " << std::endl;
	std::cout << "Return to menu	 						 RTM\n" << std::endl;
	std::cout << "______________________________________________\n" << std::endl;
	std::cout << "Please enter the section you would like to edit " << std::endl;
		std::cout << "          (project,crew or material)            \n"
				  << std::endl;
		std::cout << "- ";
}

void View::DisplayCrew(std::vector<Crew*> crewVec)
{
	std::cout << "___________________________________\n" << std::endl;
   	std::cout << "            Crew Members             " << "\n"<< std::endl;
   	std::cout << " ID             Name            Job\n" << std::endl;
   	for(auto it = crewVec.begin(); it != crewVec.end(); ++it)
	{   
      	std::cout << "- " << (*it)->ID<< "\t"<< (*it)->Name << "\t\t\t" << (*it)->Job << std::endl;
	}
   	std::cout << "\n";
}

void View::DisplayCurrentFilmProject(FilmProject* film)
{
	std::cout << "        Project Data " << std::endl;
   std::cout << "Datatype"<< "\t\t" << "Data\n" << std::endl;
   std::cout << "ID" << "\t\t\t"<< film->ID << std::endl;
   switch (film->Status)
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
	std::cout << "Title" << "\t\t\t"<< film->Title << std::endl;
	std::cout << "Keywords"<< "\t\t";
	for(auto it = film->KeyWords.begin(); it != film->KeyWords.end(); ++it)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Summary" << "\t\t\t"<< film->Summary << std::endl;
	std::cout << "Genre"<< "\t\t\t";
	for(auto it = film->Genre.begin(); it != film->Genre.end(); ++it)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Release_Date" << "\t\t"<< film->ReleaseDate << std::endl;
	std::cout << "Filming_Loc"<< "\t\t";
	for(auto it = film->Filming_Locations.begin(); it != film->Filming_Locations.end(); ++it)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Runtime" << "\t\t\t"<< film->Runtime << " Minutes "<< std::endl;
	std::cout << "Language"<< "\t\t";
	for(auto it = film->Languages.begin(); it != film->Languages.end(); ++it)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	if (film->Status == 1)
	{
		std::cout << "Weekly Ticket Sales," << "\t" << "£";
		for (auto it = film->WeeklyTicketSales.begin(); it != film->WeeklyTicketSales.end(); ++it)
		{
			std::cout << *it << ",";
		}
		std::cout << std::endl;
	}
   	std::cout << "Crew Member ID's" << "\t";
	for(auto it = film->CrewMembers.begin(); it != film->CrewMembers.end(); ++it)
	{
		std::cout << (*it)->ID << ",";
	}
   	std::cout << std::endl;
	if (film->Status == 2)
	{
		std::cout << "Material ID's" << "\t\t";
		for(auto it = film->Materials.begin(); it != film->Materials.end(); ++it)
		{
			std::cout << (*it)->ID << ",";
		}
		std::cout << std::endl;
	}
   	std::cout << std::endl;
}

void View::DisplayMaterial()
{
	std::cout << "________________________________________________\n\n"
			  << std::endl;
	std::cout << "                     Materials                 "
			  << "\n"
			  << std::endl;
}

void View::Vector_Instructions()
{
    std::cout << "Type in the value then press enter to add another value" << std::endl;
	std::cout << "When you have finished enter in (case sensitive) - Q" << std::endl;
}

void View::Next_Back_Instructions()
{
	std::cout << "\nNext                                Enter Next" << std::endl;
	std::cout << "Back                                Enter Back\n" << std::endl;
	std::cout << "________________________________________________\n" << std::endl;
}

void View::LoadMatData(Material* mat, std::string strvar)
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

void View::value_error()
{
	std::cout << "\n                     ERROR             " << std::endl;
	std::cout << "\n         Please enter correct value    \n" << std::endl;
}

void View::DisplayCreateNewCrew()
{
	system("clear");
	std::cout << "________________________________________________\n\n" << std::endl;
	std::cout << "           Create New Crew Member                 " << "\n" << std::endl;

}

void View::DisplayCreateNewMaterial()
{
	system("clear");
	std::cout << "________________________________________________\n\n" << std::endl;
	std::cout << "              Create New Material                 " << "\n" << std::endl;
	std::cout << "\nPlease insert the type of Material:";
	std::cout << "\nTypes are: VHS, DVD(SingleSided), BluRay, ComboBox, DoubleSidedDVD\n";
}
void View::ShowInsertCrewName()
{
	std::cout << "\nPlease insert the Crew Members Name: ";
}
void View::ShowInsertCrewJob()
{
	std::cout << "\nPlease insert the Crew Members Job: ";
}
void View::ShowStatusMeaning()
{
	std::cout << "\nUnreleased 0, Now_Playing 1, Released 2\n";
}
void View::ShowInsertStatus()
{
	std::cout << "\nPlease insert a Status Number: ";
}
void View::ShowInsertTitle()
{
	std::cout << "\nPlease insert a Title: ";
}
void View::ShowInsertKeywords()
{
	std::cout << "\nPlease insert the Keyword(s): " << std::endl;
}
void View::ShowInsertSummary()
{
	std::cout << "\nPlease insert a Summary: ";
}
void View::ShowInsertGenre()
{
	std::cout << "\nPlease insert the Genre(s): " << std::endl;
}
void View::ShowInsertReleaseDate()
{
	std::cout << "\nPlease insert a Release Date: ";
}
void View::ShowInsertFilmingLocations()
{
	std::cout << "\nPlease insert the Filming Location(s): " << std::endl;
}
void View::ShowInsertRuntime()
{
	std::cout << "\nPlease insert the Runtime: ";
}
void View::ShowInsertLanguages()
{
	std::cout << "\nPlease insert the Language(s): " << std::endl;
}
void View::ShowInsertWeeklyTicketSale()
{
	std::cout << "\nPlease insert the Weekly Ticket Sale: ";
}
void View::ShowInsertDataType()
{
	std::cout << "Please enter in the datatype you want to edit\n" << std::endl;
}
void View::ShowInsertFrameAspect()
{
	std::cout << "Please entert the frame aspect: ";
}
void View::ShowInsertDescription()
{
	std::cout << "\nPlease insert the Description:\n"<< std::endl;
}
void View::ShowInsertVideoFormat()
{
	std::cout << "\nPlease insert the Video Format:\n"<< std::endl; 
}
void View::ShowInsertAudioFormat()
{
	std::cout << "\nPlease insert the Audio Format:\n"<< std::endl;
}
void View::ShowInsertRetailPrice()
{
	std::cout << "\nPlease insert the Retail Price:\n"<< std::endl;
}
void View::ShowInsertSubtitles()
{
	std::cout << "\nPlease insert the Subtitle Language(s):\n"<< std::endl;
}
void View::ShowInsertNumMaterials()
{
	std::cout << "\nEnter the number of materials stored in the combo box\n"<< std::endl;
}
void View::ShowInsertFilmIDs()
{
	std::cout << "\nEnter the ID's of the films to store on this material\n"<< std::endl;
}
void View::ShowVectorEdit(std::vector<std::string> strVec)
{
	int counter= 0;
	std::cout << "\n";
	for (auto it = strVec.begin(); it != strVec.end(); ++it)
	{
		std::cout << counter << " - " << *it << "\n";
		counter++;
	}
	std::cout << "\n" << counter << " - " << "Enter in this number to add a new value " << std::endl;
	std::cout << "000" << " - " << "Enter in this number to delete a value " << std::endl;
}
void View::ShowInsertEditGenre()
{
	std::cout << "\nPlease Enter in a Genre number you want to edit\n";
}
void View::ShowInsertPackaging()
{
	std::cout << "\nPlease Enter in a the type of packaging, either plastic or cardboard\n";
}
void View::ShowInsertEditKeywords()
{
	std::cout << "\nPlease Enter in a keywords number you want to edit\n";
}
void View::ShowDeleteGenre()
{
	std::cout << "\nPlease enter in the Genre number you want to delete\n";
}
void View::ShowDeleteKeywords()
{
	std::cout << "\nPlease enter in the keyword number you want to delete\n";
}
void View::ShowDeleteFilmingLocations()
{
	std::cout << "\nPlease enter in the filming location number you want to delete\n";
}
void View::ShowDeleteLanguages()
{
	std::cout << "\nPlease enter in the language number you want to delete\n";
}
void View::ShowDeleteSubtitles()
{
	std::cout << "\nPlease enter in the subtitle number you want to delete\n";
}
void View::ShowEditDeleteCrew()
{
	std::cout << "\nPlease choose edit or delete to manage the crew members\n";
}
void View::ShowRequestCrewID()
{
	std::cout << "\nPlease choose the ID of the crew member you wish to edit\n";
}
void View::ShowRequestMaterialID()
{
	std::cout << "\nPlease choose the ID of the material you wish to edit (000 to exit)\n";
}
void View::ShowDeleteCrew()
{
	std::cout << "\nPlease enter in the ID of the crew member you want to delete\n";
}
void View::ShowAddCrew()
{
	std::cout << "\nPlease enter in the ID of the crew member you want to add\n";
}
void View::ShowAddMaterial()
{
	std::cout << "\nPlease enter in the ID of the material you want to add\n";
}
void View::ShowDeleteMaterial()
{
	std::cout << "\nPlease enter in the ID of the material you want to delete\n";
}
void View::ShowAddDeleteCrew()
{
	std::cout << "\nPlease enter 'delete' to delete crew members from this project or 'add' to add crew members to this project\n";
}
void View::ShowAddDeleteMaterial()
{
	std::cout << "\nPlease enter 'delete' to delete materials from this project or 'add' to add materials to this project\n";
}
void View::ShowSearchRequest()
{	
	std::cout << "\nWould you like to search for projects by Actor Name : Enter Actor" << std::endl;
	std::cout << "Would you like to search for a project Title        : Enter Title\n";
	std::cout << "\nReturn to Browser Menu                              : Enter rtm\n";
}
void View::ShowEnterProjectTitle()
{
	std::cout << "\nPlease enter a Project Title - ";
}
void View::ShowEnterActorName()
{
	std::cout << "\nPlease enter an actors name  - ";
}
void View::DisplayFilmTitles(std::vector<std::string> films, std::string actorName)
{
	std::cout << actorName <<" appears in the following films: \n";
	for (auto it = films.begin(); it != films.end(); ++it)
	{
		std::cout << (*it) << std::endl;
	}
}
void View::ReportsOptions()
{
	std::cout << "\n         Please select a report option            \n";
	std::cout << "Data Report:     New Projects and Materials Made today" << std::endl;
	std::cout << "Earnings Report: Projects with a certain Box Office Earning"<< std::endl;
	std::cout << "rtm:             Return to Menu        \n"<< std::endl;
}

void View::New_data_report()
{
	std::cout <<"\n Time          Change Type";

}

void View::Total_Earnings_report(FilmProject* filmProject)
{
	std::cout << "\nProject Title: " << filmProject->Title;
	std::cout << "\nProject ID: " << filmProject->ID;
	std::cout << "\nProjects Total Weekly Earnings:" << std::accumulate(filmProject->WeeklyTicketSales.begin(), filmProject->WeeklyTicketSales.end(), 0);
}
void View::DisplayEarningsReport()
{
	std::cout << "\nPlease enter a threshold value for the earnings report; ";
}
