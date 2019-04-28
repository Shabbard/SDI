#include "Material.h"

DVD::DVD()
{
    Type = "dvd";
    Packaging = "plastic";
}

void DoubleSidedDVD::SetDoubleDVD(Material* a, Material* b)
{
    DVD.first = a;
    DVD.second = b;
}

BluRay::BluRay()
{
    Type = "bluray";
    Packaging = "small plastic box";
}

ComboBox::ComboBox()
{
    Type = "combobox";
    Packaging = "cardboard";
}
ComboBox::~ComboBox()
{
    for (std::vector<Material *>::iterator it = DVDs.begin(); it != DVDs.end(); ++it)
    {
        delete *it;
    }
    DVDs.clear();
}
