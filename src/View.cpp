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
	std::cout << "Save                                Enter Save\n" << std::endl;
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
	std::cout << "\nNext                               Enter Next" << std::endl;
	std::cout << "Back                                 Enter Back" << std::endl;
	std::cout << "View Crew                            Enter Crew" << std::endl;
	std::cout << "View Material Info                   Enter MI\n" << std::endl;
	std::cout << "Create New Project                   Enter CNP" << std::endl;
	std::cout << "Create New Crew                      Enter CNC" << std::endl;
	std::cout << "Create New Material                  Enter CNM" << std::endl;
	std::cout << "Edit                                 Enter EDIT" << std::endl;
	std::cout << "Delete Project                       Enter DP\n" << std::endl;
	std::cout << "Reports Mode                         Enter R\n" << std::endl;
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
	std::cout << "______________________________________________\n" << std::endl;
}

void View::DisplayCrew(std::vector<Crew> crewVec)
{
	std::cout << "___________________________________\n" << std::endl;
   	std::cout << "            Crew Members             " << "\n"<< std::endl;
   	std::cout << " ID             Name            Job\n" << std::endl;
   	for(auto it = crewVec.begin(); it != crewVec.end(); ++it)
	{   
      	std::cout << "- " << (*it).ID<< "\t"<< (*it).Name << "\t\t" << (*it).Job << std::endl;
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
		std::cout << (*it).ID << ",";
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
