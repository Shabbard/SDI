#include <iostream>
#include "FilmProject.h"
#include "Material.h"

class View
{
private:
    /* data */
public:
    View(/* args */);
    ~View();
    void Main_Menu_Templates();
    void BM_Templates();
    void MM_Templates();
    void Edit_Templates();
    void CNP_Templates();
    void DisplayCurrentFilmProject(FilmProject*);
    void DisplayCrew(std::vector<Crew>);
    void DisplayAllCrew(std::vector<Crew>);
    void DisplayMaterial();
    void LoadMatData(Material*, std::string);
    void Vector_Instructions();
    void Next_Back_Instructions();
    void value_error();

};

