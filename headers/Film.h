#include <string>
#include <vector>
#pragma once

class Film
{
  private:
    
  public:
    Film();
    ~Film();
    std::string Title, Summary, ReleaseDate;
    std::vector<std::string> Genre, Filming_Locations, Languages, KeyWords;
    int ID, Runtime;
    double WeeklyTicketSale;

};
