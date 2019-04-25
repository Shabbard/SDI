#include "Material.h"

DVD::DVD()
{
    Type = "dvd";
    Packaging = "Plastic Box";
}

void DoubleSidedDVD::SetDoubleDVD(Material* a, Material* b)
{
    DVD.first = a;
    DVD.second = b;
}

BluRay::BluRay()
{
    Type = "bluray";
    Packaging = "Small Plastic Box";
}

ComboBox::ComboBox()
{
    Type = "combobox";
    Packaging = "Cardboard Box";
}
ComboBox::~ComboBox()
{
    for (std::vector<Material *>::iterator it = DVDs.begin(); it != DVDs.end(); ++it)
    {
        delete *it;
    }
    DVDs.clear();
}
