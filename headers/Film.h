#ifndef FILM_H
#define FILM_H
#include "Material.h"
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
    enum Status { Unreleased, Now_Playing, Released };
    int ID, Runtime, Status;
    double WeeklyTicketSales;
    //std::vector<Material*> Materials;
};

#endif