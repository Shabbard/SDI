#include "Film.h"

struct Node
{
    Film data;
    Node* next;
    Node* previous;
};

class Browser
{
    public:
    Node* head = NULL;
    Node* tail = NULL;
    Node* current = NULL;

    void insert(Film new_data);
    void display();
    void nextNode();
    void previousNode();
    void setHead();
    void setTail();
    void insert_tail(Film new_data);
    void insert_head(Film new_data);
    void delete_current();
    // void delete_tail();
    // void delete_head();

};


