#include "Film.h"

class Browser
{
    public:
    Film Data;
    Browser* next;
    Browser* previous;
    Browser* head;
    Browser* tail;

    void insert(Film new_data);
    void display();

}