#include <string>
#include <vector>
#pragma once

struct Crew
{
  int ID;
  std::string Name;
  std::string Job;
};

class Film
{
  private:
    
  public:
    Film();
    ~Film();
    std::string Title, Summary, ReleaseDate;
    std::vector<std::string> Genre, Filming_Locations, Languages, KeyWords;
    std::vector<Crew> CrewMembers;
    int ID, Runtime, Status;
    double WeeklyTicketSales;
};

