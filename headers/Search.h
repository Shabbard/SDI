#include <vector>
#include <string>
class Search
{
private:
    /* data */
public:
    Search(/* args */);
    ~Search();
    int IntVectorSearch(std::vector<int> Vector, int value);
    int StringVectorSearch(std::vector<std::string> stringVector, std::string value);

};
