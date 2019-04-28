#include <string>
#include <iostream>
#include <algorithm>

class InputHandler
{
    private:
        /* data */
    public:
        InputHandler(/* args */);
        ~InputHandler();
        std::string Basic_User_Input(std::string datatype);
        std::pair <bool,bool> string_int_check(std::string string_check);
};