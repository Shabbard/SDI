#include "FileHandler.h"
#include <stdlib.h>
#include <algorithm>
#include <string>
//#include <conio.h>
#pragma once

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

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
