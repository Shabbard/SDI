#pragma once
#include "Browser.h"
#include <vector>
#include <string>
#include <algorithm>
class Search
{
public:
    Search(/* args */);
    ~Search();
    int IntVectorSearch(std::vector<int> Vector, int value);
    int StringVectorSearch(std::vector<std::string> stringVector, std::string value);
    Node* SearchProjectTitle(Browser* browser, std::string search);
    std::vector<std::string> SearchActor(Browser* browser, std::string search);

};
