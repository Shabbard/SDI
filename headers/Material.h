#include <string>
#include <vector>
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
    private:
        std::string Packaging = "Plastic Box";
        
};

class DoubleSidedDVD : public Material
{
    private:
        std::string Packaging = "Plastic Box";
        
};

class BluRay : public Material
{
    private:
        std::string Packaging = "Small Plastic Box";
        
};

class ComboBox : public Material
{
    private:
        std::string Packaging = "Plastic Box";
        
};