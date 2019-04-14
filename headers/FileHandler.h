#include "Browser.h"
#include <iostream>
#include <fstream>
#include <regex>
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
};


