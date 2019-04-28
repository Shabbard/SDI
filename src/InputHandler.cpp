#include "InputHandler.h"

InputHandler::InputHandler(/* args */)
{
}

InputHandler::~InputHandler()
{
}

std::pair <bool,bool> InputHandler::string_int_check(std::string string_check)
{
	bool integer_val = false, string_val = false;

		for(auto it = string_check.begin(); it != string_check.end(); ++it)
		{
			if (isalpha(*it))
			{
				string_val = true;
			}
			else if (isdigit(*it))
			{
				integer_val = true;
			}
		}

	std::pair<bool, bool> output = {string_val, integer_val};
		
	return output;
}

std::string InputHandler::Basic_User_Input(std::string datatype)
{
	std::string user_input;

    do 
    {
        std::getline(std::cin, user_input);

        if (string_int_check(user_input).first && datatype == "string")
        {
            std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);
        }
        else if(!string_int_check(user_input).second && datatype == "number")
        {
            return "interror";
        }
        

		



        return user_input;
    } while(true);


    

	// if (user_input == "next")
	// if (user_input == "next")
	// {
	// 	browser->nextNode();
	// }

	// if (user_input == "back")
	// {
	// 	browser->previousNode();
	// }
}