#ifndef MATERIAL_H
#define MATERIAL_H
#include "Film.h"
#include <string>
#include <vector>
#include <memory>
#pragma once

class Material
{
private:
    /* data */
public:

    int ID, Runtime;
    std::string Title, VideoFormat, AudioFormat, FrameAspect, Packaging, Description; 
    double RetailPrice;
    std::vector<std::string> Languages, Subtitles;
    std::vector<std::unique_ptr<Material>> DVDs;
    std::pair<std::unique_ptr<Material>, std::unique_ptr<Material>> DVD;
    //Film film;

    Material(/* args */);
    ~Material();
};

class VHS : public Material
{
    public:
     std::string Languages, Subtitles;
};

class SingleSidedDVD : public Material
{
    public:
        const std::string Packaging = "Plastic Box";
};

class DoubleSidedDVD : public Material
{
    public:
     const std::string Packaging = "Plastic Box";        
};

class BluRay : public Material
{
    public:
        const std::string Packaging = "Small Plastic Box";
};

class ComboBox : public Material
{
    public:
        const std::string Packaging = "Cardboard Box";
};

#endif