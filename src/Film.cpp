#include "Film.h"

Film::Film()
{
    Title = "";
    Summary = "";
    ReleaseDate = "";
    Genre.clear();
    Filming_Locations.clear();
    Languages.clear();
    KeyWords.clear();
    Crew_Members_String.clear();
    ID = 0;
    Runtime = 0;
    Status = 0;
    WeeklyTicketSales = 0;
}

Film::~Film()
{
    Title = "";
    Summary = "";
    ReleaseDate = "";
    Genre.clear();
    Filming_Locations.clear();
    Languages.clear();
    KeyWords.clear();
    Crew_Members_String.clear();
    ID = 0;
    Runtime = 0;
    Status = 0;
    WeeklyTicketSales = 0;
}
