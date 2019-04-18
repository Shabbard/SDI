#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include "Film.h"
#include <string>
#include <vector>
#include <memory>

class Material
{
    public:
        int ID = 0, Runtime = 0;
        std::string Title, VideoFormat, AudioFormat, FrameAspect, Packaging, Description, Type; 
        double RetailPrice = 0;
        virtual void SetLanguages(std::vector<std::string>);
        virtual void SetSubtitiles(std::vector<std::string>);
        virtual void SetDVDVector(Material*);
        virtual void SetDoubleDVD(Film, Film);
        virtual void SetFilm(Film);
};

class VHS : public Material
{   
    private:
        Film film;
        std::string Languages, Subtitles;
    public:
     VHS()
     {
         Type = "VHS";
     }
     void SetLanguages(std::vector<std::string> input) override {Languages = input.at(0);}
     void SetSubtitiles(std::vector<std::string> input) override {Subtitles = input.at(0);}
     void SetFilm(Film in) override {film = in;} 
};

class DVD : public Material
{   
    private:
        Film film;
        std::vector<std::string> Languages, Subtitles;
    public:
        DVD()
        {
            Type = "DVD";
            Packaging = "Plastic Box";
        }
        void SetFilm(Film in) override {film = in;}
        void SetLanguages(std::vector<std::string> input) override {Languages = input;}
        void SetSubtitiles(std::vector<std::string> input) override {Subtitles = input;}
};

class DoubleSidedDVD : public Material
{
    private:
        std::pair<Film, Film> DVD;
        std::vector<std::string> Languages, Subtitles;
    public:   
     DoubleSidedDVD(){Type = "DoubleSidedDVD";}
     virtual void SetDoubleDVD(Film, Film);
};

class BluRay : public DVD
{
    private:
        Film film;
        std::vector<std::string> Languages, Subtitles;
    public:
        BluRay()
        {
            Type = "BluRay";
            Packaging = "Small Plastic Box";
        }
        void SetFilm(Film in) override {film = in;}
        void SetLanguages(std::vector<std::string> input) override {Languages = input;}
        void SetSubtitiles(std::vector<std::string> input) override {Subtitles = input;}     
};

class ComboBox : public Material
{
    private:
        std::vector<Material*> DVDs;
        std::vector<std::string> Languages, Subtitles;
    public:
        ComboBox()
        {
            Type = "ComboBox";
            Packaging = "Cardboard Box";
        }
        void SetDVDVector(Material* in) override {DVDs.push_back(in);}
        void SetLanguages(std::vector<std::string> input) override {Languages = input;}
        void SetSubtitiles(std::vector<std::string> input) override {Subtitles = input;}
};
#endif