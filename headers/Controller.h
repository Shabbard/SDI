#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "FileHandler.h"
#include "FilmProject.h"
#include "Browser.h"
#include "View.h"
#include "InputHandler.h"
#include <stdlib.h>

#include <string>
#include <stdexcept>
//#include <conio.h>
#pragma once

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class Controller
{
private:
    Browser* browser;
    FileHandler fileHandler;
    View view;
    InputHandler inputHandler;

    std::vector<Crew> crewVector;
    std::vector<Material*> matVector;
public:
    Controller();
    ~Controller();
    void LoadCrew();
    void LoadMaterials();

    void Main_Menu();
    void Browser_Menu();
    void Maintenance_Menu();
    void Edit_Menu();
    void Create_New_Project_Menu();

    void DisplayMaterials(std::vector<Material*> matVec);
 
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
};

#endif
