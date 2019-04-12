#include "Film.h"

struct Node
{
    Film data;
    Node* next;
    Node* previous;
};

class Browser
{
    private:
    Node* head = NULL;
    Node* tail = NULL;

    public:
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
};


