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
    void DisplayCurrentFilmProject(FilmProject);
    void DisplayCrew(std::vector<Crew>);
    void DisplayAllCrew(std::vector<Crew> crewVec);
    void DisplayMaterial();
    void LoadMatData(Material* mat, std::string strvar);
    void Vector_Instructions();
    void Next_Back_Instructions();
    void interror();

};

