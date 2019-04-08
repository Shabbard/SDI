#include <string>

class Film
{
  private:
    std::string Title, Summary, ReleaseDate;
    std::vector<std::string> Genre, FilmingLocations, Langauges, KeyWords;
    int Runtime;
    double WeeklyTicketSale;

  public:
    Film();
    std::string GetTitle(), GetSummary(), GetReleaseDate();
    std::vector<std::string> GetGenre(), GetFilmingLocations(), GetLanguages(), GetKeyWords();
    int GetRuntime();
    double GetWeeklyTicketSales();
}