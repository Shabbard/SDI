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
    std::string dataPrefix = "../data/";
    std::string FilmData = dataPrefix + "Film_Info_backup.txt";
    std::string MaterialData = dataPrefix + "Material_Data.txt";
    std::string CrewData = dataPrefix + "Crew_Member_Info.txt";

public:
    FileHandler(Browser* browser);
    void LoadFilmProjects();
    void UpdateFile();
    void WriteToFile(std::ofstream& file);
    Crew LoadCrew(Crew CrewMember);
    std::vector<Crew> LoadEntireCrew();
    template<typename T>
    T GetMaterialType(T mat, int currentID);
    template<typename T>
    T LoadMaterial(T mat, int currentID);
    Film LoadFilm(int currentID);
    std::vector<std::string> SeparateCommasIntoData(std::string input);

    void insertionSort(struct Node** head_ref);
    void sortedInsert(struct Node** head_ref, struct Node* newNode);
};

#endif
