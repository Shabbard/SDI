#pragma once
#include "Film.h"
#include "Material.h"

class FilmProject : public Film
{
    public:
        ~FilmProject();
        double WeeklyTicketSales = 0;
        std::vector<Material*> Materials;
        std::vector<Crew> CrewMembers;
        enum Status { Unreleased, Now_Playing, Released };
        int Status = 0;
        std::vector<std::string> Filming_Locations, KeyWords;
};