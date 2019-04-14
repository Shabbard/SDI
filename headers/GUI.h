#include "FileHandler.h"
#include <stdlib.h>
#include <algorithm>
#include <string>
#pragma once

class GUI
{
private:
    Browser* browser;
public:
    GUI(Browser* browser);
    ~GUI();
    void GUI_Templates(std::string GUI_ID);
    void CLI(FileHandler fileHandler, std::string filePath);
};

