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
    virtual ~Material(){};
    virtual void SetLanguages(std::vector<std::string>){};
    virtual void SetSubtitles(std::vector<std::string>){};
    virtual void SetBonusFeatures(std::vector<std::string>){};
    virtual void SetDVDVector(Material*){};
    virtual void SetDoubleDVD(Material*, Material*){};
    virtual void SetFilm(Film){};
    virtual std::string GetLanguage(size_t index) {};
    virtual std::string GetBonusFeature(size_t index) {};
    virtual std::string GetSubtitle(size_t index) {};
    virtual size_t GetNumLanguages() {};
    virtual size_t GetNumBonusFeatures() {};
    virtual size_t GetNumSubtitles() {};
    virtual std::vector<Material*> GetDVDs() {};
    virtual std::pair<Material*, Material*> GetDVDPair() {};

};

class VHS : public Material
{
  private:
    Film film;
    std::string Language, Subtitle;

  public:
    VHS()
    {
        Type = "VHS";
    }
    void SetLanguages(std::vector<std::string> input) override { Language = input.at(0); }
    void SetSubtitles(std::vector<std::string> input) override { Subtitle = input.at(0); }
    void SetFilm(Film in) override { film = in; }
    std::string GetLanguage(size_t index) override { return Language; }
    std::string GetSubtitle(size_t index) override { return Subtitle; }
};

class DVD : public Material
{
  private:
    Film film;
    std::vector<std::string> Languages, Subtitles, BonusFeatures;

  public:
    DVD()
    {
        Type = "DVD";
        Packaging = "Plastic Box";
    }
    void SetFilm(Film in) override { film = in; }
    void SetLanguages(std::vector<std::string> input) override { Languages = input; }
    void SetSubtitles(std::vector<std::string> input) override { Subtitles = input; }
    void SetBonusFeatures(std::vector<std::string> input) override { BonusFeatures = input; }
    std::string GetLanguage(size_t index) override { return Languages.at(index); }
    std::string GetSubtitle(size_t index) override { return Subtitles.at(index); }
    std::string GetBonusFeature(size_t index) override { return BonusFeatures.at(index); }
    size_t GetNumLanguages() override { return Languages.size(); };
    size_t GetNumSubtitles() override { return Subtitles.size(); };
    size_t GetNumBonusFeatures() override { return BonusFeatures.size(); };
};

class DoubleSidedDVD : public Material
{
  private:
    std::pair<Material*, Material*> DVD;
    std::vector<std::string> Languages, Subtitles;

  public:
    DoubleSidedDVD() { Type = "DoubleSidedDVD"; }
    void SetDoubleDVD(Material* a, Material* b) override
    {
        DVD.first = a;
        DVD.second = b;
    }
    void SetLanguages(std::vector<std::string> input) override { Languages = input; }
    void SetSubtitles(std::vector<std::string> input) override { Subtitles = input; }
    std::string GetLanguage(size_t index) override { return Languages.at(index); }
    std::string GetSubtitle(size_t index) override { return Subtitles.at(index); }
    size_t GetNumLanguages() override { return Languages.size(); };
    size_t GetNumSubtitles() override { return Subtitles.size(); };
    std::pair<Material*, Material*> GetDVDPair() override { return DVD; };
};

class BluRay : public DVD
{
  private:
    Film film;
    std::vector<std::string> Languages, Subtitles, BonusFeatures;

  public:
    BluRay()
    {
        Type = "BluRay";
        Packaging = "Small Plastic Box";
    }
    void SetFilm(Film in) override { film = in; }
    void SetLanguages(std::vector<std::string> input) override { Languages = input; }
    void SetSubtitles(std::vector<std::string> input) override { Subtitles = input; }
    void SetBonusFeatures(std::vector<std::string> input) override { BonusFeatures = input; }
    std::string GetLanguage(size_t index) override { return Languages.at(index); }
    std::string GetSubtitle(size_t index) override { return Subtitles.at(index); }
    std::string GetBonusFeature(size_t index) override { return BonusFeatures.at(index); }
    size_t GetNumLanguages() override { return Languages.size(); };
    size_t GetNumSubtitles() override { return Subtitles.size(); };
    size_t GetNumBonusFeatures() override { return BonusFeatures.size(); };
};

class ComboBox : public Material
{
  private:
    std::vector<Material *> DVDs;
    std::vector<std::string> Languages, Subtitles;

  public:
    ComboBox()
    {
        Type = "ComboBox";
        Packaging = "Cardboard Box";
    }
    ~ComboBox() override
    {
        for (std::vector<Material *>::iterator it = DVDs.begin(); it != DVDs.end(); ++it)
        {
            delete *it;
        }
        DVDs.clear();
    }
    void SetDVDVector(Material *in) override { DVDs.push_back(in); }
    void SetLanguages(std::vector<std::string> input) override { Languages = input; }
    void SetSubtitles(std::vector<std::string> input) override { Subtitles = input; }
    std::string GetLanguage(size_t index) override { return Languages.at(index); }
    std::string GetSubtitle(size_t index) override { return Subtitles.at(index); }
    size_t GetNumLanguages() override { return Languages.size(); };
    size_t GetNumSubtitles() override { return Subtitles.size(); };
    std::vector<Material*> GetDVDs() override { return DVDs; };
};
#endif
