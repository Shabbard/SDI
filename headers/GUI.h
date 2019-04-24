#ifndef GUI_H
#define GUI_H
#include "FileHandler.h"
#include "FilmProject.h"
#include "Browser.h"
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
    FileHandler* fileHandler;
public:
    GUI(Browser* browser, FileHandler* file);
    ~GUI();
    void Main_Menu_Templates();
    void BM_Templates();
    void MM_Templates();
    void Edit_Templates();
    void CNP_Templates();

    void Main_Menu();
    void Browser_Menu();
    void Maintenance_Menu();
    void Edit_Menu();
    void Create_New_Project_Menu();
    void DisplayMaterials();
    void LoadMatData(Material* mat, std::string strvar);
    void DisplayCurrentFilmProject();
    void DisplayCrew();

    void project_edit();
    void crew_edit();
    void material_edit();
    void material_edit_management();

    int unique_id_check();

    void Basic_User_Input(std::string user_input);
};

#endif
