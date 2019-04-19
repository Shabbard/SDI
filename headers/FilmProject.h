#pragma once
#ifndef FILMPROJECT_H
#define FILMPROJECT_H
#include "Film.h"
#include "Material.h"

class FilmProject : public Film
{
    public:
        ~FilmProject()
        {
            for (std::vector<Material*>::iterator it = Materials.begin(); it != Materials.end(); ++it)
            {
                delete *it;
            }
            Materials.clear();
        }
        double WeeklyTicketSales = 0;
        std::vector<Material*> Materials;
        std::vector<Crew> CrewMembers;
        enum Status { Unreleased, Now_Playing, Released };
        int Status = 0;
        std::vector<std::string> Filming_Locations, KeyWords;
};
#endif