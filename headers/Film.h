#pragma once
#ifndef FILM_H
#define FILM_H
#include <string>
#include <vector>

struct Crew
{
  int ID = 0;
  std::string Name;
  std::string Job;
};

class Film
{
  public:
    std::string Title, Summary, ReleaseDate;
    std::vector<std::string> Genre, Languages;
    int ID = 0, Runtime = 0;
};

#endif