#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
//#ifndef FILM_H
#include "Film.h"
//#endif
#include <string>
#include <vector>
#include <memory>

class Material
{
    public:
        virtual ~Material() {}
        int ID = 0, Runtime = 0;
        std::string Title, VideoFormat, AudioFormat, FrameAspect, Packaging, Description, Type; 
        double RetailPrice = 0;
        std::vector<std::string> Languages, Subtitles;
        std::vector<Material*> DVDs;
        std::pair<Film, Film> DVD;
        Film film;
};

class VHS : public Material
{
    public:
     VHS()
     {
         Type = "VHS";
         std::string Languages, Subtitles;
     }
};

class DVD : public Material
{  
    public:
        DVD()
        {
            Type = "DVD";
            Packaging = "Plastic Box";
        }
};

// class SingleSidedDVD : public DVD
// {
//     public:
        
// };

class DoubleSidedDVD : public Material
{
    public:   
     DoubleSidedDVD(){Type = "DoubleSidedDVD";}
};

class BluRay : public DVD
{
    public:
        BluRay()
        {
            Type = "BluRay";
            Packaging = "Small Plastic Box";
        }
        
};

class ComboBox : public Material
{
    public:
        ComboBox()
        {
            Type = "ComboBox";
            Packaging = "Cardboard Box";
        }

};

#endif
