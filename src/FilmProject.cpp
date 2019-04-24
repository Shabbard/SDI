#include "FilmProject.h"

FilmProject::~FilmProject()
{
            for (std::vector<Material*>::iterator it = Materials.begin(); it != Materials.end(); ++it)
            {
                delete *it;
            }
            Materials.clear();
}