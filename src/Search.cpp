#include "Search.h"

Search::Search()
{
}

Search::~Search()
{
}

int Search::StringVectorSearch(std::vector<std::string> Vector, std::string value)
{
    int first = 0,             // First array element
        last = Vector.size() - 1,       // Last array element
        middle,                // Mid point of search
        position = -1;         // Position of search value
    bool found = false;        // Flag

    while (!found && first <= last)
    {
        middle = (first + last) / 2;     // Calculate mid point
        if (Vector.at(middle) == value)      // If value is found at mid
        {
            found = true;
            position = middle;
        }
        else if (Vector.at(middle) > value)  // If value is in lower half
            last = middle - 1;
        else
            first = middle + 1;           // If value is in upper half
    }
    return position;
}

int Search::IntVectorSearch(std::vector<int> Vector, int value)
{
    int first = 0,             // First array element
        last = Vector.size() - 1,       // Last array element
        middle,                // Mid point of search
        position = -1;         // Position of search value
    bool found = false;        // Flag

    while (!found && first <= last)
    {
        middle = (first + last) / 2;     // Calculate mid point
        if (Vector.at(middle) == value)      // If value is found at mid
        {
            found = true;
            position = middle;
        }
        else if (Vector.at(middle) > value)  // If value is in lower half
            last = middle - 1;
        else
            first = middle + 1;           // If value is in upper half
    }
    return position;
}