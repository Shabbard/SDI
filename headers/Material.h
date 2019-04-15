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
    std::string Title, VideoFormat, AudioFormat, FrameAspect, Packaging; 
    double RetailPrice;
    std::vector<std::string> Languages, Subtitles;
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
     std::pair<SingleSidedDVD, SingleSidedDVD> DVD;
        
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
        std::vector<std::unique_ptr<Material>> DVDs;
        
};
