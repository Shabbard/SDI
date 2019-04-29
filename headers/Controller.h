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
#include <numeric>
#pragma once

class Controller
{
private:
    Browser* browser;
    FileHandler fileHandler;
    View view;
    InputHandler inputHandler;

    std::vector<Crew*>* crewVector = new std::vector<Crew*>();
    std::vector<Material*>* matVector = new std::vector<Material*>();
public:
    Controller();
    ~Controller();
    void LoadCrew();
    void LoadMaterials();
    void Init();

    void Main_Menu();
    void Browser_Menu();
    void Maintenance_Menu();
    void Edit_Menu();
    void Create_New_Project_Menu();

    void Tracking(int change, std::string);
    void Reports();

    void searchEngine();
    std::vector<std::string> SearchActor(std::string search);
    Node* SearchProjectTitle(std::string search);

    bool BasicUserInput(std::string, std::string);

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
