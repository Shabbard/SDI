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
        int ID, Runtime;
        std::string Title, VideoFormat, AudioFormat, FrameAspect, Packaging, Description, Type; 
        double RetailPrice;
        std::vector<std::string> Languages, Subtitles;
};

class VHS : public Material
{
    public:
     std::string Languages, Subtitles;
     Film film;
};

class DVD : public Material
{  
    public:
        Film film;
        const std::string Packaging = "Plastic Box";
};

// class SingleSidedDVD : public DVD
// {
//     public:
        
// };

class DoubleSidedDVD : public Material
{
    public:   
     std::pair<Film, Film> DVD;
};

class BluRay : public DVD
{
    public:
        const std::string Packaging = "Small Plastic Box";
};

class ComboBox : public Material
{
    public:
        const std::string Packaging = "Cardboard Box";
        std::vector<std::unique_ptr<Material>> DVDs;
};

#endif
