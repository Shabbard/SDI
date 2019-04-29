#pragma once
#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "Browser.h"
#include "Film.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <typeinfo>
#include <memory>

class FileHandler
{
private:
    Browser* browser;
    std::vector<Crew*>* crewVector;
    std::vector<Material*>* matVector;
    std::string dataPrefix = "../data/";
    std::string FilmDataRead = dataPrefix + "Film_Info_backup.txt";
    std::string FilmDataWrite = dataPrefix + "Film_Info.txt";
    std::string MaterialData = dataPrefix + "Material_Data.txt";
    std::string CrewData = dataPrefix + "Crew_Member_Info.txt";

public:
    FileHandler(Browser*, std::vector<Crew*>*, std::vector<Material*>*);
    FileHandler() {};
    void LoadFilmProjects();
    void UpdateProjectFile();
    void WriteProjectToFile(std::ofstream& file);
    void WriteCrewToFile();
    Crew* LoadCrew(int);
    void LoadEntireCrew();
    template<typename T>
    T GetMaterialType(T mat, int currentID);
    template<typename T>
    T LoadMaterial(T mat, int currentID);
    Material* LoadProjectMaterial(int);
    Film LoadFilm(int currentID);
    std::vector<std::string> SeparateCommasIntoData(std::string input);
    void LoadAllMaterials();
    void Tracking(int change);
    void WriteMaterialToFile();
};

#endif
