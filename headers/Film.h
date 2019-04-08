#include <string>
#include <vector>

class Film
{
  private:
    
  public:
    Film();
    ~Film();
    std::string Title, Summary, ReleaseDate;
    std::vector<std::string> Genre, FilmingLocations, Langauges, KeyWords;
    int Runtime;
    double WeeklyTicketSale;

}