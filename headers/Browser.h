#include "Film.h"

struct Node
{
    int data = 0;
    Node* next;
    Node* previous;
};

class Browser
{
    public:
    Node* head = NULL;
    Node* tail = NULL;
    Node* current = NULL;

    void insert(int new_data);
    void display();
    void nextNode();
    void previousNode();
    void insert_tail(int new_data);
    void insert_head(int new_data);
    void delete_current();
    // void delete_tail();
    // void delete_head();

};


