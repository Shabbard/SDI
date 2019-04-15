#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "Browser.h"
#include "Film.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <typeinfo>
#pragma once

class FileHandler
{
private:
    Browser* browser;
public:
    FileHandler(Browser* browser);
    ~FileHandler();
    void LoadFile(std::string filePath);
    void UpdateFile(std::string filePath);
    void WriteToFile(std::ofstream& file);
    Crew LoadCrew(std::string filePath, Crew CrewMember);
    Material* LoadMaterial(std::string filePath, Material* mat);
};

#endif
