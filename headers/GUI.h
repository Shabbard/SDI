#ifndef GUI_H
#define GUI_H
#include "FileHandler.h"
#include "FilmProject.h"
#include "Browser.h"
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <stdexcept>
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
    std::vector<Crew> crewVector;
public:
    GUI(Browser* browser, FileHandler* file);
    ~GUI();
    void Main_Menu_Templates();
    void BM_Templates();
    void MM_Templates();
    void Edit_Templates();
    void CNP_Templates();
    void LoadCrew();

    void Main_Menu();
    void Browser_Menu();
    void Maintenance_Menu();
    void Edit_Menu();
    void Create_New_Project_Menu();
    void DisplayMaterials();
    void LoadMatData(Material* mat, std::string strvar);
    void DisplayCurrentFilmProject();
    void DisplayCrew();
    void CreateNewCrew();
    Material* CreateNewMaterial();
    void SaveAllFiles();

    void project_edit();
    void crew_edit();
    void material_edit();
    void material_edit_management(int material_ID);

    int unique_id_check_project();
    int unique_id_check_material();
    int unique_id_check_crew();

    std::pair <bool,bool> string_int_check(std::string string_check);

    void Basic_User_Input(std::string user_input);
};

#endif
